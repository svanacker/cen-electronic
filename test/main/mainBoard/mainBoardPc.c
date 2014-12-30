#include "mainBoardPc.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "../../../common/clock/clock.h"
#include "../../../common/delay/cenDelay.h"
#include "../../../common/eeprom/pc/eepromPc.h"
#include "../../../common/error/error.h"
#include "../../../common/i2c/i2cDebug.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/io/pc/consoleInputStream.h"
#include "../../../common/io/filter.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/pc/consoleLogHandler.h"

#include "../../../common/timer/timerList.h"


#include "../../../device/device.h"
#include "../../../device/deviceList.h"
#include "../../../device/transmitMode.h"

// CLOCK
#include "../../../device/clock/clockDevice.h"
#include "../../../device/clock/clockDeviceInterface.h"

// DISPATCHER DEVICE
#include "../../../device/dispatcher/dataDispatcherDevice.h"
#include "../../../device/dispatcher/dataDispatcherDeviceInterface.h"

// I2C -> Master
#include "../../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// EEPROM
#include "../../../device/eeprom/eepromDevice.h"
#include "../../../device/eeprom/eepromDeviceInterface.h"

// MOTION

#include "../../../device/motion/pid/pidDevice.h"
#include "../../../device/motion/pid/pidDeviceInterface.h"

#include "../../../device/motion/position/codersDevice.h"
#include "../../../device/motion/position/codersDeviceInterface.h"

#include "../../../device/motion/position/trajectoryDevice.h"
#include "../../../device/motion/position/trajectoryDeviceInterface.h"

#include "../../../device/motion/simple/motionDevice.h"
#include "../../../device/motion/simple/motionDeviceInterface.h"

// SERVO
#include "../../../device/servo/servoDevice.h"
#include "../../../device/servo/servoDeviceInterface.h"

// STRATEGY
#include "../../../device/strategy/strategyDevice.h"
#include "../../../device/strategy/strategyDeviceInterface.h"

// SYSTEM
#include "../../../device/system/systemDevice.h"
#include "../../../device/system/systemDeviceInterface.h"

#include "../../../device/test/testDevice.h"
#include "../../../device/test/testDeviceInterface.h"

#include "../../../device/motor/pwmMotorDevice.h"
#include "../../../device/motor/pwmMotorDeviceInterface.h"

#include "../../../drivers/driverStreamListener.h"
#include "../../../drivers/clock/mockClock.h"
#include "../../../drivers/driverList.h"

#include "../../../drivers/dispatcher/dataDispatcherDeviceDriver.h"
#include "../../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../../drivers/dispatcher/i2cDriverDataDispatcher.h"
#include "../../../drivers/test/testDriver.h"

#include "../../../robot/match/startMatchDetector.h"
#include "../../../robot/match/startMatchDetectorDevice.h"
#include "../../../robot/match/startMatchDetectorDeviceInterface.h"
#include "../../../robot/match/pc/startMatchDetectorPc.h"

#include "../../../remote/clock/remoteClock.h"

#include "../../../test/main/motorBoard/motorBoardPc.h"

#include "../../../common/pc/process/processHelper.h"

// Dispatchers
static DriverDataDispatcher driverDataDispatcherListArray[MAIN_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH];

// Dispatcher i2c->Motor
static char motorBoardInputBufferArray[MAIN_BOARD_PC_DATA_MOTOR_BOARD_DISPATCHER_BUFFER_LENGTH];
static Buffer motorBoardInputBuffer;
static InputStream motorBoardInputStream;
static OutputStream motorBoardOutputStream;

// Drivers
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH];

