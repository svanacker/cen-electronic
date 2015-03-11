#include <peripheral/i2c.h>
#include <stdlib.h>

// List of available functionality

#include "motorBoard.h"

#include "../../common/commons.h"
#include "../../common/2d/2d.h"
#include "../../common/math/cenMath.h"

#include "../../common/setup/32/picSetup32.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/master/i2cMasterSetup.h"
#include "../../common/i2c/slave/i2cSlave.h"
#include "../../common/i2c/slave/i2cSlaveSetup.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"

#include "../../common/io/filter.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/printWriter.h"

#include "../../common/pwm/pwmPic.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/deviceList.h"
#include "../../device/transmitMode.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"

#include "../../drivers/driverStreamListener.h"

// -> Devices

// Clock
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// FILE
#include "../../device/file/fileDevice.h"
#include "../../device/file/fileDeviceInterface.h"

// Test
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// Serial
#include "../../device/serial/serialDebugDevice.h"
#include "../../device/serial/serialDebugDeviceInterface.h"

// System
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// Timer
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// Log
//#include "../../device/log/logDevice.h"
//#include "../../device/log/logDeviceInterface.h"

// I2C Slave Device/
#include "../../device/i2c/slave/i2cSlaveDebugDevice.h"
#include "../../device/i2c/slave/i2cSlaveDebugDeviceInterface.h"

// Motors
#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

// PID
#include "../../motion/pid/pid.h"
#include "../../motion/pid/pidDebug.h"
#include "../../motion/pid/pidMotionProfileComputer.h"
#include "../../device/motion/pid/pidDevice.h"
#include "../../device/motion/pid/pidDeviceInterface.h"

// Coders
#include "../../device/motion/position/codersDevice.h"
#include "../../device/motion/position/codersDeviceInterface.h"

// Trajectory
#include "../../device/motion/position/trajectoryDevice.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"

// Motion
#include "../../device/motion/simple/motionDevice.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

// Drivers
#include "../../drivers/clock/softClock.h"
#include "../../drivers/eeprom/24c512.h"

#include "../../drivers/motor/motorDriver.h"

// Direct implementation
#include "../../motion/simple/motion.h"
#include "../../motion/position/trajectory.h"
#include "../../motion/position/coders.h"

// #include "../../test/mathTest.h"
#include "../../test/motion/bspline/bsplinetest.h"

// The port used to send instruction if we connect MainBoard and MotorBoard via RS232
#define SERIAL_PORT_STANDARD  SERIAL_PORT_1

// The port for which we debug (we can send instruction too)
#define SERIAL_PORT_DEBUG     SERIAL_PORT_2

// I2C Bus
static I2cBus mainBoardI2cBus;
static I2cBus eepromI2cBus;

// Eeprom
static Eeprom eeprom_;

// Clock
static Clock clock;

// serial INSTRUCTION
static char standardInputBufferArray[MOTOR_BOARD_IN_BUFFER_LENGTH];
static Buffer standardInputBuffer;
static char standardOutputBufferArray[MOTOR_BOARD_OUT_BUFFER_LENGTH];
static Buffer standardOutputBuffer;
static OutputStream standardOutputStream;
static StreamLink standardSerialStreamLink;

