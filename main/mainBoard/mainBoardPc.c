#include "mainBoardPc.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#include "../../common/clock/clock.h"
#include "../../common/delay/cenDelay.h"
#include "../../common/eeprom/pc/eepromPc.h"
#include "../../common/error/error.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/filter.h"
#include "../../common/io/pc/consoleOutputStream.h"
#include "../../common/io/pc/consoleInputStream.h"
#include "../../common/io/pc/consoleOutputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/streamLink.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/pc/consoleLogHandler.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/system/system.h"

#include "../../common/timer/timerList.h"


#include "../../device/device.h"
#include "../../device/deviceList.h"
#include "../../device/transmitMode.h"

// BATTERY
#include "../../device/battery/batteryDevice.h"
#include "../../device/battery/batteryDeviceInterface.h"

// CLOCK
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// DISPATCHER DEVICE
#include "../../device/dispatcher/dataDispatcherDevice.h"
#include "../../device/dispatcher/dataDispatcherDeviceInterface.h"

// I2C Common
#include "../../device/i2c/i2cCommonDebugDevice.h"
#include "../../device/i2c/i2cCommonDebugDeviceInterface.h"

// I2C -> Master
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// CONFIG
#include "../../robot/config/pc/robotConfigPc.h"
#include "../../robot/config/robotConfigDevice.h"
#include "../../robot/config/robotConfigDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// FILE
// #include "../../device/file/fileDevice.h"
// #include "../../device/file/fileDeviceInterface.h"

// KINEMATICS
#include "../../robot/kinematics/robotKinematicsDeviceInterface.h"

// ADC
#include "../../device/adc/adcDevice.h"
#include "../../device/adc/adcDeviceInterface.h"

// LCD
#include "../../device/lcd/lcdDevice.h"
#include "../../device/lcd/lcdDeviceInterface.h"

// LOGS
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// MOTION
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/position/codersDeviceInterface.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"
#include "../../device/motion/simple/motionDeviceInterface.h"
#include "../../device/motion/simulation/motionSimulationDeviceInterface.h"

// NAVIGATION
#include "../../device/navigation/navigationDevice.h"
#include "../../device/navigation/navigationDeviceInterface.h"

// PWM
#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

// SENSOR->TEMPERATURE
#include "../../device/sensor/temperature/temperatureSensor.h"
#include "../../device/sensor/temperature/temperatureSensorDevice.h"
#include "../../device/sensor/temperature/temperatureSensorDeviceInterface.h"

// SERVO
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// STRATEGY
#include "../../device/strategy/strategyDevice.h"
#include "../../device/strategy/strategyDeviceInterface.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// TEST
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// TIMER
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/clock/pc/pcClock.h"
#include "../../drivers/driverList.h"

#include "../../drivers/dispatcher/dataDispatcherDeviceDriver.h"
#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../drivers/dispatcher/i2cDriverDataDispatcher.h"
#include "../../drivers/file/eeprom/eepromFile.h"
#include "../../drivers/test/testDriver.h"
#include "../../drivers/sensor/temperature/pc/temperaturePc.h"

#include "../../robot/match/startMatch.h"
#include "../../robot/match/startMatchDevice.h"
#include "../../robot/match/startMatchDeviceInterface.h"
#include "../../robot/match/pc/startMatchDetectorPc.h"

#include "../../remote/clock/remoteClock.h"

#include "../../main/motorBoard/motorBoardPc.h"

#include "../../common/pc/process/processHelper.h"

// Logs
static LogHandler logHandlerListArray[MAIN_BOARD_PC_LOG_HANDLER_LIST_LENGTH];

// Robot Manager Link
#define SERIAL_PORT_ROBOT_MANAGER       SERIAL_PORT_1
static char robotManagerInputBufferArray[ROBOT_MANAGER_INPUT_BUFFER_LENGTH];
static Buffer robotManagerInputBuffer;
static char robotManagerOutputBufferArray[ROBOT_MANAGER_OUTPUT_BUFFER_LENGTH];
static Buffer robotManagerOutputBuffer;
static OutputStream robotManagerOutputStream;
static StreamLink robotManagerSerialStreamLink;

// Dispatchers
static DriverDataDispatcher driverDataDispatcherListArray[MAIN_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH];

// I2C
static I2cBus i2cBusListArray[MAIN_BOARD_I2C_BUS_LIST_LENGTH];

// Dispatcher i2c->Motor
static I2cBus* motorBoardI2cBus;
static I2cBusConnection motorBoardI2cBusConnection;
static char motorBoardInputBufferArray[MAIN_BOARD_PC_DATA_MOTOR_BOARD_DISPATCHER_BUFFER_LENGTH];
static Buffer motorBoardInputBuffer;
static InputStream motorBoardInputStream;
static OutputStream motorBoardOutputStream;