// I2C Debug
static char i2cMasterDebugOutputBufferArray[MAIN_BOARD_PC_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MAIN_BOARD_PC_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// Timers
#define MAIN_BOARD_PC_TIMER_LENGTH    10
static Device timerListArray[MAIN_BOARD_PC_TIMER_LENGTH];

// ConsoleOutputStream
static InputStream consoleInputStream;
static OutputStream consoleOutputStream;

static char consoleInputBufferArray[MAIN_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH];
static Buffer consoleInputBuffer;

static char consoleOutputBufferArray[MAIN_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH];
static Buffer consoleOutputBuffer;

// Eeprom
static Eeprom eeprom;

// Devices
static Device deviceListArray[MAIN_BOARD_PC_DEVICE_LIST_LENGTH];
static Device* testDevice;

// StartMatchDetector
static StartMatchDetector startMatchDetector;

void mainBoardDeviceHandleNotification(const Device* device, const char commandHeader, InputStream* inputStream) {
    appendString(getDebugOutputStreamLogger(), "Notification ! commandHeader=");
    append(getDebugOutputStreamLogger(), commandHeader);
    appendCRLF(getDebugOutputStreamLogger());
    if (commandHeader == NOTIFY_TEST) {
        unsigned char value = readHex2(inputStream);
        appendStringAndDec(getDebugOutputStreamLogger(), "value=", value);
    }
}

void mainBoardWaitForInstruction(void) {

    while (handleNotificationFromDispatcherList(TRANSMIT_I2C)) {
        // loop for all notification
        // notification handler must avoid to directly information in notification callback
        // and never to the call back device
    }

    // delaymSec(MAIN_BOARD_PC_DELAY_CONSOLE_ANALYZE_MILLISECONDS);
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

void runMainBoardPC(void) {
    setPicName(MAIN_BOARD_PC_NAME);
    moveConsole(0, 0, HALF_SCREEN_WIDTH, CONSOLE_HEIGHT);

    // We use http://patorjk.com/software/taag/#p=testall&v=2&f=Acrobatic&t=MOTOR%20BOARD%20PC
    // with Font : Jerusalem
    printf(" __  __    _    ___ _   _    ____   ___    _    ____  ____     ____   ____ \r\n");
    printf("|  \\/  |  / \\  |_ _| \\ | |  | __ ) / _ \\  / \\  |  _ \\|  _ \\   |  _ \\ / ___|\r\n");
    printf("| |\\/| | / _ \\  | ||  \\| |  |  _ \\| | | |/ _ \\ | |_) | | | |  | |_) | |    \r\n");
    printf("| |  | |/ ___ \\ | || |\\  |  | |_) | |_| / ___ \\|  _ <| |_| |  |  __/| |___ \r\n");
    printf("|_|  |_/_/   \\_|___|_| \\_|  |____/ \\___/_/   \\_|_| \\_|____/   |_|    \\____|\r\n");
    printf("\r\n");


    initLog(DEBUG);
    initConsoleInputStream(&consoleInputStream);
    initConsoleOutputStream(&consoleOutputStream);
    addConsoleLogHandler(DEBUG);
    appendStringCRLF(getDebugOutputStreamLogger(), getPicName());

    initEepromPc(&eeprom);

    initTimerList((Timer(*)[]) &timerListArray, MAIN_BOARD_PC_TIMER_LENGTH);

    initBuffer(&consoleInputBuffer, (char(*)[]) &consoleInputBufferArray, MAIN_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH, "inputConsoleBuffer", "IN");
    initBuffer(&consoleOutputBuffer, (char(*)[]) &consoleOutputBufferArray, MAIN_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH, "outputConsoleBuffer", "IN");

    // Dispatchers
    initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, MAIN_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH);
    addLocalDriverDataDispatcher();

    addI2CDriverDataDispatcher("MOTOR_BOARD_DISPATCHER",
    &motorBoardInputBuffer,
    (char(*)[]) &motorBoardInputBufferArray,
    MAIN_BOARD_PC_DATA_MOTOR_BOARD_DISPATCHER_BUFFER_LENGTH,
    &motorBoardOutputStream,
    &motorBoardInputStream,
    MOTOR_BOARD_PC_I2C_ADDRESS);

    // I2C Debug
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
        (char(*)[]) &i2cMasterDebugInputBufferArray,
        MAIN_BOARD_PC_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
        &i2cMasterDebugOutputBuffer,
        (char(*)[]) &i2cMasterDebugOutputBufferArray,
        MAIN_BOARD_PC_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);

    // Init the drivers
    initDrivers(&driverRequestBuffer, (char(*)[]) &driverRequestBufferArray, MAIN_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH,
        &driverResponseBuffer, (char(*)[]) &driverResponseBufferArray, MAIN_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH);

    // Get test driver for debug purpose
    addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);

    // Devices
    initDeviceList((Device(*)[]) &deviceListArray, MAIN_BOARD_PC_DEVICE_LIST_LENGTH);
    // addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());

    testDevice = addI2cRemoteDevice(getTestDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    testDevice->deviceHandleNotification = mainBoardDeviceHandleNotification;

    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());
    addLocalDevice(getStrategyDeviceInterface(), getStrategyDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getDataDispatcherDeviceInterface(), getDataDispatcherDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());
    initStartMatchDetectorPc(&startMatchDetector);
    addLocalDevice(getStartMatchDetectorDeviceInterface(), getStartMatchDetectorDeviceDescriptor(&startMatchDetector));
    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));

    addLocalDevice(getPIDDeviceInterface(), getPIDDeviceDescriptor());
    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getCodersDeviceInterface(), getCodersDeviceDescriptor());
    addLocalDevice(getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
    addLocalDevice(getMotionDeviceInterface(), getMotionDeviceDescriptor());

    initDevices();

    delaymSec(100);

    setDebugI2cEnabled(false);

	if (!pingDriverDataDispatcherList()) {
		printf("PING PROBLEM !");
	}
    // testDriverIntensive(100);

    while (1) {
        mainBoardWaitForInstruction();
    }
}