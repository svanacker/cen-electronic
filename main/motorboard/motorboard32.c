#define _SUPPRESS_PLIB_WARNING
#include <peripheral/i2c.h>
#include <stdlib.h>

// List of available functionality

#include "motorBoard32.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/memoryEeprom.h"

#include "../../common/math/cenMath.h"

#include "../../common/setup/32/picSetup32.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"
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
#include "../../common/serial/serialLinkList.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"

#include "../../common/system/system.h"

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

// IO EXPANDER
#include "../../device/ioExpander/ioExpanderDevice.h"
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"

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
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// I2C
#include "../../device/i2c/i2cCommonDebugDevice.h"
#include "../../device/i2c/i2cCommonDebugDeviceInterface.h"

// I2C Master Device
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// I2C Slave Device
#include "../../device/i2c/slave/i2cSlaveDebugDevice.h"
#include "../../device/i2c/slave/i2cSlaveDebugDeviceInterface.h"

// Motors
#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

// PID
#include "../../motion/pid/pid.h"
#include "../../motion/pid/pidDebug.h"
#include "../../motion/pid/profile/pidMotionProfileComputer.h"
#include "../../device/motion/pid/pidDevice.h"
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/pid/pidDebugDevice.h"
#include "../../device/motion/pid/pidDebugDeviceInterface.h"

// Coders
#include "../../device/motion/position/codersDevice.h"
#include "../../device/motion/position/codersDeviceInterface.h"

// Trajectory
#include "../../device/motion/position/trajectoryDevice.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"

// Motion
#include "../../device/motion/extended/extendedMotionDevice.h"
#include "../../device/motion/extended/extendedMotionDeviceInterface.h"

#include "../../device/motion/simple/motionDevice.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

// Tof
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// Robot
#include "../../robot/kinematics/robotKinematicsDevice.h"
#include "../../robot/kinematics/robotKinematicsDeviceInterface.h"

// Drivers
#include "../../drivers/clock/softClock.h"
#include "../../drivers/clock/PCF8563.h"

// -> IO EXPANDER)
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"
#include "../../drivers/ioExpander/pcf8574.h"

#include "../../drivers/eeprom/24c512.h"

#include "../../drivers/motor/motorDriver.h"

// Direct implementation
#include "../../motion/motion.h"
#include "../../motion/simple/simpleMotion.h"
#include "../../motion/position/trajectory.h"
#include "../../motion/position/coders.h"

// #include "../../test/mathTest.h"
#include "../../test/motion/bspline/bsplinetest.h"

// I2C
static I2cBus i2cBusListArray[MOTOR_BOARD_I2C_BUS_LIST_LENGTH];
static I2cBusConnection i2cBusConnectionListArray[MOTOR_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH];

// I2C Bus
static I2cBus* mainBoardI2cBus;
static I2cBusConnection* mainBoardI2cBusConnection;
static I2cBus* masterI2cBus;
static I2cBusConnection* eepromI2cBusConnection;
static I2cBusConnection* clockI2cBusConnection;
static I2cBusConnection* tofI2cBusConnection;
static I2cBusConnection* ioExpanderBusConnection;

// Eeprom
static Eeprom eeprom_;
// Memory Eeprom
static char memoryEepromArray[MOTOR_BOARD_MEMORY_EEPROM_LENGTH];

// Clock
static Clock clock;

// IO Expander
static IOExpander ioExpander;
static int ioExpanderValue;

// SERIAL
static SerialLink serialLinkListArray[MOTOR_BOARD_SERIAL_LINK_LIST_LENGTH];

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

// Pid Motion
static PidMotion pidMotion;
static PidMotionDefinition motionDefinitionArray[MOTOR_BOARD_PID_MOTION_INSTRUCTION_COUNT];

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

    // Common I2C
    addLocalDevice(getI2cCommonDebugDeviceInterface(), getI2cCommonDebugDeviceDescriptor(mainBoardI2cBusConnection));

    // I2C_1
    addLocalDevice(getI2cSlaveDebugDeviceInterface(), getI2cSlaveDebugDeviceDescriptor(mainBoardI2cBusConnection));

    // I2C_4
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor(mainBoardI2cBusConnection));
    addLocalDevice(getRobotKinematicsDeviceInterface(), getRobotKinematicsDeviceDescriptor(&eeprom_));
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom_));

    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getCodersDeviceInterface(), getCodersDeviceDescriptor());
    addLocalDevice(getPidDeviceInterface(), getPidDeviceDescriptor(&pidMotion));
    addLocalDevice(getPidDebugDeviceInterface(), getPidDebugDeviceDescriptor(&pidMotion));
    addLocalDevice(getExtendedMotionDeviceInterface(), getExtendedMotionDeviceDescriptor(&pidMotion));
    addLocalDevice(getMotionDeviceInterface(), getMotionDeviceDescriptor(&pidMotion));
    addLocalDevice(getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());

    
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(tofI2cBusConnection));

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
    handleInstructionAndMotion(&pidMotion);
}

