﻿#include "mainBoardPc.h"

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

#include "../../client/clock/clientClock.h"

#include "../../common/clock/clock.h"
#include "../../common/delay/cenDelay.h"
#include "../../common/eeprom/pc/eepromPc.h"
#include "../../common/error/error.h"
#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"
#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/pc/i2cCommonPc.h"
#include "../../common/i2c/master/pc/i2cMasterSetupPc.h"

#include "../../common/io/filter.h"
#include "../../common/io/pin.h"
#include "../../common/io/pc/consoleOutputStream.h"
#include "../../common/io/pc/consoleInputStream.h"
#include "../../common/io/pc/consoleOutputStream.h"
#include "../../common/io/pc/pinPc.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/streamLink.h"

#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/pc/ioExpanderPc.h"
#include "../../drivers/ioExpander/pc/ioExpanderFilePc.h"

#include "../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../drivers/i2c/multiplexer/multiplexerList.h"
#include "../../drivers/i2c/multiplexer/pc/multiplexerPc.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/pc/consoleLogHandler.h"

#include "../../common/math/cenMath.h"

#include "../../common/pwm/servo/servoPwm.h"
#include "../../common/pwm/servo/servoList.h"
#include "../../common/pwm/servo/pc/servoListPc.h"

// ONLY FOR TEST
#include "../../common/motor/dualHBridgeMotor.h"
#include "../../common/motor/pc/dualHBridgeMotorPc.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"
#include "../../common/serial/serialLinkList.h"

#include "../../common/system/system.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerConstants.h"
#include "../../common/timer/timerList.h"
#include "../../common/timer/delayTimer.h"

#include "../../common/pc/process/processHelper.h"

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

// IO
#include "../../device/ioExpander/ioExpanderDevice.h"
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"

// LED
#include "../../device/led/ledDevice.h"
#include "../../device/led/ledDeviceInterface.h"

// Multiplexer
#include "../../device/i2c/multiplexer/multiplexerDevice.h"
#include "../../device/i2c/multiplexer/multiplexerDeviceInterface.h"

// MAIN
#include "../../main/motorboard/motorBoardPc.h"
#include "../../main/meca1/mechanicalMainBoard1Pc.h"

#include "../../device/motor/pwmMotorDeviceInterface.h"
// MOTOR : NOT PRESENT on MAIN_BOARD
#include "../../device/motor/pwmMotorDevice.h"

// MOTION
#include "../../motion/simulation/motionSimulation.h"

// CONFIG
#include "../../robot/config/robotConfig.h"
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

// CURRENT
#include "../../device/sensor/current/currentSensorDevice.h"
#include "../../device/sensor/current/currentSensorDeviceInterface.h"

// GAMEBOARD
#include "../../device/gameboard/gameboardDevice.h"
#include "../../device/gameboard/gameboardDeviceInterface.h"

// IO
#include "../../device/io/ioDevice.h"
#include "../../device/io/ioDeviceInterface.h"

// LCD
#include "../../device/lcd/lcdDevice.h"
#include "../../device/lcd/lcdDeviceInterface.h"

// LED
#include "../../device/led/ledDevice.h"
#include "../../device/led/ledDeviceInterface.h"

// LOGS
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// MOTION
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/position/codersDeviceInterface.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"

// MOTION->Simple
#include "../../device/motion/simple/motionDeviceInterface.h"

#include "../../device/motion/simulation/motionSimulationDeviceInterface.h"

// MOTION->Extended
#include "../../device/motion/extended/extendedMotionDeviceInterface.h"

// NAVIGATION
#include "../../device/navigation/navigationDevice.h"
#include "../../device/navigation/navigationDeviceInterface.h"

// PWM
#include "../../device/motor/pwmMotorDevice.h"
#include "../../device/motor/pwmMotorDeviceInterface.h"

// ROBOT
#include "../../device/robot/fake/fakeRobotDevice.h"
#include "../../device/robot/fake/fakeRobotDeviceInterface.h"

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

