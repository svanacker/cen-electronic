#include <i2c.h>
#include <p30fxxxx.h>
#include <stdlib.h>

#include "strategyMain.h"

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

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

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/2012/gameboardElement2012.h"

#include "../../navigation/navigation.h"
#include "../../navigation/navigationTest2.h"

// -> Devices

// Test
#include "../../device/test/deviceTest.h"
#include "../../device/test/deviceTestInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

#include "../../drivers/driverStreamListener.h"

// The port for which we debug (we can send instruction too)
#include "../../robot/robot.h"

#ifndef MPBLAB_SIMULATION
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
static char debugInputBufferArray[STRATEGY_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[STRATEGY_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler serialLogHandler;

// i2c Link
static char i2cSlaveInputBufferArray[STRATEGY_BOARD_I2C_INPUT_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[STRATEGY_BOARD_I2C_OUTPUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSerialStreamLink;

// devices
static Device testDevice;
static Device systemDevice;

void initDevicesDescriptor() {
	addLocalDevice(&testDevice, getTestDeviceInterface(), getTestDeviceDescriptor());
	addLocalDevice(&systemDevice, getSystemDeviceInterface(), getSystemDeviceDescriptor());

	initDevices(&devices);
}

void initStrategyBoardIO() {
	// 2011 : TODO : A regarder
	ADPCFG = 0xFFFF;
}

int main(void) {
	setPicName("STRATEGY_BOARD");

	initStrategyBoardIO();
	openSerialLink(	&debugSerialStreamLink,
					&debugInputBuffer,
					&debugInputBufferArray,
					STRATEGY_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
					&debugOutputBuffer,
					&debugOutputBufferArray,
					STRATEGY_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
					&debugOutputStream,
					SERIAL_PORT_DEBUG);

	// Init the logs
	initLog(DEBUG);
	addLogHandler(&serialLogHandler, "UART", &debugOutputStream, DEBUG);
	appendString(getOutputStreamLogger(INFO), getPicName());
	println(getOutputStreamLogger(INFO));

	openSlaveI2cStreamLink(&i2cSerialStreamLink,
							&i2cSlaveInputBuffer,
							&i2cSlaveInputBufferArray,
							STRATEGY_BOARD_I2C_INPUT_BUFFER_LENGTH,
							&i2cSlaveOutputBuffer,
							&i2cSlaveOutputBufferArray,
							STRATEGY_BOARD_I2C_OUTPUT_BUFFER_LENGTH,
							STRATEGY_BOARD_I2C_ADDRESS
						);

	// init the devices
	initDevicesDescriptor();

	// addElements2012();
	
	//int cost = addNavigationLocationsTest2();
	// printNavigationContext(&debugOutputStream);
	// appendStringAndDec(&debugOutputStream, "cost=", cost);

	// printGameboard(&debugOutputStream);

	while(1) {

	}

	// Init the timers management
	startTimerList();
	while (1) {

		// I2C Stream
		handleStreamInstruction(&i2cSlaveInputBuffer,
								&i2cSlaveOutputBuffer,
								NULL,
								&filterRemoveCRLF,
								NULL);

		// UART Stream
		handleStreamInstruction(&debugInputBuffer,
								&debugOutputBuffer,
								&debugOutputStream,
								&filterRemoveCRLF,
								NULL);
	}
	return (0);
}
