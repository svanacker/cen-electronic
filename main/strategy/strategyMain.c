#include <p30fxxxx.h>
#include <stdlib.h>

#include "strategyMain.h"

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

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

// gameboard
#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"


// navigation
#include "../../navigation/navigation.h"
#include "../../navigation/navigationTest.h"

// strategy
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameStrategyList.h"
#include "../../robot/strategy/gameStrategy.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyHandler.h"

#include "../../robot/strategy/nextGameStrategyItemComputer.h"

// specific 2012
#include "../../robot/2012/gameboardElement2012.h"
#include "../../robot/2012/strategy2012.h"

// -> Devices
#include "../../device/deviceUsage.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// System
#include "../../device/strategy/strategyDevice.h"
#include "../../device/strategy/strategyDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverTransmitter.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverStreamListener.h"

// Test
// #include "../../test/common/math/bitListTest.h"

// The port for which we debug (we can send instruction too)
#include "../../robot/robot.h"

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
static Device deviceListArray[STRATEGY_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[STRATEGY_BOARD_TIMER_LENGTH];

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[STRATEGY_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[STRATEGY_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

// compositeOutputStream
static CompositeOutputStream driverToI2CSlaveAndDebugCompositeOutputStream;

void initDevicesDescriptor() {
	initDeviceList(&deviceListArray, STRATEGY_BOARD_DEVICE_LENGTH);
	addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());

	addLocalDevice(getStrategyDeviceInterface(), getStrategyDeviceDescriptor());

	initDevices(&devices);
}

void initDriverToI2CSlaveAndDebugCompositeOutputStream(bool includeI2C) {
	initCompositeOutputStream(&driverToI2CSlaveAndDebugCompositeOutputStream);

	// UART / DEBUG
	addOutputStream(&driverToI2CSlaveAndDebugCompositeOutputStream, getOutputStreamLogger(INFO));

	// I2C
	if (includeI2C) {
		StreamLink* i2cStreamLink = getI2cStreamLink();
		Buffer* i2cOutputBuffer = i2cStreamLink->outputBuffer;
		OutputStream* i2cOutputStream = getOutputStream(i2cOutputBuffer);
	
		addOutputStream(&driverToI2CSlaveAndDebugCompositeOutputStream, i2cOutputStream);
	} 
}

/**
 * Redirect to debug output Stream for SIMULATION_MODE
 */
bool redirectDriverToCompositeOutputStream() {
    InputStream* inputStream = getInputStream(getDriverRequestBuffer());

	// Redirect to debug OutputStream
	copyInputToOutputStream(inputStream, &(driverToI2CSlaveAndDebugCompositeOutputStream.outputStream), NULL, COPY_ALL); 

	return true;
}

/**
 * @private
 */
void initDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, STRATEGY_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
				&driverResponseBuffer, &driverResponseBufferArray, STRATEGY_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);

	// Include I2C => true, false, else
	initDriverToI2CSlaveAndDebugCompositeOutputStream(true);
	// Redirect driver to I2C Slave (not default behaviour)
	setRedirectionTransmitFromDriverRequestBuffer(&redirectDriverToCompositeOutputStream);
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


	initTimerList(&timerListArray, STRATEGY_BOARD_TIMER_LENGTH);

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

	initDriversDescriptor();

	// initStrategy2012(0);
	//setColor(COLOR_VIOLET);

	// printGameboard(getOutputStreamLogger(INFO));
	// printStrategyAllDatas(getOutputStreamLogger(INFO));

	initStrategyHandler();

	#ifdef MPLAB_SIMULATION
		//addNavigationLocations();
		//printDeviceListUsage(getOutputStreamLogger(INFO));
		while (nextStep());
		while (1);
	#endif

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
