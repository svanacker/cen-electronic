#include "mainBoard32Pc.h"

#include <stdlib.h>

#include "../../../common/clock/clock.h"
#include "../../../common/error/error.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/io/pc/consoleInputStream.h"
#include "../../../common/io/filter.h"
#include "../../../common/io/stream.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/pc/consoleLogHandler.h"

#include "../../../device/device.h"
#include "../../../device/deviceList.h"

// CLOCK
#include "../../../device/clock/clockDevice.h"
#include "../../../device/clock/clockDeviceInterface.h"

// SERVO
#include "../../../device/servo/servoDevice.h"
#include "../../../device/servo/servoDeviceInterface.h"

// STRATEGY
#include "../../../device/strategy/strategyDevice.h"
#include "../../../device/strategy/strategyDeviceInterface.h"

// SYSTEM
#include "../../../device/system/systemDevice.h"
#include "../../../device/system/systemDeviceInterface.h"

// SYSTEM DEBUG
#include "../../../device/system/systemDebugDevice.h"
#include "../../../device/system/systemDebugDeviceInterface.h"

#include "../../../device/test/testDevice.h"
#include "../../../device/test/testDeviceInterface.h"

#include "../../../device/motor/pwmMotorDevice.h"
#include "../../../device/motor/pwmMotorDeviceInterface.h"

#include "../../../drivers/driverStreamListener.h"
#include "../../../drivers/clock/mockClock.h"
#include "../../../drivers/driverList.h"
#include "../../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../../drivers/test/testDriver.h"

#include "../../../robot/match/startMatchDetector.h"
#include "../../../robot/match/startMatchDetectorDevice.h"
#include "../../../robot/match/startMatchDetectorDeviceInterface.h"
#include "../../../robot/match/pc/startMatchDetectorPc.h"

#include "../../../remote/clock/remoteClock.h"


// Dispatchers
#define MAIN_BOARD_32_PC_DATA_DISPATCHER_LIST_LENGTH 2
static DriverDataDispatcher driverDataDispatcherListArray[MAIN_BOARD_32_PC_DATA_DISPATCHER_LIST_LENGTH];

// Drivers
#define MAIN_BOARD_32_PC_REQUEST_DRIVER_BUFFER_LENGTH	40
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_32_PC_REQUEST_DRIVER_BUFFER_LENGTH];
#define MAIN_BOARD_32_PC_RESPONSE_DRIVER_BUFFER_LENGTH	40
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_32_PC_RESPONSE_DRIVER_BUFFER_LENGTH];

// ConsoleOutputStream
static InputStream consoleInputStream;
static OutputStream consoleOutputStream;
#define MAIN_BOARD_32_PC_CONSOLE_INPUT_BUFFER_LENGTH	40
static char consoleInputBufferArray[MAIN_BOARD_32_PC_CONSOLE_INPUT_BUFFER_LENGTH];
static Buffer consoleInputBuffer;
#define MAIN_BOARD_32_PC_CONSOLE_OUTPUT_BUFFER_LENGTH	40
static char consoleOutputBufferArray[MAIN_BOARD_32_PC_CONSOLE_OUTPUT_BUFFER_LENGTH];
static Buffer consoleOutputBuffer;

// Devices
#define MAIN_BOARD_32_PC_DEVICE_LIST_LENGTH		10
static Device deviceListArray[MAIN_BOARD_32_PC_DEVICE_LIST_LENGTH];

// StartMatchDetector
static StartMatchDetector startMatchDetector;

void waitForInstruction(void) {

	while (consoleInputStream.availableData(&consoleInputStream)) {
		unsigned char c = consoleInputStream.readChar(&consoleInputStream);
		consoleInputBuffer.outputStream.writeChar(&(consoleInputBuffer.outputStream), c);
		if (c == 13) {
			appendCRLF(&consoleOutputStream);
		}
		consoleOutputStream.writeChar(&consoleOutputStream, c);
	}

	// TODO : Introduce the same as interrupt to be able to add char not in the main execution program
		handleStreamInstruction(
			&consoleInputBuffer,
			&consoleOutputBuffer,
			&consoleOutputStream,
			&filterRemoveCRLF,
			NULL);
}

void runMainBoard32PC(void) {
	setPicName("MAIN BOARD 32 PC");
	initConsoleInputStream(&consoleInputStream);
	initConsoleOutputStream(&consoleOutputStream);

	initBuffer(&consoleInputBuffer, (char(*)[]) &consoleInputBufferArray, MAIN_BOARD_32_PC_CONSOLE_INPUT_BUFFER_LENGTH, "inputConsoleBuffer", "IN");
	initBuffer(&consoleOutputBuffer, (char(*)[]) &consoleOutputBufferArray, MAIN_BOARD_32_PC_CONSOLE_OUTPUT_BUFFER_LENGTH, "outputConsoleBuffer", "IN");

	initLog(DEBUG);
	addConsoleLogHandler(DEBUG);

	// Dispatchers
	initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, MAIN_BOARD_32_PC_DATA_DISPATCHER_LIST_LENGTH);
	addLocalDriverDataDispatcher();

	// Init the drivers
	initDrivers(&driverRequestBuffer, (char(*)[]) &driverRequestBufferArray, MAIN_BOARD_32_PC_REQUEST_DRIVER_BUFFER_LENGTH,
		&driverResponseBuffer, (char(*)[]) &driverResponseBufferArray, MAIN_BOARD_32_PC_RESPONSE_DRIVER_BUFFER_LENGTH);

	// Get test driver for debug purpose
	addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);

	// Devices
	initDeviceList((Device(*)[]) &deviceListArray, MAIN_BOARD_32_PC_DEVICE_LIST_LENGTH);
	addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
	addLocalDevice(getStrategyDeviceInterface(), getStrategyDeviceDescriptor());
	addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
	addLocalDevice(getSystemDebugDeviceInterface(), getSystemDebugDeviceDescriptor());
	addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());
	initStartMatchDetectorPc(&startMatchDetector);
	addLocalDevice(getStartMatchDetectorDeviceInterface(), getStartMatchDetectorDeviceDescriptor(&startMatchDetector));
	addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());

	// printf("test");

	while (1) {
		waitForInstruction();
	}
}