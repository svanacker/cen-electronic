#include <i2c.h>
#include <p30fxxxx.h>
#include <stdlib.h>

#define CUSTOM_BUFFER_SIZE 40

#include "../../main/beaconReceiver/beaconReceiverBoard.h"
#include "../../main/beaconBoard/beaconBoard.h"

#include "../../common/setup/pic30FSetup.h"

#include "../../common/commons.h"

#include "../../common/delay/delay30F.h"

#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/stream.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

// -> Devices

// Test
#include "../../device/test/deviceTest.h"
#include "../../device/test/deviceTestInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Common Beacon (common to receiver and sender)
#include "../../device/beacon/commonBeaconDevice.h"
#include "../../device/beacon/commonBeaconDeviceInterface.h"

// beacon Receiver
#include "../../device/beacon/beaconReceiverDevice.h"
#include "../../device/beacon/beaconReceiverDeviceInterface.h"

// beacon Board
#include "../../device/beacon/laserBeaconDeviceInterface.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/dispatcher/zigbeeDriverDataDispatcher.h"

// -> Jennic
#include "../../drivers/jennic/jennic5139Driver.h"
#include "../../drivers/jennic/jennic5139EventParser.h"
#include "../../drivers/jennic/jennic5139OutputStream.h"

#ifndef MPBLAB_SIMULATION
	// The port for which we debug (we can send instruction too)
	#define SERIAL_PORT_DEBUG 	SERIAL_PORT_2
	
	// The port for which we dialog with ZIGBEE
	#define SERIAL_PORT_ZIGBEE 	SERIAL_PORT_1
#else
	// Same port when using Simulation
	#define SERIAL_PORT_DEBUG 		SERIAL_PORT_1
	#define SERIAL_PORT_ZIGBEE	 	SERIAL_PORT_1
#endif

// DEVICES

static Device testDevice;
static Device systemDevice;
static Device commonBeaconDevice;
static Device beaconReceiverDevice;
static Device beaconBoardDevice;

// BUFFER