int runMotorBoard() {
    // configure for multi-vectored mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // enable interrupts
    INTEnableInterrupts();

    setBoardName(MOTOR_BOARD_PIC_NAME);

    initSerialLinkList(&serialLinkListArray, MOTOR_BOARD_SERIAL_LINK_LIST_LENGTH);

    openSerialLink(&standardSerialStreamLink,
            "SERIAL_STANDARD",
            &standardInputBuffer,
            &standardInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &standardOutputBuffer,
            &standardOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            &standardOutputStream,
            MOTOR_BOARD_SERIAL_PORT_STANDARD,
            DEFAULT_SERIAL_SPEED);

    openSerialLink(&debugSerialStreamLink,
            "SERIAL_DEBUG",
            &debugInputBuffer,
            &debugInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            &debugOutputStream,
            MOTOR_BOARD_SERIAL_PORT_DEBUG,
            DEFAULT_SERIAL_SPEED);

    // Init the logs
    initLogs(LOG_LEVEL_DEBUG, (LogHandler(*)[]) &logHandlerListArray, MOTOR_BOARD_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    addLogHandler("UART", &debugOutputStream, LOG_LEVEL_DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);
    appendString(getDebugOutputStreamLogger(), getBoardName());
    appendCRLF(getDebugOutputStreamLogger());

    initTimerList(&timerListArray, MOTOR_BOARD_TIMER_LENGTH);

	// I2c
	initI2cBusList((I2cBus(*)[]) &i2cBusListArray, MOTOR_BOARD_I2C_BUS_LIST_LENGTH);
	initI2cBusConnectionList((I2cBusConnection(*)[]) &i2cBusConnectionListArray, MOTOR_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH);

    mainBoardI2cBus = addI2cBus(I2C_BUS_TYPE_SLAVE, I2C_BUS_PORT_1);
    mainBoardI2cBusConnection = addI2cBusConnection(mainBoardI2cBus, MOTOR_BOARD_I2C_ADDRESS, true);
    openSlaveI2cStreamLink(&i2cSlaveStreamLink,
            &i2cSlaveInputBuffer,
            &i2cSlaveInputBufferArray,
            MOTOR_BOARD_IN_BUFFER_LENGTH,
            &i2cSlaveOutputBuffer,
            &i2cSlaveOutputBufferArray,
            MOTOR_BOARD_OUT_BUFFER_LENGTH,
            // NULL, 
            mainBoardI2cBusConnection
            );

    // Debug of I2C : Only if there is problems
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
        (char(*)[]) &i2cMasterDebugInputBufferArray,
        MOTOR_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
        &i2cMasterDebugOutputBuffer,
        (char(*)[]) &i2cMasterDebugOutputBufferArray,
        MOTOR_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);

    setDebugI2cEnabled(false);

    // I2C Master (PORT 4)
    masterI2cBus = addI2cBus(I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_4);
    i2cMasterInitialize(masterI2cBus);
    
    // EEPROM : If Eeprom is installed
    // eepromI2cBusConnection = addI2cBusConnection(masterI2cBus, ST24C512_ADDRESS_0, true);
    // init24C512Eeprom(&eeprom_, eepromI2cBusConnection);
    
    // EEPROM : If we use Software Eeprom
    initEepromMemory(&eeprom_, &memoryEepromArray, MOTOR_BOARD_MEMORY_EEPROM_LENGTH);
    
    // IO Expander
    ioExpanderBusConnection = addI2cBusConnection(masterI2cBus, PCF8574_ADDRESS_0, true);
    initIOExpanderPCF8574(&ioExpander, ioExpanderBusConnection);
    
    // TOF
    tofI2cBusConnection = addI2cBusConnection(masterI2cBus, VL530X_ADDRESS_0, true);

    // Clock
    // -> Clock
    clockI2cBusConnection = addI2cBusConnection(masterI2cBus, PCF8563_WRITE_ADDRESS, true);
    initClockPCF8563(&clock, clockI2cBusConnection);

    // PidMotion
    initPidMotion(&pidMotion, &eeprom_, (PidMotionDefinition(*)[]) &motionDefinitionArray, MOTOR_BOARD_PID_MOTION_INSTRUCTION_COUNT);

    // initSoftClock(&clock);

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
