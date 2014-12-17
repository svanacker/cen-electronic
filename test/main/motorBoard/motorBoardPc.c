#include "motorBoardPc.h"

#include <stdlib.h>
#include <stdio.h>

#include "../../../common/clock/clock.h"
#include "../../../common/eeprom/pc/eepromPc.h"
#include "../../../common/error/error.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/io/pc/consoleInputStream.h"
#include "../../../common/io/filter.h"
#include "../../../common/io/stream.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/pc/consoleLogHandler.h"

#include "../../../common/timer/timerList.h"


#include "../../../device/device.h"
#include "../../../device/deviceList.h"

// MOTION

#include "../../../device/motion/pid/pidDevice.h"
#include "../../../device/motion/pid/pidDeviceInterface.h"

#include "../../../device/motion/position/codersDevice.h"
#include "../../../device/motion/position/codersDeviceInterface.h"

#include "../../../device/motion/position/trajectoryDevice.h"
#include "../../../device/motion/position/trajectoryDeviceInterface.h"

#include "../../../device/motion/simple/motionDevice.h"
#include "../../../device/motion/simple/motionDeviceInterface.h"

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
#include "../../../drivers/driverList.h"
#include "../../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../../drivers/test/testDriver.h"

#include "../../../remote/clock/remoteClock.h"

#include "../processHelper.h"

// Dispatchers
#define MOTOR_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH 2
static DriverDataDispatcher driverDataDispatcherListArray[MOTOR_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH];

// Drivers
#define MOTOR_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH	40
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MOTOR_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH];
#define MOTOR_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH	40
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MOTOR_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH];

// Timers
#define MOTOR_BOARD_PC_TIMER_LENGTH	10
static Device timerListArray[MOTOR_BOARD_PC_TIMER_LENGTH];

// ConsoleOutputStream
static InputStream consoleInputStream;
static OutputStream consoleOutputStream;
#define MOTOR_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH	40
static char consoleInputBufferArray[MOTOR_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH];
static Buffer consoleInputBuffer;
#define MOTOR_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH	40
static char consoleOutputBufferArray[MOTOR_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH];
static Buffer consoleOutputBuffer;

// Devices
#define MOTOR_BOARD_PC_DEVICE_LIST_LENGTH		20
static Device deviceListArray[MOTOR_BOARD_PC_DEVICE_LIST_LENGTH];

void motorBoardWaitForInstruction(void) {

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

void runMotorBoardPC(void) {
	setPicName(MOTOR_BOARD_PC_NAME);
	moveConsole(HALF_SCREEN_WIDTH, 0, HALF_SCREEN_WIDTH, CONSOLE_HEIGHT);

	// We use http://patorjk.com/software/taag/#p=testall&v=2&f=Acrobatic&t=MOTOR%20BOARD%20PC
	// with Font : Jerusalem
	printf(" __  __  ___ _____ ___  ____     ____   ___    _    ____  ____     ____   ____\r\n");
	printf("|  \\/  |/ _ |_   _/ _ \\|  _ \\   | __ ) / _ \\  / \\  |  _ \\|  _ \\   |  _ \\ / ___|\r\n");
	printf("| |\\/| | | | || || | | | |_) |  |  _ \\| | | |/ _ \\ | |_) | | | |  | |_) | |    \r\n");
	printf("| |  | | |_| || || |_| |  _ <   | |_) | |_| / ___ \\|  _ <| |_| |  |  __/| |___ \r\n");
	printf("|_|  |_|\\___/ |_| \\___/|_| \\_\\  |____/ \\___/_/   \\_|_| \\_|____/   |_|    \\____|\r\n");
	printf("\r\n");

	initLog(DEBUG);
	initConsoleInputStream(&consoleInputStream);
	initConsoleOutputStream(&consoleOutputStream);
	addConsoleLogHandler(DEBUG);
	appendStringCRLF(getDebugOutputStreamLogger(), getPicName());

	initTimerList((Timer(*)[]) &timerListArray, MOTOR_BOARD_PC_TIMER_LENGTH);

	initBuffer(&consoleInputBuffer, (char(*)[]) &consoleInputBufferArray, MOTOR_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH, "inputConsoleBuffer", "IN");
	initBuffer(&consoleOutputBuffer, (char(*)[]) &consoleOutputBufferArray, MOTOR_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH, "outputConsoleBuffer", "IN");

	// Dispatchers
	initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, MOTOR_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH);
	addLocalDriverDataDispatcher();

	// Init the drivers
	initDrivers(&driverRequestBuffer, (char(*)[]) &driverRequestBufferArray, MOTOR_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH,
		&driverResponseBuffer, (char(*)[]) &driverResponseBufferArray, MOTOR_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH);

	// Get test driver for debug purpose
	addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);

	// Devices
	initDeviceList((Device(*)[]) &deviceListArray, MOTOR_BOARD_PC_DEVICE_LIST_LENGTH);
	addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
	addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
	addLocalDevice(getSystemDebugDeviceInterface(), getSystemDebugDeviceDescriptor());
	addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());

	addLocalDevice(getPIDDeviceInterface(), getPIDDeviceDescriptor());
	addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
	addLocalDevice(getCodersDeviceInterface(), getCodersDeviceDescriptor());
	addLocalDevice(getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
	addLocalDevice(getMotionDeviceInterface(), getMotionDeviceDescriptor());

	initDevices();

	while (1) {
		motorBoardWaitForInstruction();
	}
}