// serial DEBUG 
static char debugInputBufferArray[BEACON_RECEIVER_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[BEACON_RECEIVER_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// serial ZIGBEE 
static char zigbeeInputBufferArray[BEACON_RECEIVER_BOARD_ZIGBEE_INPUT_BUFFER_LENGTH];
static Buffer zigbeeInputBuffer;
static char zigbeeOutputBufferArray[BEACON_RECEIVER_BOARD_ZIGBEE_OUTPUT_BUFFER_LENGTH];
static Buffer zigbeeOutputBuffer;
static OutputStream zigbeeOutputStream;
static StreamLink zigbeeSerialStreamLink;

// -> Zigbee Response
#define		RESPONSE_DATA_OUTPUT_BUFFER_LENGTH		20
static Buffer responseDataOutputBuffer;
static char responseDataOutputBufferArray[RESPONSE_DATA_OUTPUT_BUFFER_LENGTH];
static OutputStream responseDataOutputStream; 

// DISPATCHERS

// -> zigbee->Beacon Board Main
static DriverDataDispatcher beaconBoardDispatcher;
static InputStream beaconBoardInputStream;
static OutputStream beaconBoardOutputStream;

// logs
static LogHandler serialLogHandler;

// i2c Link
static char i2cSlaveInputBufferArray[BEACON_RECEIVER_BOARD_I2C_INPUT_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[BEACON_RECEIVER_BOARD_I2C_OUTPUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSerialStreamLink;

// events
static JennicEvent dataEvent;
static JennicEvent networkStartEvent;
static JennicEvent childJoinedEvent;
static JennicEvent childLeaveEvent;
static JennicEvent resetEvent;

// I2C Debug
// static Buffer debugI2cInputBuffer;
// static Buffer debugI2cOutputBuffer;

void initDevicesDescriptor() {
	//addLocalDevice(&testDevice, getTestDeviceInterface(), getTestDeviceDescriptor());
	addLocalDevice(&systemDevice, getSystemDeviceInterface(), getSystemDeviceDescriptor());
	addLocalDevice(&commonBeaconDevice, getCommonBeaconDeviceInterface(), getCommonBeaconDeviceDescriptor());
	addLocalDevice(&beaconReceiverDevice, getBeaconReceiverDeviceInterface(), getBeaconReceiverDeviceDescriptor());

	// Remote
	addZigbeeRemoteDevice(&beaconBoardDevice, getLaserBeaconDeviceInterface(), JENNIC_COORDINATER_MAC_ADDRESS);
	addZigbeeRemoteDevice(&testDevice, getTestDeviceInterface(), JENNIC_COORDINATER_MAC_ADDRESS);

	initDevices();
}

/**
 * Called when the network started.
 */ 
void onNetworkStart(JennicEvent* jennicEvent) {
	setNetworkStatus(JENNIC_WAITING_FOR_NODE);
	appendString(getOutputStreamLogger(INFO), "NETWORK START ! \n");
}

/**
 * Called when the child joined.
 */ 
void onChildJoined(JennicEvent* jennicEvent) {
	setNetworkStatus(JENNIC_LINK_CONNECTED);
	appendString(getOutputStreamLogger(INFO), "CHILD JOINED ! \n");
}

/**
 * Called when the child leave.
 */ 
void onChildLeave(JennicEvent* jennicEvent) {
	setNetworkStatus(JENNIC_WAITING_FOR_NODE);
	appendString(getOutputStreamLogger(INFO), "CHILD LEAVE ! \n");
}

void onConnectionReset(JennicEvent* jennicEvent) {
	setNetworkStatus(JENNIC_WAITING_FOR_NODE);
	appendString(getOutputStreamLogger(INFO), "CONNECTION RESET ! \n");
	// TODO : Reset Robot Position
	// TODO : Get the time of the position
}

void onData(JennicEvent* jennicEvent) {
	// Manage real Data into the Jennic Buffer
	Buffer* requestBuffer = getJennicInDataBuffer();
	if (!isBufferEmpty(requestBuffer)) {
		appendString(&debugOutputStream, "\nDATA ! ");

		// printBuffer(&debugOutputStream, inDataBuffer);
		// handle it like other source (UART, I2C ...)
		handleStreamInstruction(requestBuffer, &responseDataOutputBuffer, &responseDataOutputStream, &filterRemoveCRLF, NULL);
	}
}

void registerJennicEvents() {
	initJennicEventList();
	addJennicEvent(&networkStartEvent, JENNIC_NETWORK_STARTED, ",?,", JENNIC_ROUTER_MAC_ADDRESS, "", NO_PAY_LOAD, onNetworkStart);
	addJennicEvent(&childJoinedEvent, JENNIC_CHILD_JOINED, ",", JENNIC_COORDINATER_MAC_ADDRESS, "", NO_PAY_LOAD, onChildJoined);
	addJennicEvent(&childLeaveEvent, JENNIC_CHILD_LEAVE, ",", JENNIC_COORDINATER_MAC_ADDRESS, "", NO_PAY_LOAD, onChildLeave);
	addJennicEvent(&resetEvent, JENNIC_RESET, "", "", "", NO_PAY_LOAD, onConnectionReset);
	// WARN : Length of data must be > 9 in hexadecimal (because size is on 2 char)
	// Normally the argument is ",0,??," where 
	addJennicEvent(&dataEvent, JENNIC_RECEIVE_DATA, ",", JENNIC_COORDINATER_MAC_ADDRESS, ",0,???", 4, onData);
}

int runZigBeeReceiver() {
	setPicName("BEACON RECEIVER BOARD");

	// zigBee link through UART connected to Zigbee
	openSerialLink(	&zigbeeSerialStreamLink,
					&zigbeeInputBuffer,
					&zigbeeInputBufferArray,
					BEACON_RECEIVER_BOARD_ZIGBEE_INPUT_BUFFER_LENGTH,
					&zigbeeOutputBuffer,
					&zigbeeOutputBufferArray,
					BEACON_RECEIVER_BOARD_ZIGBEE_OUTPUT_BUFFER_LENGTH,
					&zigbeeOutputStream,
					SERIAL_PORT_ZIGBEE);

	// Debug link through Free UART
	openSerialLink(	&debugSerialStreamLink,
					&debugInputBuffer,
					&debugInputBufferArray,
					BEACON_RECEIVER_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
					&debugOutputBuffer,
					&debugOutputBufferArray,
					BEACON_RECEIVER_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
					&debugOutputStream,
					SERIAL_PORT_DEBUG);

	// To response data
    initBuffer(&responseDataOutputBuffer, &responseDataOutputBufferArray, RESPONSE_DATA_OUTPUT_BUFFER_LENGTH, "responseDataOutputBuffer", "RESPONSE");
	initZigbeeOutputStream(&responseDataOutputStream, &responseDataOutputBuffer, JENNIC_COORDINATER_MAC_ADDRESS);


	// Init the logs
	initLog(DEBUG);
	addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
	appendString(getOutputStreamLogger(DEBUG), getPicName());
	println(getOutputStreamLogger(DEBUG));	

	// I2C Stream Link
	openSlaveI2cStreamLink(&i2cSerialStreamLink,
							&i2cSlaveInputBuffer,
							&i2cSlaveInputBufferArray,
							BEACON_RECEIVER_BOARD_I2C_INPUT_BUFFER_LENGTH,
							&i2cSlaveOutputBuffer,
							&i2cSlaveOutputBufferArray,
							BEACON_RECEIVER_BOARD_I2C_OUTPUT_BUFFER_LENGTH,
							BEACON_RECEIVER_I2C_ADDRESS
						);

	// init the devices
	initDevicesDescriptor();

	// Zigbee OutputStream
	
    addZigbeeDriverDataDispatcher(&beaconBoardDispatcher,
    						        "BEACON_BOARD_DISPATCHER",
						            &beaconBoardInputStream,
						            &beaconBoardOutputStream,
						            JENNIC_COORDINATER_MAC_ADDRESS);

	// Init the timers management
	#ifndef MPBLAB_SIMULATION
    startTimerList();
	#endif

	InputStream* zigbeeInputStream = getInputStream(&zigbeeInputBuffer);
	InputStream* debugInputStream = getInputStream(&debugInputBuffer);

	// Init router streams
	initJennic5139Streams(zigbeeInputStream, &zigbeeOutputStream, &debugOutputStream);
	registerJennicEvents();

	// Get interesting data 
    while (1) {
		// I2C Stream
		handleStreamInstruction(&i2cSlaveInputBuffer,
								&i2cSlaveOutputBuffer,
								NULL,
								&filterRemoveCRLF,
								NULL);

		//handleStreamInstruction(&zigbeeInputBuffer, &zigbeeOutputBuffer, &zigbeeOutputStream, &filterRemoveCRLF, NULL);


        // Copy data from the Jennic to the debug outputStream
        copyFromZigbeeToDebugRetainingData();

		// Redirect to Devices
		if (isCommandRedirectToDevices()) {
        	// Handle debug from UART
        	handleStreamInstruction(&debugInputBuffer, &debugOutputBuffer, &debugOutputStream, &filterRemoveCRLF, NULL);
		}
		else {
			if (isBufferEmpty(&debugInputBuffer)) {
				continue;
			}
			// Detects if we want to redirect to devices
			if (bufferGetFirstChar(&debugInputBuffer) == '@') {
				appendString(getOutputStreamLogger(INFO), "REDIRECT COMMAND TO DEVICES \n");
				// delete the '@' char from the buffer
				bufferReadChar(&debugInputBuffer);
				setCommandRedirectToDevices();
				// Redirect to Jennic and not to the devices
				continue;				
			}
	        // Copy char entered on debug -> JENNIC
	        copyInputToOutputStream(debugInputStream, &zigbeeOutputStream, NULL, COPY_ALL);
		}
    }
}

int main(void) {
	runZigBeeReceiver();

	return (0);
}
