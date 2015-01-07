#include "motorBoardPc.h"

#include <stdlib.h>
#include <stdio.h>

#include "../../../common/clock/clock.h"
#include "../../../common/delay/cenDelay.h"
#include "../../../common/eeprom/pc/eepromPc.h"
#include "../../../common/error/error.h"
#include "../../../common/i2c/i2cDebug.h"
#include "../../../common/i2c/slave/pc/i2cSlavePc.h"
#include "../../../common/i2c/slave/pc/i2cSlaveSetupPc.h"
#include "../../../common/i2c/slave/i2cSlaveLink.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/io/pc/consoleInputStream.h"
#include "../../../common/io/filter.h"
#include "../../../common/io/streamLink.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/log/pc/consoleLogHandler.h"

#include "../../../common/timer/timerList.h"


#include "../../../device/device.h"
#include "../../../device/deviceList.h"

// I2C -> Slave
#include "../../../device/i2c/slave/i2cSlaveDebugDevice.h"
#include "../../../device/i2c/slave/i2cSlaveDebugDeviceInterface.h"

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

// SYSTEM
#include "../../../device/system/systemDevice.h"
#include "../../../device/system/systemDeviceInterface.h"

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

#include "../../../common/pc/process/processHelper.h"

// Dispatchers
static DriverDataDispatcher driverDataDispatcherListArray[MOTOR_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH];

// Timers
static Device timerListArray[MOTOR_BOARD_PC_TIMER_LENGTH];

// ConsoleOutputStream
static InputStream consoleInputStream;
static OutputStream consoleOutputStream;
static char consoleInputBufferArray[MOTOR_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH];
static Buffer consoleInputBuffer;
static char consoleOutputBufferArray[MOTOR_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH];
static Buffer consoleOutputBuffer;

// i2c Link
static char i2cSlaveInputBufferArray[MOTOR_BOARD_PC_IN_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MOTOR_BOARD_PC_OUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSlaveStreamLink;

static char i2cSlaveDebugOutputBufferArray[MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_OUT_BUFFER_LENGTH];
static Buffer i2cSlaveDebugOutputBuffer;
static char i2cSlaveDebugInputBufferArray[MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_IN_BUFFER_LENGTH];
static Buffer i2cSlaveDebugInputBuffer;

// Eeprom
static Eeprom eeprom;

// Devices
static Device deviceListArray[MOTOR_BOARD_PC_DEVICE_LIST_LENGTH];

void motorBoardWaitForInstruction(void) {

    // delaymSec(MOTOR_BOARD_PC_DELAY_CONSOLE_ANALYZE_MILLISECONDS);

    // Analyze data from the Console (Specific to PC)
    while (consoleInputStream.availableData(&consoleInputStream)) {
        unsigned char c = consoleInputStream.readChar(&consoleInputStream);
        consoleInputBuffer.outputStream.writeChar(&(consoleInputBuffer.outputStream), c);
        if (c == 13) {
            appendCRLF(&consoleOutputStream);
        }
        consoleOutputStream.writeChar(&consoleOutputStream, c);
    }

    // Analyse from the ConsoleBuffer
    handleStreamInstruction(
        &consoleInputBuffer,
        &consoleOutputBuffer,
        &consoleOutputStream,
        &filterRemoveCRLF,
        NULL);


    // Analyse data from the I2C
    handleStreamInstruction(
        &i2cSlaveInputBuffer,
        &i2cSlaveOutputBuffer,
        NULL,
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

    openSlaveI2cStreamLink(&i2cSlaveStreamLink,
        &i2cSlaveInputBuffer,
        (char(*)[]) &i2cSlaveInputBufferArray,
        MOTOR_BOARD_PC_IN_BUFFER_LENGTH,
        &i2cSlaveOutputBuffer,
        (char(*)[]) &i2cSlaveOutputBufferArray,
        MOTOR_BOARD_PC_OUT_BUFFER_LENGTH,
        MOTOR_BOARD_PC_I2C_ADDRESS
    );

    // I2C Debug
    initI2CDebugBuffers(&i2cSlaveDebugInputBuffer,
        (char(*)[]) &i2cSlaveDebugInputBufferArray,
        MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_IN_BUFFER_LENGTH,
        &i2cSlaveDebugOutputBuffer,
        (char(*)[]) &i2cSlaveDebugOutputBufferArray,
        MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_OUT_BUFFER_LENGTH);

    initEepromPc(&eeprom);

    // Devices
    initDeviceList((Device(*)[]) &deviceListArray, MOTOR_BOARD_PC_DEVICE_LIST_LENGTH);
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getI2cSlaveDebugDeviceInterface(), getI2cSlaveDebugDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());

    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getPIDDeviceInterface(), getPIDDeviceDescriptor());
    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getCodersDeviceInterface(), getCodersDeviceDescriptor());
    addLocalDevice(getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
    addLocalDevice(getMotionDeviceInterface(), getMotionDeviceDescriptor());

    initDevices();

    setDebugI2cEnabled(false);
    while (1) {
        motorBoardWaitForInstruction();
    }
}