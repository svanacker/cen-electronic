#define _SUPPRESS_PLIB_WARNING
#include <i2c.h>
#include <p30Fxxxx.h>
#include <stdlib.h>

#define CUSTOM_BUFFER_SIZE 40

#include "../../main/beaconReceiver/beaconReceiverBoard.h"
#include "../../main/beaconBoard/beaconBoard.h"

#include "../../common/setup/30F/picSetup30F.h"

#include "../../common/commons.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/printWriter.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/deviceList.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

// -> Devices

// Test
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

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

// The port for which we debug (we can send instruction too)
#define SERIAL_PORT_DEBUG     SERIAL_PORT_2

// The port for which we dialog with ZIGBEE
#define SERIAL_PORT_ZIGBEE     SERIAL_PORT_1

// logs
static LogHandler logHandlerListArray[BEACON_RECEIVER_LOG_HANDLER_LIST_LENGTH];

// DEVICES
static Device deviceListArray[BEACON_RECEIVER_DEVICE_LENGTH];

// Timers
static Timer timerListArray[BEACON_RECEIVER_BOARD_TIMER_LENGTH];

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
#define        RESPONSE_DATA_OUTPUT_BUFFER_LENGTH        20
static Buffer responseDataOutputBuffer;
static char responseDataOutputBufferArray[RESPONSE_DATA_OUTPUT_BUFFER_LENGTH];
static OutputStream responseDataOutputStream; 

// DISPATCHERS

// -> zigbee->Beacon Board Main
static DriverDataDispatcher beaconBoardDispatcher;
static InputStream beaconBoardInputStream;
static OutputStream beaconBoardOutputStream;

// i2c Link
static I2cBus beaconReceiverI2cBus;
static char i2cSlaveInputBufferArray[BEACON_RECEIVER_BOARD_I2C_INPUT_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[BEACON_RECEIVER_BOARD_I2C_OUTPUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSerialStreamLink;

// events
static JennicEvent dataEvent;
static JennicEvent errorEvent;
static JennicEvent connectionEstablishedEvent;
static JennicEvent connectionResetEvent;

// I2C Debug
// static Buffer debugI2cInputBuffer;
// static Buffer debugI2cOutputBuffer;

void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, BEACON_RECEIVER_DEVICE_LENGTH);

    // Remote
    addZigbeeRemoteDevice(getLaserBeaconDeviceInterface(), JENNIC_COORDINATER_MAC_ADDRESS);
    addZigbeeRemoteDevice(getTestDeviceInterface(), JENNIC_COORDINATER_MAC_ADDRESS);

    //addLocalDevice(&testDevice, getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getCommonBeaconDeviceInterface(), getCommonBeaconDeviceDescriptor());
    addLocalDevice(getBeaconReceiverDeviceInterface(), getBeaconReceiverDeviceDescriptor());

    initDevices();
}

void initBeaconReceiverIO() {
    // Use All port as digital Port
    ADPCFG = 0xFFFF;
    // PORT B0->B3 as output (network Status)
    // GREEN
    TRISBbits.TRISB0 = 0;
    // ORANGE
    TRISBbits.TRISB1 = 0;
    // RED
    TRISBbits.TRISB2 = 0;
    // BLUE
    TRISBbits.TRISB3 = 0;
}

/**
 * Inverse network event pin status to indicates that the jennic receive either event or either data.
 * The other network status pin help to know if the event is RST, NTU, DATA ...
 */
void updatePinNetworkEventStatus() {
    // on / off the led each time Data arrived
    LATBbits.LATB3 = (!PORTBbits.RB3);
}

void updatePinNetworkStatus() {
    int networkStatus = getJennicNetworkStatus();
    LATBbits.LATB0 = networkStatus == JENNIC_LINK_CONNECTED;
    LATBbits.LATB1 = networkStatus == JENNIC_WAITING_FOR_NODE;
    LATBbits.LATB2 = networkStatus == JENNIC_NOT_INITIALIZED;
    updatePinNetworkEventStatus();
}

void onError(JennicEvent* jennicEvent) {
    appendString(getErrorOutputStreamLogger(), "ERROR ! \n");
    onJennicError();
}

/**
 * Called when the network started.
 */ 
void onConnectionEstablished(JennicEvent* jennicEvent) {
    setJennicNetworkStatus(JENNIC_LINK_CONNECTED);
    updatePinNetworkStatus();
    appendString(getInfoOutputStreamLogger(), "CONNECTION ESTABLISHED ! \n");
}

void onConnectionReset(JennicEvent* jennicEvent) {
    setJennicNetworkStatus(JENNIC_WAITING_FOR_NODE);
    updatePinNetworkStatus();
    appendString(getErrorOutputStreamLogger(), "CONNECTION RESET ! \n");
    // TODO : Reset Robot Position
    // TODO : Get the time of the position
}

void onData(JennicEvent* jennicEvent) {
    // Manage real Data into the Jennic Buffer
    Buffer* requestBuffer = getJennicInDataBuffer();
    if (!isBufferEmpty(requestBuffer)) {
        appendString(&debugOutputStream, "\nDATA ! ");
        updatePinNetworkEventStatus();
        // handle it like other source (UART, I2C ...)
        handleStreamInstruction(requestBuffer, &responseDataOutputBuffer, &responseDataOutputStream, &filterRemoveCRLF, NULL);
        onJennicData();
    }
    updatePinNetworkStatus();
}