// TIME OF FLIGHT
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// Drivers
#include "../../drivers/driverStreamListener.h"
#include "../../drivers/clock/pc/pcClock.h"
#include "../../drivers/driverList.h"

#include "../../drivers/dispatcher/dataDispatcherDeviceDriver.h"
#include "../../drivers/dispatcher/driverDataDispatcherList.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../drivers/dispatcher/i2cDriverDataDispatcher.h"

#include "../../drivers/file/eeprom/eepromFile.h"

#include "../../drivers/led/led.h"
#include "../../drivers/led/pc/ledPc.h"

#include "../../drivers/test/testDriver.h"

#include "../../drivers/sensor/current/pc/currentPc.h"

#include "../../drivers/tof/tof.h"
#include "../../drivers/tof/tofList.h"
#include "../../drivers/tof/pc/tofPc.h"
#include "../../drivers/tof/pc/tofListPc.h"

#include "../../drivers/sensor/temperature/pc/temperaturePc.h"

// Robot
#include "../../robot/match/endMatch.h"
#include "../../robot/match/endMatch.h"
#include "../../robot/match/endMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDeviceInterface.h"
#include "../../robot/match/startMatch.h"
#include "../../robot/match/startMatchDevice.h"
#include "../../robot/match/startMatchDeviceInterface.h"
#include "../../robot/match/pc/startMatchDetectorPc.h"

#include "../../main/motorBoard/motorBoardPc.h"
#include "../../main/meca1/mechanicalMainBoard1Pc.h"

#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameStrategyMotionHandler.h"
#include "../../robot/strategy/gameStrategyPositionHandler.h"

// Fake Robot
#include "../../robot/fake/fakeRobot.h"

// Other MainBoard
#include "../../main/mainBoard/mainBoardCommonTof.h"
#include "../../main/mainBoard/mainBoardCommonTofPc.h"

// 2020
#include "../../robot/2020/mainBoard2020.h"
#include "../../robot/2020/arm/armDeviceInterface2020.h"
#include "../../robot/2020/arm/armDevice2020.h"

#include "../../robot/tof/strategyTofSensorList.h"

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
static I2cBusConnection i2cBusConnectionListArray[MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH];

static I2cBus* mainI2cBus;
static I2cBusConnection* motorBoardI2cBusConnection;
static I2cBusConnectionPc motorBoardI2cBusConnectionPc;
static I2cBusConnection* meca1BoardI2cBusConnection;
static I2cBusConnectionPc meca1BoardI2cBusConnectionPc;

// HBridge
static DualHBridgeMotor dualHBridgeMotor;

// Dispatcher i2c->Motor
static char motorBoardInputBufferArray[MAIN_BOARD_PC_DATA_MOTOR_BOARD_DISPATCHER_BUFFER_LENGTH];
static Buffer motorBoardInputBuffer;
static InputStream motorBoardInputStream;
static OutputStream motorBoardOutputStream;

// Dispatcher i2c->Meca
static char meca1BoardInputBufferArray[MAIN_BOARD_PC_DATA_MECA1_BOARD_DISPATCHER_BUFFER_LENGTH];
static Buffer meca1BoardInputBuffer;
static InputStream meca1BoardInputStream;
static OutputStream meca1BoardOutputStream;

// Drivers
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH];

// Current Sensor
static Current current;

// Eeprom
static Eeprom eeprom;

// Clock
static Clock clock;

// IO / PinList
static PinList pinList;

// LED
static LedArray ledArray;

// Temperature
static Temperature temperature;

// RobotConfig
static RobotConfig robotConfig;
static IOExpander strategyIOExpander;

// SERIAL
static SerialLink serialLinkListArray[MAIN_BOARD_PC_SERIAL_LINK_LIST_LENGTH];