// Drivers
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH];

// Eeprom
static Eeprom eeprom;

// Clock
static Clock clock;

// Temperature
static Temperature temperature;

// RobotConfig
static RobotConfig robotConfig;

// I2C Debug
static char i2cMasterDebugOutputBufferArray[MAIN_BOARD_PC_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MAIN_BOARD_PC_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// Timers
static Timer timerListArray[MAIN_BOARD_PC_TIMER_LENGTH];

// ConsoleOutputStream
static InputStream consoleInputStream;
static OutputStream consoleOutputStream;

static char consoleInputBufferArray[MAIN_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH];
static Buffer consoleInputBuffer;

static char consoleOutputBufferArray[MAIN_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH];
static Buffer consoleOutputBuffer;

// Devices
static Device deviceListArray[MAIN_BOARD_PC_DEVICE_LIST_LENGTH];
static Device* testDevice;

// StartMatch
static StartMatch startMatch;

static bool connectToRobotManager = false;

void mainBoardDeviceHandleNotification(const Device* device, const char commandHeader, InputStream* inputStream) {
    appendString(getDebugOutputStreamLogger(), "Notification ! commandHeader=");
    append(getDebugOutputStreamLogger(), commandHeader);
    appendCRLF(getDebugOutputStreamLogger());
    if (commandHeader == NOTIFY_TEST) {
        unsigned char value = readHex2(inputStream);
        appendStringAndDec(getDebugOutputStreamLogger(), "value=", value);
    }
}

bool mainBoardPcWaitForInstruction(StartMatch* startMatch) {
	/*
    while (handleNotificationFromDispatcherList(TRANSMIT_I2C)) {
        // loop for all notification
        // notification handler must avoid to directly information in notification callback
        // and never to the call back device
    }
	*/

    // delaymSec(MAIN_BOARD_PC_DELAY_CONSOLE_ANALYZE_MILLISECONDS);

    // Fill Console Buffer
    while (consoleInputStream.availableData(&consoleInputStream)) {
        unsigned char c = consoleInputStream.readChar(&consoleInputStream);
        consoleInputBuffer.outputStream.writeChar(&(consoleInputBuffer.outputStream), c);
        if (c == 13) {
            appendCRLF(&consoleOutputStream);
        }
        consoleOutputStream.writeChar(&consoleOutputStream, c);
    }

    // From Text Console
    handleStreamInstruction(
        &consoleInputBuffer,
        &consoleOutputBuffer,
        &consoleOutputStream,
        &filterRemoveCRLF,
        NULL);

    if (connectToRobotManager) {
        // From RobotManager
        handleStreamInstruction(
            &robotManagerInputBuffer,
            &robotManagerOutputBuffer,
            &robotManagerOutputStream,
            &filterRemoveCRLF,
            NULL);
    }

    return true;
}

void runMainBoardPC(bool connectToRobotManagerMode) {
    connectToRobotManager = connectToRobotManagerMode;
    setBoardName(MAIN_BOARD_PC_NAME);
	setConsoleSizeAndBuffer(CONSOLE_CHARS_WIDTH, CONSOLE_CHARS_HEIGHT, CONSOLE_BUFFER_WIDTH, CONSOLE_BUFFER_HEIGHT);
    moveConsole(0, 0, HALF_SCREEN_WIDTH, CONSOLE_HEIGHT);

    // We use http://patorjk.com/software/taag/#p=testall&v=2&f=Acrobatic&t=MOTOR%20BOARD%20PC
    // with Font : Jerusalem
    printf(" __  __    _    ___ _   _    ____   ___    _    ____  ____     ____   ____ \r\n");
    printf("|  \\/  |  / \\  |_ _| \\ | |  | __ ) / _ \\  / \\  |  _ \\|  _ \\   |  _ \\ / ___|\r\n");
    printf("| |\\/| | / _ \\  | ||  \\| |  |  _ \\| | | |/ _ \\ | |_) | | | |  | |_) | |    \r\n");
    printf("| |  | |/ ___ \\ | || |\\  |  | |_) | |_| / ___ \\|  _ <| |_| |  |  __/| |___ \r\n");
    printf("|_|  |_/_/   \\_|___|_| \\_|  |____/ \\___/_/   \\_|_| \\_|____/   |_|    \\____|\r\n");
    printf("\r\n");


    initLogs(DEBUG, (LogHandler(*)[]) &logHandlerListArray, MAIN_BOARD_PC_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    initConsoleInputStream(&consoleInputStream);
    initConsoleOutputStream(&consoleOutputStream);
    addConsoleLogHandler(DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);
    appendStringCRLF(getDebugOutputStreamLogger(), getBoardName());


    initTimerList((Timer(*)[]) &timerListArray, MAIN_BOARD_PC_TIMER_LENGTH);

    initBuffer(&consoleInputBuffer, (char(*)[]) &consoleInputBufferArray, MAIN_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH, "inputConsoleBuffer", "IN");
    initBuffer(&consoleOutputBuffer, (char(*)[]) &consoleOutputBufferArray, MAIN_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH, "outputConsoleBuffer", "IN");

    // Dispatchers
    initDriverDataDispatcherList((DriverDataDispatcher(*)[]) &driverDataDispatcherListArray, MAIN_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH);
    addLocalDriverDataDispatcher();

	// I2c
	initI2cBusList((I2cBus(*)[]) &i2cBusListArray, MAIN_BOARD_I2C_BUS_LIST_LENGTH);
	motorBoardI2cBus = addI2cBus(I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_1);
    initI2cBusConnection(&motorBoardI2cBusConnection, motorBoardI2cBus, MOTOR_BOARD_PC_I2C_ADDRESS);

    addI2CDriverDataDispatcher("MOTOR_BOARD_DISPATCHER",
        &motorBoardInputBuffer,
        (char(*)[]) &motorBoardInputBufferArray,
        MAIN_BOARD_PC_DATA_MOTOR_BOARD_DISPATCHER_BUFFER_LENGTH,
        &motorBoardOutputStream,
        &motorBoardInputStream,
        &motorBoardI2cBusConnection
    );

    if (connectToRobotManager) {
        // Open the serial Link between RobotManager (C# Project) and the MainBoardPc
        openSerialLink(&robotManagerSerialStreamLink,
            &robotManagerInputBuffer,
            (char(*)[]) &robotManagerInputBufferArray,
            ROBOT_MANAGER_INPUT_BUFFER_LENGTH,
            &robotManagerOutputBuffer,
            (char(*)[]) &robotManagerOutputBufferArray,
            ROBOT_MANAGER_OUTPUT_BUFFER_LENGTH,
            &robotManagerOutputStream,
            SERIAL_PORT_ROBOT_MANAGER,
            0);
    }

    // CONFIG
    initRobotConfigPc(&robotConfig);

    // EEPROM
    initEepromPc(&eeprom, "TODO");
    initEepromFile(&eeprom);

    // Clock
    initPcClock(&clock);

    // Temperature
    initTemperaturePc(&temperature);

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

    // LOCAL BOARD
    addLocalDevice(getADCDeviceInterface(), getADCDeviceDescriptor());
    addLocalDevice(getStrategyDeviceInterface(), getStrategyDeviceDescriptor());
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor(&robotConfig));
    addLocalDevice(getI2cCommonDebugDeviceInterface(), getI2cCommonDebugDeviceDescriptor());
	addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());
    addLocalDevice(getDataDispatcherDeviceInterface(), getDataDispatcherDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    // addLocalDevice(getFileDeviceInterface(), getFileDeviceDescriptor());
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    addLocalDevice(getTemperatureSensorDeviceInterface(), getTemperatureSensorDeviceDescriptor(&temperature));
    addLocalDevice(getNavigationDeviceInterface(), getNavigationDeviceDescriptor());

    initStartMatch(&startMatch, isMatchStartedPc, mainBoardPcWaitForInstruction, &eeprom);
    addLocalDevice(getStartMatchDeviceInterface(), getStartMatchDeviceDescriptor(&startMatch));
 
    // MOTOR BOARD
    addI2cRemoteDevice(getBatteryDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    // addI2cRemoteDevice(getEepromDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    addI2cRemoteDevice(getPIDDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    addI2cRemoteDevice(getMotorDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    addI2cRemoteDevice(getCodersDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    addI2cRemoteDevice(getTrajectoryDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    addI2cRemoteDevice(getMotionDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    addI2cRemoteDevice(getRobotKinematicsDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    addI2cRemoteDevice(getMotionSimulationDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);

    initDevices();

	startTimerList();

    delaymSec(100);

    setDebugI2cEnabled(false);

	/*
    // Ping
    if (!pingDriverDataDispatcherList()) {
        printf("PING PROBLEM !");
    }

    // Set Clock for Motor Board !

    // Read Clock
    ClockData* clockData = clock.readClock(&clock);
    // TODO : Change Dispatcher Index ...
    writeDateRemoteClockData(clockData, 0x01);
    writeHourRemoteClockData(clockData, 0x01);

    // testDriverIntensive(100);

    startTimerList();
	*/
    while (1) {
        mainBoardPcWaitForInstruction(&startMatch);
    }
    // TODO : ShowEnd
}