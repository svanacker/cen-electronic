#include "motorBoardPc.h"

#include <stdlib.h>
#include <stdio.h>

#include "../../common/clock/clock.h"
#include "../../common/delay/cenDelay.h"
#include "../../common/eeprom/pc/eepromPc.h"
#include "../../common/error/error.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"
#include "../../common/i2c/pc/i2cCommonPc.h"
#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/slave/pc/i2cSlavePc.h"
#include "../../common/i2c/slave/pc/i2cSlaveSetupPc.h"
#include "../../common/i2c/slave/i2cSlaveLink.h"
#include "../../common/io/pc/consoleOutputStream.h"
#include "../../common/io/pc/consoleInputStream.h"
#include "../../common/io/filter.h"
#include "../../common/io/streamLink.h"
#include "../../common/io/pc/consoleOutputStream.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/pc/consoleLogHandler.h"
#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"
#include "../../common/serial/serialLinkList.h"

#include "../../common/system/system.h"

#include "../../common/timer/timerList.h"


#include "../../device/device.h"
#include "../../device/deviceList.h"

// I2C
#include "../../device/i2c/i2cCommonDebugDevice.h"
#include "../../device/i2c/i2cCommonDebugDeviceInterface.h"

// I2C -> Slave
#include "../../device/i2c/slave/i2cSlaveDebugDevice.h"
#include "../../device/i2c/slave/i2cSlaveDebugDeviceInterface.h"

// BATTERY
#include "../../device/battery/batteryDevice.h"
#include "../../device/battery/batteryDeviceInterface.h"

// CLOCK
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// LOG
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// TIMERS
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// KINEMATICS
#include "../../robot/kinematics/robotKinematicsDevice.h"
#include "../../robot/kinematics/robotKinematicsDeviceInterface.h"

// MOTION

#include "../../device/motion/extended/extendedMotionDevice.h"
#include "../../device/motion/extended/extendedMotionDeviceInterface.h"

#include "../../device/motion/pid/pidDevice.h"
#include "../../device/motion/pid/pidDeviceInterface.h"

#include "../../device/motion/position/codersDevice.h"
#include "../../device/motion/position/codersDeviceInterface.h"

#include "../../device/motion/position/trajectoryDevice.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"

#include "../../device/motion/simple/motionDevice.h"
#include "../../device/motion/simple/motionDeviceInterface.h"


#include "../../device/motion/simulation/motionSimulationDevice.h"
#include "../../device/motion/simulation/motionSimulationDeviceInterface.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/driverList.h"
#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../drivers/test/testDriver.h"

#include "../../drivers/battery/battery.h"
#include "../../drivers/clock/softClock.h"

#include "../../motion/motion.h"
#include "../../motion/pid/pidMotion.h"

#include "../../common/pc/process/processHelper.h"

#include "../../main/mainBoard/mainBoardPc.h"

// Logs
static LogHandlerList logHandlerListArray[MOTOR_BOARD_PC_LOG_HANDLER_LIST_LENGTH];

// Dispatchers
static DriverDataDispatcher driverDataDispatcherListArray[MOTOR_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH];

// SERIAL
static SerialLink serialLinkListArray[MOTOR_BOARD_PC_SERIAL_LINK_LIST_LENGTH];

// I2C
static I2cBus i2cBusListArray[MOTOR_BOARD_PC_I2C_BUS_LIST_LENGTH];
static I2cBusConnection i2cBusConnectionListArray[MOTOR_BOARD_PC_I2C_BUS_LIST_LENGTH];

// Timers
static Timer timerListArray[MOTOR_BOARD_PC_TIMER_LENGTH];

// Logs

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

// Battery
static Battery battery;

// Clock
static Clock clock;

// I2C
static I2cBus* motorI2cBus;
static I2cBusConnection* motorI2cBusConnection;
static I2cBusConnectionPc motorI2cBusConnectionPc;

// Devices
static Device deviceListArray[MOTOR_BOARD_PC_DEVICE_LIST_LENGTH];

// Pid Motion
static PidMotion pidMotion;
static PidMotionDefinition motionDefinitionArray[MOTOR_BOARD_PC_PID_MOTION_INSTRUCTION_COUNT];

static bool singleModeActivated = true;

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

    if (!singleModeActivated) {
        // Analyse data from the I2C
        handleStreamInstruction(
            &i2cSlaveInputBuffer,
            &i2cSlaveOutputBuffer,
            NULL,
            &filterRemoveCRLF,
            NULL);
    }

    handleInstructionAndMotion(&pidMotion);
}