// I2C Debug
static char i2cMasterDebugOutputBufferArray[MAIN_BOARD_PC_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MAIN_BOARD_PC_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// ServoList
static ServoList servoList;
static Servo servoListArray[MAIN_BOARD_PC_SERVO_LIST_LENGTH];

// Timers
static Timer timerListArray[MAIN_BOARD_PC_TIMER_LIST_LENGTH];

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

// Match Management
static StartMatch startMatch;
static EndMatch endMatch;

// Navigation
static GameStrategyContext* gameStrategyContext;
static GameBoard* gameBoard;
static Navigation* navigation;

// IOExpander
static IOExpanderList ioExpanderList;
static IOExpander ioExpanderArray[MAIN_BOARD_PC_IO_EXPANDER_LIST_LENGTH];
static int ioExpanderValue0;
static int ioExpanderValue1;

// Multiplexer
static MultiplexerList multiplexerList;
static Multiplexer multiplexerArray[MAIN_BOARD_PC_MULTIPLEXER_LIST_LENGTH];
static int multiplexerValue0;
static int multiplexerValue1;

static bool connectToRobotManager = false;

void mainBoardDeviceHandleNotification(const Device* device, const unsigned char commandHeader, InputStream* inputStream) {
    OutputStream* logStream = getDebugOutputStreamLogger();
    appendString(logStream, "Notification ! commandHeader=");
    append(logStream, commandHeader);
    if (commandHeader == NOTIFY_TEST) {
        unsigned char value = readHex2(inputStream);
        appendStringAndDec(logStream, ", value=", value);
    }
}

bool mainBoardPcChecklist(StartMatch* startMatchParam) {
    return true;
}

bool mainBoardPcWaitForInstruction(StartMatch* startMatchParam) {
    while (handleNotificationFromDispatcherList(TRANSMIT_I2C, MOTOR_BOARD_I2C_ADDRESS)) {
        // loop for all notification
        // notification handler must avoid to directly information in notification callback
        // and never to the call back device
    }

    // delaymSec(MAIN_BOARD_PC_DELAY_CONSOLE_ANALYZE_MILLISECONDS);

    // Fill Console Buffer
    while (consoleInputStream.availableData(&consoleInputStream)) {
        unsigned char c = consoleInputStream.readChar(&consoleInputStream);
        if (c == 0) {
            continue;
        }
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
            &consoleOutputStream,
            &filterRemoveCRLF,
            NULL);

    if (connectToRobotManager) {
        // From RobotManager
        handleStreamInstruction(
                &robotManagerInputBuffer,
                &robotManagerOutputBuffer,
                &robotManagerOutputStream,
                &robotManagerOutputStream,
                &filterRemoveCRLF,
                NULL);
    }

    // Handle Tof
    if (gameStrategyContext != NULL) {
        handleTofSensorList(gameStrategyContext, startMatchParam, gameStrategyContext->tofSensorList, gameBoard);
    }

    // To Update the the position of the servo not by interruption but in the main Thread
    servoListMainUpdateCall(&servoList);

    // Protection against the start before the match
    if (startMatchParam->isMatchStartedFunction(startMatchParam)) {
        if (gameStrategyContext != NULL) {
            if (gameStrategyContext->loopTargetAndActions) {
                return nextTargetOrNextStep(gameStrategyContext);
            }
        }
    }

    return true;
}

void initMainBoardLocalDevices(void) {
    // LOCAL BOARD
    addLocalDevice(getADCDeviceInterface(), getADCDeviceDescriptor());
    addLocalDevice(getStrategyDeviceInterface(), getStrategyDeviceDescriptor(gameStrategyContext));
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor(&robotConfig));
    addLocalDevice(getI2cCommonDebugDeviceInterface(), getI2cCommonDebugDeviceDescriptor());
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());
    addLocalDevice(getDataDispatcherDeviceInterface(), getDataDispatcherDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor(&servoList));
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    // addLocalDevice(getFileDeviceInterface(), getFileDeviceDescriptor());
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getIODeviceInterface(), getIODeviceDescriptor(&pinList));
    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    addLocalDevice(getLedDeviceInterface(), getLedDeviceDescriptor(&ledArray));
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(mainBoardCommonTofGetTofSensorList()));


    //  IO Expander
    initIOExpanderPc(getIOExpanderByIndex(&ioExpanderList, 0), "IO Expander 0", &ioExpanderValue0);
    initIOExpanderPc(getIOExpanderByIndex(&ioExpanderList, 1), "IO Expander 1", &ioExpanderValue1);
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));

    // Multiplexer
    initMultiplexerPc(getMultiplexerByIndex(&multiplexerList, 0), &multiplexerValue0);
    initMultiplexerPc(getMultiplexerByIndex(&multiplexerList, 1), &multiplexerValue1);
    addLocalDevice(getMultiplexerDeviceInterface(), getMultiplexerDeviceDescriptor(&multiplexerList));

    addLocalDevice(getCurrentSensorDeviceInterface(), getCurrentSensorDeviceDescriptor(&current));
    addLocalDevice(getTemperatureSensorDeviceInterface(), getTemperatureSensorDeviceDescriptor(&temperature));
    addLocalDevice(getNavigationDeviceInterface(), getNavigationDeviceDescriptor(navigation));

    addLocalDevice(getStartMatchDeviceInterface(), getStartMatchDeviceDescriptor(&startMatch));
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor(&endMatch));

    // TODO
    // addLocalDevice(getRelayDeviceInterface(), getRelayDeviceDescriptor(&relay));
    // addLocalDevice(getColorSensorDeviceInterface(), getColorSensorDeviceDescriptor(&colorSensor));
    addLocalDevice(getGameboardDeviceInterface(), getGameboardDeviceDescriptor(gameBoard));
    addLocalDevice(getFakeRobotDeviceInterface(), getFakeRobotDeviceDescriptor(getFakeRobotInstance()));

    // 2020 specific
    addLocalDevice(getArm2020DeviceInterface(), getArm2020DeviceDescriptor(&servoList));
}