// serial DEBUG 
static char debugInputBufferArray[MOTOR_BOARD_IN_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MOTOR_BOARD_OUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// logs
static LogHandler logHandlerListArray[MOTOR_BOARD_LOG_HANDLER_LIST_LENGTH];

// i2c Link
static char i2cSlaveInputBufferArray[MOTOR_BOARD_IN_BUFFER_LENGTH];
static Buffer i2cSlaveInputBuffer;
static char i2cSlaveOutputBufferArray[MOTOR_BOARD_OUT_BUFFER_LENGTH];
static Buffer i2cSlaveOutputBuffer;
static StreamLink i2cSlaveStreamLink;

// I2C Debug
static char i2cMasterDebugOutputBufferArray[MOTOR_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MOTOR_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// Timers
static Timer timerListArray[MOTOR_BOARD_TIMER_LENGTH];
int currentTimeInSecond;
bool currentTimeChanged;

#define MOTOR_BOARD_PIC_NAME "MOTOR BOARD 32"

Buffer* getI2CSlaveOutputBuffer() {
    return &i2cSlaveOutputBuffer;
}

// I2C Debug
/*
static Buffer debugI2cInputBuffer;
static Buffer debugI2cOutputBuffer;
 */

// Devices
static Device deviceListArray[MOTOR_BOARD_DEVICE_LIST_LENGTH];

void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MOTOR_BOARD_DEVICE_LIST_LENGTH);

    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getCodersDeviceInterface(), getCodersDeviceDescriptor());
    addLocalDevice(getPIDDeviceInterface(), getPIDDeviceDescriptor(&eeprom_));
    addLocalDevice(getMotionDeviceInterface(), getMotionDeviceDescriptor(&eeprom_));
    addLocalDevice(getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());

    // I2C_4
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom_));
    addLocalDevice(getFileDeviceInterface(), getFileDeviceDescriptor());


//    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
//    addLocalDevice(getI2cSlaveDebugDeviceInterface(), getI2cSlaveDebugDeviceDescriptor());


    initDevices();
}

void waitForInstruction() {
    // I2C Stream
    handleStreamInstruction(&i2cSlaveInputBuffer, &i2cSlaveOutputBuffer, NULL, &filterRemoveCRLF, NULL);

    // STANDARD UART Stream
    handleStreamInstruction(&standardInputBuffer, &standardOutputBuffer, &standardOutputStream, &filterRemoveCRLF, NULL);

    // DEBUG UART Stream
    handleStreamInstruction(&debugInputBuffer, &debugOutputBuffer, &debugOutputStream, &filterRemoveCRLF, NULL);

    // Manage Motion
    handleInstructionAndMotion();
}



int runMotorBoard() {
    // configure for multi-vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // enable interrupts
    INTEnableInterrupts();

    setPicName(MOTOR_BOARD_PIC_NAME);

    delaymSec(100);

    openSerialLink(&standardSerialStreamLink,
            &standardInputBuffer,
            &standardInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &standardOutputBuffer,
            &standardOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            &standardOutputStream,
            SERIAL_PORT_STANDARD,
            DEFAULT_SERIAL_SPEED);

    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG,
            DEFAULT_SERIAL_SPEED);

    // Init the logs
    initLogs(DEBUG, (LogHandler(*)[]) &logHandlerListArray, MOTOR_BOARD_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    addLogHandler("UART", &debugOutputStream, DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);
    appendString(getDebugOutputStreamLogger(), getPicName());
    appendCRLF(getDebugOutputStreamLogger());

    initTimerList(&timerListArray, MOTOR_BOARD_TIMER_LENGTH);

    // TODO : Replace by an init I2cBus
    mainBoardI2cBus.portIndex = I2C_BUS_PORT_1;
    openSlaveI2cStreamLink(&i2cSlaveStreamLink,
            &i2cSlaveInputBuffer,
            &i2cSlaveInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &i2cSlaveOutputBuffer,
            &i2cSlaveOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            // NULL, 
            &mainBoardI2cBus,
            MOTOR_BOARD_I2C_ADDRESS
            );

    // Debug of I2C : Only if there is problems
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
        (char(*)[]) &i2cMasterDebugInputBufferArray,
        MOTOR_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
        &i2cMasterDebugOutputBuffer,
        (char(*)[]) &i2cMasterDebugOutputBufferArray,
        MOTOR_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);

    setDebugI2cEnabled(false);

    // Eeprom
    eepromI2cBus.portIndex = I2C_BUS_PORT_4;
    i2cMasterInitialize(&eepromI2cBus);
    init24C512Eeprom(&eeprom_, &eepromI2cBus);

    // Clock
    initSoftClock(&clock);

    // init the devices
    initDevicesDescriptor();

    // Init the timers management
    startTimerList();

    while (1) {
        waitForInstruction();
    }
}

int main(void) {
    runMotorBoard();

    return (0);
}