void runMotorBoardPC(bool singleMode) {
    singleModeActivated = singleMode;
    setBoardName(MOTOR_BOARD_PC_NAME);
	setConsoleSizeAndBuffer(CONSOLE_CHARS_WIDTH, CONSOLE_CHARS_HEIGHT, CONSOLE_BUFFER_WIDTH, CONSOLE_BUFFER_HEIGHT);
    moveConsole(HALF_SCREEN_WIDTH, 0, HALF_SCREEN_WIDTH, CONSOLE_HEIGHT / 2);

    // We use http://patorjk.com/software/taag/#p=testall&v=2&f=Acrobatic&t=MOTOR%20BOARD%20PC
    // with Font : Jerusalem
    printf(" __  __  ___ _____ ___  ____     ____   ___    _    ____  ____     ____   ____\r\n");
    printf("|  \\/  |/ _ |_   _/ _ \\|  _ \\   | __ ) / _ \\  / \\  |  _ \\|  _ \\   |  _ \\ / ___|\r\n");
    printf("| |\\/| | | | || || | | | |_) |  |  _ \\| | | |/ _ \\ | |_) | | | |  | |_) | |    \r\n");
    printf("| |  | | |_| || || |_| |  _ <   | |_) | |_| / ___ \\|  _ <| |_| |  |  __/| |___ \r\n");
    printf("|_|  |_|\\___/ |_| \\___/|_| \\_\\  |____/ \\___/_/   \\_|_| \\_|____/   |_|    \\____|\r\n");

    initLogs(LOG_LEVEL_DEBUG, (LogHandler(*)[]) &logHandlerListArray, MOTOR_BOARD_PC_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    initConsoleInputStream(&consoleInputStream);
    initConsoleOutputStream(&consoleOutputStream);
    addConsoleLogHandler(LOG_LEVEL_DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);

	initSerialLinkList((SerialLink(*)[]) &serialLinkListArray, MOTOR_BOARD_PC_SERIAL_LINK_LIST_LENGTH);

    initTimerList((Timer(*)[]) &timerListArray, MOTOR_BOARD_PC_TIMER_LENGTH);

    initBuffer(&consoleInputBuffer, (char(*)[]) &consoleInputBufferArray, MOTOR_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH, "inputConsoleBuffer", "IN");
    initBuffer(&consoleOutputBuffer, (char(*)[]) &consoleOutputBufferArray, MOTOR_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH, "outputConsoleBuffer", "IN");

    // Dispatchers
    initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, MOTOR_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH);
    addLocalDriverDataDispatcher();

    if (!singleModeActivated) {
		// I2c
		initI2cBusList((I2cBus(*)[]) &i2cBusListArray, MOTOR_BOARD_PC_I2C_BUS_LIST_LENGTH);
        initI2cBusConnectionList((I2cBusConnection(*)[]) &i2cBusConnectionListArray, MOTOR_BOARD_PC_I2C_BUS_CONNECTION_LIST_LENGTH);
        motorI2cBus = addI2cBus(I2C_BUS_TYPE_SLAVE, I2C_BUS_PORT_1);
        
        motorI2cBusConnection = addI2cBusConnection(motorI2cBus, MOTOR_BOARD_PC_I2C_ADDRESS, false);
        motorI2cBusConnection->i2cBus = motorI2cBus;
        motorI2cBusConnectionPc.i2cPipeMasterName = MAIN_BOARD_TO_MOTOR_BOARD_PC_PIPE_I2C_MASTER_NAME;
        motorI2cBusConnectionPc.i2cPipeSlaveName = MOTOR_BOARD_PC_PIPE_I2C_SLAVE_NAME;
        motorI2cBusConnection->object = &motorI2cBusConnectionPc;
		openSlaveI2cStreamLink(&i2cSlaveStreamLink,
            &i2cSlaveInputBuffer,
            (char(*)[]) &i2cSlaveInputBufferArray,
            MOTOR_BOARD_PC_IN_BUFFER_LENGTH,
            &i2cSlaveOutputBuffer,
            (char(*)[]) &i2cSlaveOutputBufferArray,
            MOTOR_BOARD_PC_OUT_BUFFER_LENGTH,
            motorI2cBusConnection
        );
        // I2C Debug
        initI2CDebugBuffers(&i2cSlaveDebugInputBuffer,
            (char(*)[]) &i2cSlaveDebugInputBufferArray,
            MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_IN_BUFFER_LENGTH,
            &i2cSlaveDebugOutputBuffer,
            (char(*)[]) &i2cSlaveDebugOutputBufferArray,
            MOTOR_BOARD_PC_I2C_DEBUG_SLAVE_OUT_BUFFER_LENGTH);
	}

    // Eeprom
    initEepromPc(&eeprom, "TODO");

    // Battery
    initBattery(&battery, getBatteryVoltage);
	
    // Clock
    initSoftClock(&clock);

	// Pid Motion
	initPidMotion(&pidMotion, &eeprom, (PidMotionDefinition(*)[]) &motionDefinitionArray, MOTOR_BOARD_PC_PID_MOTION_INSTRUCTION_COUNT);

    // Devices
    initDeviceList((Device(*)[]) &deviceListArray, MOTOR_BOARD_PC_DEVICE_LIST_LENGTH);
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
	addLocalDevice(getI2cCommonDebugDeviceInterface(), getI2cCommonDebugDeviceDescriptor());
    addLocalDevice(getI2cSlaveDebugDeviceInterface(), getI2cSlaveDebugDeviceDescriptor(motorI2cBusConnection));
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
	addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());

    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getBatteryDeviceInterface(), getBatteryDeviceDescriptor(&battery));
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getRobotKinematicsDeviceInterface(), getRobotKinematicsDeviceDescriptor(&eeprom));

    addLocalDevice(getPIDDeviceInterface(), getPIDDeviceDescriptor(&pidMotion));
    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getCodersDeviceInterface(), getCodersDeviceDescriptor());
    addLocalDevice(getTrajectoryDeviceInterface(), getTrajectoryDeviceDescriptor());
    addLocalDevice(getMotionDeviceInterface(), getMotionDeviceDescriptor(&pidMotion));
	addLocalDevice(getExtendedMotionDeviceInterface(), getExtendedMotionDeviceDescriptor(&pidMotion));
	addLocalDevice(getMotionSimulationDeviceInterface(), getMotionSimulationDeviceDescriptor());
	addLocalDevice(getRobotKinematicsDeviceInterface(), getRobotKinematicsDeviceDescriptor(&eeprom));

    initDevices();

    startTimerList();

    setDebugI2cEnabled(false);
    while (1) {
        motorBoardWaitForInstruction();
    }
}