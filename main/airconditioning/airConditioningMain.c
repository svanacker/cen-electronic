#include <p30fxxxx.h>
#include <stdlib.h>

#include "airConditioningMain.h"

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

#include "../../common/io/compositeOutputStream.h"
#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/pin.h"
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
#include "../../device/deviceUsage.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Servo
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverTransmitter.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverStreamListener.h"

#ifndef MPLAB_SIMULATION
	#define SERIAL_PORT_DEBUG 		SERIAL_PORT_2
#else
	// We use the same port for both
	#define SERIAL_PORT_DEBUG 		SERIAL_PORT_1
#endif

/**
* Device list.
*/
static DeviceList devices;

// serial DEBUG 
static char debugInputBufferArray[AIR_CONDITIONING_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[AIR_CONDITIONING_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler serialLogHandler;

// devices
static Device deviceListArray[AIR_CONDITIONING_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[AIR_CONDITIONING_BOARD_TIMER_LENGTH];

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[AIR_CONDITIONING_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[AIR_CONDITIONING_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

void initDevicesDescriptor() {
	initDeviceList(&deviceListArray, AIR_CONDITIONING_BOARD_DEVICE_LENGTH);
	addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
	addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());

	initDevices(&devices);
}

/**
 * @private
 */
void initDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, AIR_CONDITIONING_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
				&driverResponseBuffer, &driverResponseBufferArray, AIR_CONDITIONING_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);
}

void initStrategyBoardIO() {
	// 2011 : TODO : A regarder
	ADPCFG = 0xFFFF;
}

int main(void) {
	setPicName("AIR_COND_BOARD");

	initStrategyBoardIO();

	openSerialLink(	&debugSerialStreamLink,
					&debugInputBuffer,
					&debugInputBufferArray,
					AIR_CONDITIONING_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
					&debugOutputBuffer,
					&debugOutputBufferArray,
					AIR_CONDITIONING_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
					&debugOutputStream,
					SERIAL_PORT_DEBUG);


	initTimerList(&timerListArray, AIR_CONDITIONING_BOARD_TIMER_LENGTH);

	// Init the logs
	initLog(DEBUG);
	addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
	appendString(getOutputStreamLogger(INFO), getPicName());
	println(getOutputStreamLogger(INFO));

	// init the devices
	initDevicesDescriptor();

	initDriversDescriptor();

	// Init the timers management
	startTimerList();
	while (1) {

		// UART Stream
		handleStreamInstruction(&debugInputBuffer,
								&debugOutputBuffer,
								&debugOutputStream,
								&filterRemoveCRLF,
								NULL);
	}
	return (0);
}