void registerJennicEvents() {
    initJennicEventList();
    addJennicEvent(&connectionEstablishedEvent, JENNIC_NETWORK_STARTED, JENNIC_COORDINATER_MAC_ADDRESS, JENNIC_ROUTER_MAC_ADDRESS, NULL, NO_PAY_LOAD, onConnectionEstablished);
    addJennicEvent(&connectionResetEvent, JENNIC_RESET, NULL, NULL, NULL, NO_PAY_LOAD, onConnectionReset);
    addJennicEvent(&errorEvent, JENNIC_RESPONSE_ERROR, NULL, NULL, NULL, NO_PAY_LOAD, onError);
    // WARN : Length of data must be > 9 in hexadecimal (because size is on 2 char) => ???
    addJennicEvent(&dataEvent, JENNIC_RECEIVE_DATA, JENNIC_COORDINATER_MAC_ADDRESS, "0", "???", 4, onData);
}

int runZigBeeReceiver() {
    setBoardName("BEACON RECEIVER BOARD");
    initBeaconReceiverIO();

    // zigBee link through UART connected to Zigbee
    openSerialLink(    &zigbeeSerialStreamLink,
                    &zigbeeInputBuffer,
                    &zigbeeInputBufferArray,
                    BEACON_RECEIVER_BOARD_ZIGBEE_INPUT_BUFFER_LENGTH,
                    &zigbeeOutputBuffer,
                    &zigbeeOutputBufferArray,
                    BEACON_RECEIVER_BOARD_ZIGBEE_OUTPUT_BUFFER_LENGTH,
                    &zigbeeOutputStream,
                    SERIAL_PORT_ZIGBEE,
                    115200);

    // Debug link through Free UART
    openSerialLink(    &debugSerialStreamLink,
                    &debugInputBuffer,
                    &debugInputBufferArray,
                    BEACON_RECEIVER_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
                    &debugOutputBuffer,
                    &debugOutputBufferArray,
                    BEACON_RECEIVER_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
                    &debugOutputStream,
                    SERIAL_PORT_DEBUG,
                    115200);

    initTimerList(&timerListArray, BEACON_RECEIVER_BOARD_TIMER_LENGTH);

    // To response data
    initBuffer(&responseDataOutputBuffer, &responseDataOutputBufferArray, RESPONSE_DATA_OUTPUT_BUFFER_LENGTH, "responseDataOutputBuffer", "RESPONSE");
    initZigbeeOutputStream(&responseDataOutputStream, &responseDataOutputBuffer, JENNIC_COORDINATER_MAC_ADDRESS);


    // Init the logs
    initLogs(DEBUG, &logHandlerListArray, BEACON_RECEIVER_LOG_HANDLER_LIST_LENGTH);
    addLogHandler("UART", &debugOutputStream, DEBUG);
    appendString(getDebugOutputStreamLogger(), getBoardName());
    println(getDebugOutputStreamLogger());    

    // I2C Stream Link
    openSlaveI2cStreamLink(&i2cSerialStreamLink,
                            &i2cSlaveInputBuffer,
                            &i2cSlaveInputBufferArray,
                            BEACON_RECEIVER_BOARD_I2C_INPUT_BUFFER_LENGTH,
                            &i2cSlaveOutputBuffer,
                            &i2cSlaveOutputBufferArray,
                            BEACON_RECEIVER_BOARD_I2C_OUTPUT_BUFFER_LENGTH,
                            &beaconReceiverI2cBus,
                            BEACON_RECEIVER_I2C_ADDRESS
                        );

    // Zigbee OutputStream
    
    addZigbeeDriverDataDispatcher(&beaconBoardDispatcher,
                                    "BEACON_BOARD_DISPATCHER",
                                    &beaconBoardInputStream,
                                    &beaconBoardOutputStream,
                                    JENNIC_COORDINATER_MAC_ADDRESS);


    // init the devices
    initDevicesDescriptor();

    // Init the timers management
    startTimerList();

    InputStream* zigbeeInputStream = getInputStream(&zigbeeInputBuffer);
    InputStream* debugInputStream = getInputStream(&debugInputBuffer);

    // Init router streams
    initJennic5139Streams(zigbeeInputStream, &zigbeeOutputStream, &debugOutputStream);
    registerJennicEvents();

    updatePinNetworkStatus();

    // Init jennic as router
    initJennic5139Router();

    // Get interesting data 
    while (1) {
        // I2C Stream
        handleStreamInstruction(&i2cSlaveInputBuffer,
                                &i2cSlaveOutputBuffer,
                                NULL,
                                &filterRemoveCRLF,
                                NULL);

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
            /*
            // Detects if we want to redirect to devices
            if (bufferGetFirstChar(&debugInputBuffer) == '@') {
                appendString(getInfoOutputStreamLogger(), "REDIRECT COMMAND TO DEVICES \n");
                // delete the '@' char from the buffer
                bufferReadChar(&debugInputBuffer);
                setCommandRedirectToDevices();
                // Redirect to Jennic and not to the devices
                continue;                
            }
            // Copy char entered on debug -> JENNIC
            copyInputToOutputStream(debugInputStream, &zigbeeOutputStream, NULL, COPY_ALL);
            */
        }
    }
}

int main(void) {
    runZigBeeReceiver();

    return (0);
}