void runMainBoardPC(bool connectToRobotManagerMode, bool singleMode) {
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


    initLogs(LOG_LEVEL_DEBUG, (LogHandler(*)[]) & logHandlerListArray, MAIN_BOARD_PC_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
    initConsoleInputStream(&consoleInputStream);
    initConsoleOutputStream(&consoleOutputStream);
    addConsoleLogHandler(LOG_LEVEL_DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);

    initSerialLinkList((SerialLink(*)[]) & serialLinkListArray, MAIN_BOARD_PC_SERIAL_LINK_LIST_LENGTH);

    initTimerList((Timer(*)[]) & timerListArray, MAIN_BOARD_PC_TIMER_LIST_LENGTH);
    initSystemDelayTimer();
    initServoListPc(&servoList, (Servo(*)[]) & servoListArray, MAIN_BOARD_PC_SERVO_LIST_LENGTH);

    initBuffer(&consoleInputBuffer, (char(*)[]) & consoleInputBufferArray, MAIN_BOARD_PC_CONSOLE_INPUT_BUFFER_LENGTH, "inputConsoleBuffer", "IN");
    initBuffer(&consoleOutputBuffer, (char(*)[]) & consoleOutputBufferArray, MAIN_BOARD_PC_CONSOLE_OUTPUT_BUFFER_LENGTH, "outputConsoleBuffer", "IN");

    // Dispatchers
    initDriverDataDispatcherList((DriverDataDispatcher(*)[]) & driverDataDispatcherListArray, MAIN_BOARD_PC_DATA_DISPATCHER_LIST_LENGTH);
    addLocalDriverDataDispatcher();

    // I2c
    if (!singleMode) {
        initI2cBusList((I2cBus(*)[]) & i2cBusListArray, MAIN_BOARD_I2C_BUS_LIST_LENGTH);
        mainI2cBus = addI2cBus(I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_1);

        initI2cBusConnectionList((I2cBusConnection(*)[]) & i2cBusConnectionListArray, MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH);

        motorBoardI2cBusConnection = addI2cBusConnection(mainI2cBus, MOTOR_BOARD_PC_I2C_ADDRESS, false);
        initI2cBusConnectionPc(motorBoardI2cBusConnection,
                mainI2cBus,
                &motorBoardI2cBusConnectionPc,
                MOTOR_BOARD_PC_I2C_ADDRESS,
                MAIN_BOARD_TO_MOTOR_BOARD_PC_PIPE_I2C_MASTER_NAME,
                MOTOR_BOARD_PC_PIPE_I2C_SLAVE_NAME);

        meca1BoardI2cBusConnection = addI2cBusConnection(mainI2cBus, MECHANICAL_BOARD_1_I2C_ADDRESS, false);
        initI2cBusConnectionPc(meca1BoardI2cBusConnection,
                mainI2cBus,
                &meca1BoardI2cBusConnectionPc,
                MECHANICAL_BOARD_1_I2C_ADDRESS,
                MAIN_BOARD_TO_MECA1_BOARD_PC_PIPE_I2C_MASTER_NAME,
                MECHANICAL_BOARD_1_PC_PIPE_I2C_SLAVE_NAME);

        addI2CDriverDataDispatcher("MOTOR_BOARD_DISPATCHER",
                &motorBoardInputBuffer,
                (char(*)[]) & motorBoardInputBufferArray,
                MAIN_BOARD_PC_DATA_MOTOR_BOARD_DISPATCHER_BUFFER_LENGTH,
                &motorBoardOutputStream,
                &motorBoardInputStream,
                motorBoardI2cBusConnection
                );

        addI2CDriverDataDispatcher("MECA1_BOARD_DISPATCHER",
                &meca1BoardInputBuffer,
                (char(*)[]) & meca1BoardInputBufferArray,
                MAIN_BOARD_PC_DATA_MECA1_BOARD_DISPATCHER_BUFFER_LENGTH,
                &meca1BoardOutputStream,
                &meca1BoardInputStream,
                meca1BoardI2cBusConnection
                );
    }

    if (connectToRobotManager) {
        // Open the serial Link between RobotManager (C# Project) and the MainBoardPc
        openSerialLink(&robotManagerSerialStreamLink,
                "SERIAL_PC",
                &robotManagerInputBuffer,
                (char(*)[]) & robotManagerInputBufferArray,
                ROBOT_MANAGER_INPUT_BUFFER_LENGTH,
                &robotManagerOutputBuffer,
                (char(*)[]) & robotManagerOutputBufferArray,
                ROBOT_MANAGER_OUTPUT_BUFFER_LENGTH,
                &robotManagerOutputStream,
                SERIAL_PORT_ROBOT_MANAGER,
                0);
    }

    // CONFIG
    initRobotConfigPc(&robotConfig, ROBOT_TYPE_BIG);
    // initRobotConfigPc(&robotConfig, ROBOT_TYPE_SMALL);
    initIOExpanderFilePc(&strategyIOExpander, "strategy", "strategyConfigPc.txt");

    // EEPROM
    initEepromPc(&eeprom, "MAIN_BOARD_EEPROM");
    initEepromFile(&eeprom);

    // Clock
    initPcClock(&clock);

    // HBridge
    initDualHBridgeMotorPc(&dualHBridgeMotor, &pinList);

    // IO
    initPinListPc(&pinList);

    // LED
    initLedArrayPc(&ledArray);

    // -> SHOW COLOR OF THE TEAM
    enum TeamColor teamColor = getTeamColorFromRobotConfig(&robotConfig);
    Color color = getColorForTeam(teamColor);
    setLedColor(&ledArray, MAIN_BOARD_LED_COLOR_TEAM_INDEX, color);

    // Sensor
    initCurrentPc(&current);

    // Temperature
    initTemperaturePc(&temperature);

    // I2C Debug
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
            (char(*)[]) & i2cMasterDebugInputBufferArray,
            MAIN_BOARD_PC_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
            &i2cMasterDebugOutputBuffer,
            (char(*)[]) & i2cMasterDebugOutputBufferArray,
            MAIN_BOARD_PC_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);

    // IO Expander List
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) & ioExpanderArray, MAIN_BOARD_PC_IO_EXPANDER_LIST_LENGTH);

    // Multiplxer List
    initMultiplexerList(&multiplexerList, (Multiplexer(*)[]) & multiplexerArray, MAIN_BOARD_PC_MULTIPLEXER_LIST_LENGTH);

    // Fake Robot
    // initFakeRobot(300.0f, 1200.0f, 0.0f, 140.0f);
    initFakeRobot(900.0f, 1800.0f, 0.0f, 140.0f);

    navigation = initNavigation2020();
    unsigned char strategyId = strategyIOExpander.ioExpanderReadValue(&strategyIOExpander) & 0x0F;
    gameStrategyContext = initGameStrategyContext2020(&robotConfig, strategyId, &endMatch, mainBoardCommonTofGetTofSensorList(), &servoList);

    // Init the Tof as soon with have the gameStrategyContext
    mainBoardCommonTofInitDriversPc(&robotConfig, &multiplexerList, &ioExpanderList, gameStrategyContext);

    // For PC, we simulate the move
    gameStrategyContext->simulateMove = true;
    gameBoard = initGameBoard2020(gameStrategyContext);
    initMotionSimulation(gameStrategyContext);

    // Init the drivers
    initDrivers(&driverRequestBuffer, (char(*)[]) & driverRequestBufferArray, MAIN_BOARD_PC_REQUEST_DRIVER_BUFFER_LENGTH,
            &driverResponseBuffer, (char(*)[]) & driverResponseBufferArray, MAIN_BOARD_PC_RESPONSE_DRIVER_BUFFER_LENGTH);

    // Get test driver for debug purpose
    addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);

    // Devices
    initDeviceList((Device(*)[]) & deviceListArray, MAIN_BOARD_PC_DEVICE_LIST_LENGTH);
    // addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());

    testDevice = addI2cRemoteDevice(getTestDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
    testDevice->deviceHandleNotification = mainBoardDeviceHandleNotification;

    // Start Match
    initEndMatch(&endMatch, &robotConfig, MATCH_DURATION, &endMatchBeforeEnd2020);
    initStartMatch(&startMatch, &robotConfig, &endMatch, startupCheckList2020, isMatchStartedPc, mainBoardPcWaitForInstruction, mainBoardPcWaitForInstruction);

    initMainBoardLocalDevices();

    if (!singleMode) {
        // MOTOR BOARD
        addI2cRemoteDevice(getBatteryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
        // addI2cRemoteDevice(getEepromDeviceInterface(), MOTOR_BOARD_PC_I2C_ADDRESS);
        addI2cRemoteDevice(getPidDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
        addI2cRemoteDevice(getMotorDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
        addI2cRemoteDevice(getCodersDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
        addI2cRemoteDevice(getTrajectoryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
        addI2cRemoteDevice(getMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
        addI2cRemoteDevice(getExtendedMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
        addI2cRemoteDevice(getRobotKinematicsDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
        addI2cRemoteDevice(getMotionSimulationDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    }
    else {
        addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor(&dualHBridgeMotor));

    }
    initDevices();

    startTimerList(false);
    Timer* servoTimer = getTimerByCode(SERVO_TIMER_CODE);
    if (servoTimer != NULL) {
        servoTimer->enabled = true;
    }
    getTimerByCode(ROBOT_OBSTACLE_TIMER_CODE)->enabled = true;
    getTimerByCode(END_MATCH_DETECTOR_TIMER_CODE)->enabled = true;

    delayMilliSecs(100);

    setDebugI2cEnabled(false);

    mainBoardCommonStrategyMainEndInit2020(gameStrategyContext);

    // Wait until the match start
    loopUntilStart(&startMatch);

    while (true) {
        mainBoardPcWaitForInstruction(&startMatch);

        updateIfNeededRobotPositionFromMotorBoardToMainBoard(gameStrategyContext);

        // do the action before the end of the match
        doActionBeforeEndOfMatch(&endMatch, getAlwaysOutputStreamLogger());

        // Show the end of the match
        showEndAndScoreIfNeeded(&endMatch, getAlwaysOutputStreamLogger());
    }
}