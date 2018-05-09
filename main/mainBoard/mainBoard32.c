#include "../../common/commons.h"

#include "../../common/setup/32/picSetup32.h"

#include <plib.h>
#include <stdlib.h>
#include <math.h>

#include "mainBoard32.h"
#include "mainBoardCommon.h"

// CLIENT
// -> Motion Driver
#include "../../client/motion/simple/clientMotion.h"
#include "../../client/motion/position/clientTrajectory.h"
#include "../../client/robot/2018/launcherClient2018.h"

// COMMON
#include "../../common/delay/cenDelay.h"

#include "../../common/error/error.h"

#include "../../common/eeprom/eeprom.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cDebug.h"
#include "../../common/i2c/i2cBusList.h"
#include "../../common/i2c/i2cBusConnectionList.h"

#include "../../common/i2c/master/i2cMaster.h"
#include "../../common/i2c/master/i2cMasterSetup.h"

#include "../../common/i2c/master/i2cMasterOutputStream.h"
#include "../../common/i2c/master/i2cMasterInputStream.h"

#include "../../common/io/buffer.h"
#include "../../common/io/compositeOutputStream.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/streamLink.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../common/pwm/pwmPic.h"
#include "../../common/pwm/servo/servoPwm.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"
#include "../../common/serial/serialLinkList.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerConstants.h"
#include "../../common/timer/timerList.h"

#include "../../common/system/system.h"

#include "../../device/device.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceUsage.h"
#include "../../device/deviceList.h"
#include "../../device/transmitMode.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"


#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"
#include "../../drivers/dispatcher/i2cDriverDataDispatcher.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"
#include "../../drivers/dispatcher/uartDriverDataDispatcher.h"

// CLOCK
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// COLOR
#include "../../device/color/colorDevice.h"
#include "../../device/color/colorDeviceInterface.h"

// DATA DISPATCHER
#include "../../device/dispatcher/dataDispatcherDevice.h"
#include "../../device/dispatcher/dataDispatcherDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// GAMEBOARD
#include "../../device/gameboard/gameboardDevice.h"
#include "../../device/gameboard/gameboardDeviceInterface.h"

// LOG
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// I2C
#include "../../device/i2c/i2cCommonDebugDevice.h"
#include "../../device/i2c/i2cCommonDebugDeviceInterface.h"

// I2C MASTER DEBUG
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// IO EXPANDER
#include "../../device/ioExpander/ioExpanderDevice.h"
#include "../../device/ioExpander/ioExpanderDeviceInterface.h"

// LCD
#include "../../device/lcd/lcdDevice.h"
#include "../../device/lcd/lcdDeviceInterface.h"

// SERIAL
#include "../../device/serial/serialDebugDevice.h"
#include "../../device/serial/serialDebugDeviceInterface.h"

// SERVO
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// TEST
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// TEST 2
#include "../../device/test/test2Device.h"
#include "../../device/test/test2DeviceInterface.h"

// TEMPERATURE
#include "../../device/sensor/temperature/temperatureSensorDevice.h"
#include "../../device/sensor/temperature/temperatureSensorDeviceInterface.h"

// TIMER
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// Tof
#include "../../device/tof/tofDevice.h"
#include "../../device/tof/tofDeviceInterface.h"

// Motor
#include "../../device/motor/pwmMotorDeviceInterface.h"

// Motion
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/position/codersDeviceInterface.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"
#include "../../device/motion/simple/motionDeviceInterface.h"
#include "../../device/motion/extended/extendedMotionDeviceInterface.h"

// Navigation
#include "../../device/navigation/navigationDevice.h"
#include "../../device/navigation/navigationDeviceInterface.h"

// Relay
#include "../../device/relay/relayDevice.h"
#include "../../device/relay/relayDeviceInterface.h"

// Sonar
#include "../../device/sonar/sonarDevice.h"
#include "../../device/sonar/sonarDeviceInterface.h"

// Strategy
#include "../../device/strategy/strategyDevice.h"
#include "../../device/strategy/strategyDeviceInterface.h"

#include "../../device/adc/adcDevice.h"
#include "../../device/adc/adcDeviceInterface.h"

// Drivers
// -> Clock
#include "../../drivers/clock/PCF8563.h"

// -> Color
#include "../../drivers/colorSensor/tcs34725.h"
#include "../../drivers/colorSensor/colorSensorTcs34725.h"

// DRIVER TRANSMITTER
#include "../../drivers/driverTransmitter.h"

// -> Eeprom
#include "../../drivers/eeprom/24c512.h"

// -> IO EXPANDER
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/ioExpander/ioExpanderDebug.h"
#include "../../drivers/ioExpander/ioExpanderList.h"
#include "../../drivers/ioExpander/ioExpanderPcf8574.h"
#include "../../drivers/ioExpander/pcf8574.h"

// LCD
#include "../../drivers/lcd/lcd.h"

// MOTOR
#include "../../drivers/motor/md22.h"

// RELAY
#include "../../drivers/relay/rly08.h"

// -> System
#include "../../drivers/system/systemDriver.h"

// -> Temperature
#include "../../drivers/sensor/temperature/LM75A.h"

// -> Test
#include "../../drivers/test/testDriver.h"

// TOF
#include "../../drivers/tof/vl53l0x/tof_vl53l0x.h"
#include "../../drivers/tof/vl53l0x/tofList_vl53l0x.h"

// MOTION
#include "../../motion/simple/simpleMotion.h"

// NAVIGATION
#include "../../navigation/navigation.h"

// Robot
#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"
#include "../../robot/config/robotConfigDeviceInterface.h"
#include "../../robot/config/32/robotConfigPic32.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElementList.h"

#include "../../robot/kinematics/robotKinematicsDeviceInterface.h"

#include "../../robot/match/startMatch.h"
#include "../../robot/match/endMatch.h"
#include "../../robot/match/32/startMatchDetector32.h"
#include "../../robot/match/startMatchDevice.h"
#include "../../robot/match/startMatchDeviceInterface.h"
#include "../../robot/match/endMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDeviceInterface.h"

#include "../../robot/opponent/robotInfraredDetectorDeviceInterface.h"
#include "../../robot/opponent/robotInfraredDetectorDriver.h"
#include "../../robot/opponent/robotSonarDetectorDevice.h"
#include "../../robot/opponent/robotSonarDetectorDeviceInterface.h"

#include "../../robot/strategy/teamColor.h"
#include "../../robot/strategy/gameStrategyHandler.h"
#include "../../robot/strategy/gameTargetList.h"

#include "../../robot/robot.h"
#include "../../robot/gameboard/gameboard.h"

// 2018
#include "../../robot/2018/strategy2018.h"
#include "../../robot/2018/distributor2018.h"
#include "../../robot/2018/launcherDevice2018.h"
#include "../../robot/2018/launcherDeviceInterface2018.h"

#include "../../robot/2018/strategyDevice2018.h"
#include "../../robot/2018/strategyDeviceInterface2018.h"
#include "../../robot/2018/instructionCounter2018.h"

#include "mainBoard2018.h"
#include "2dDebug.h"
#include "strategyConfig2018.h"

// I2C => PORT 1 (for All Peripherical, including Eeprom / Clock / Temperatur)
static I2cBus i2cBusListArray[MAIN_BOARD_I2C_BUS_LIST_LENGTH];
static I2cBusConnection i2cBusConnectionListArray[MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH];
static I2cBus* i2cBus;
static I2cBus* i2cBus4;

// EEPROM
static Eeprom eeprom;
static I2cBusConnection* eepromI2cBusConnection;

// CLOCK
static Clock clock;
static I2cBusConnection* clockI2cBusConnection;

// COLOR
static ColorSensor colorSensor;
static Tcs34725 tcs34725;
static Color colorValue;
static I2cBusConnection* colorBusConnection;

// IO Expander
static IOExpanderList ioExpanderList;
static IOExpander ioExpanderArray[MAIN_BOARD_IO_EXPANDER_LIST_LENGTH];
static I2cBusConnection* tofIoExpanderBusConnection;

// TEMPERATURE
static Temperature temperature;
static I2cBusConnection* temperatureI2cBusConnection;

// StartMatch
static StartMatch startMatch;
static EndMatch endMatch;

// TOF
static TofSensorList tofSensorList;
static TofSensor tofSensorArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];
static TofSensorVL53L0X tofSensorVL53L0XArray[MAIN_BOARD_TOF_SENSOR_LIST_LENGTH];

// SERIAL
static SerialLink serialLinkListArray[MAIN_BOARD_SERIAL_LINK_LIST_LENGTH];

// serial link DEBUG 
static char debugInputBufferArray[MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// serial link Motor
static char motorInputBufferArray[MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH];
static Buffer motorInputBuffer;
static char motorOutputBufferArray[MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH];
static Buffer motorOutputBuffer;
static OutputStream motorOutputStream;
static StreamLink motorSerialStreamLink;

// serial link Meca1
static char meca1InputBufferArray[MAIN_BOARD_MECA_1_INPUT_BUFFER_LENGTH];
static Buffer meca1InputBuffer;
static char meca1OutputBufferArray[MAIN_BOARD_MECA_1_OUTPUT_BUFFER_LENGTH];
static Buffer meca1OutputBuffer;
static OutputStream meca1OutputStream;
static StreamLink meca1SerialStreamLink;

// serial link Motor Notification
static char motorNotifyInputBufferArray[MAIN_BOARD_MOTOR_NOTIFY_INPUT_BUFFER_LENGTH];
static Buffer motorNotifyInputBuffer;
static char motorNotifyOutputBufferArray[MAIN_BOARD_MOTOR_NOTIFY_OUTPUT_BUFFER_LENGTH];
static Buffer motorNotifyOutputBuffer;
static OutputStream motorNotifyOutputStream;
static StreamLink motorNotifySerialStreamLink;

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

// DISPATCHER I2C
static DriverDataDispatcher driverDataDispatcherListArray[MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH];
// Robot Configuration
static RobotConfig robotConfig;

// lcd DEBUG 
static OutputStream lcdOutputStream;

// Logs
static LogHandler logHandlerListArray[MAIN_BOARD_LOG_HANDLER_LIST_LENGTH];

// Devices
static Device deviceListArray[MAIN_BOARD_DEVICE_LENGTH];

// Relay
static Relay relay;
static I2cBusConnection* relayBusConnection;

// Timers
static Timer timerListArray[MAIN_BOARD_TIMER_LENGTH];

// 2018
static Distributor distributor;

static GameStrategyContext* gameStrategyContext;
static Navigation* navigation;
static GameBoard* gameBoard;

void updateNewPositionFromNotification(InputStream* inputStream) {
    float x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
    checkIsSeparator(inputStream);
    float y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
    checkIsSeparator(inputStream);
    float angleDegree = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);
    
    gameStrategyContext->robotPosition->x = x;
    gameStrategyContext->robotPosition->y = y;
    gameStrategyContext->robotAngleRadian = degToRad(angleDegree);
}

void mainBoardDeviceHandleMotionDeviceNotification(const Device* device, const char commandHeader, InputStream* inputStream) {
    if (device->deviceInterface->deviceHeader == MOTION_DEVICE_HEADER) {
        if (
                commandHeader == NOTIFY_MOTION_STATUS_FAILED
                || commandHeader == NOTIFY_MOTION_STATUS_MOVING
                || commandHeader == NOTIFY_MOTION_STATUS_OBSTACLE
                || commandHeader == NOTIFY_MOTION_STATUS_REACHED
                || commandHeader == NOTIFY_MOTION_STATUS_BLOCKED
                || commandHeader == NOTIFY_MOTION_STATUS_SHOCKED) {
            updateNewPositionFromNotification(inputStream);
            // FAKE DATA To Align with TrajectoryDevice
            checkIsSeparator(inputStream);
            checkIsChar(inputStream, 'F');

            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_NONE;
            // To know if we have reached the target
            if (commandHeader == NOTIFY_MOTION_STATUS_REACHED) {
                gameStrategyContext->instructionCounter++;
            }
        }
        else {
            writeError(NOTIFICATION_BAD_DEVICE_COMMAND_HANDLER_NOT_HANDLE);
            appendString(getAlwaysOutputStreamLogger(), "header");
            append(getAlwaysOutputStreamLogger(), commandHeader);
            println(getAlwaysOutputStreamLogger());
        }
    }
    else {
        writeError(NOTIFICATION_BAD_DEVICE);
    }
}

void mainBoardDeviceHandleTrajectoryDeviceNotification(const Device* device, const char commandHeader, InputStream* inputStream) {
    if (device->deviceInterface->deviceHeader == TRAJECTORY_DEVICE_HEADER) {
        if (commandHeader == NOTIFY_TRAJECTORY_CHANGED) {
            updateNewPositionFromNotification(inputStream);
            checkIsSeparator(inputStream);
            enum TrajectoryType trajectoryType = readHex(inputStream);
            gameStrategyContext->trajectoryType = trajectoryType;
        }
        else {
            writeError(NOTIFICATION_BAD_DEVICE_COMMAND_HANDLER_NOT_HANDLE);
            appendString(getAlwaysOutputStreamLogger(), "header");
            append(getAlwaysOutputStreamLogger(), commandHeader);
            println(getAlwaysOutputStreamLogger());
        }
    }
    else {
        writeError(NOTIFICATION_BAD_DEVICE);
    }
}

/**
 * TODO : Rename Driver into ClientDriver
 * @private
 */
void initMainBoardDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
                &driverResponseBuffer, &driverResponseBufferArray, MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);

    // Get test driver for debug purpose
    addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);
}

/**
 * @private.
 */
void addLocalDevices(void) {
    // SYSTEM & DEBUG
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getTest2DeviceInterface(), getTest2DeviceDescriptor());
    addLocalDevice(getDataDispatcherDeviceInterface(), getDataDispatcherDeviceDescriptor());
    addLocalDevice(getI2cCommonDebugDeviceInterface(), getI2cCommonDebugDeviceDescriptor());
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());

    // LOCAL
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor(&robotConfig));
    addLocalDevice(getStrategyDeviceInterface(), getStrategyDeviceDescriptor(gameStrategyContext));

    addLocalDevice(getStartMatchDeviceInterface(), getStartMatchDeviceDescriptor(&startMatch));
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor(&endMatch));
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getTemperatureSensorDeviceInterface(), getTemperatureSensorDeviceDescriptor(&temperature));
    addLocalDevice(getADCDeviceInterface(), getADCDeviceDescriptor());
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor(PWM_SERVO_ENABLED_MASK_SERVO_1_2_5));

    addLocalDevice(getRelayDeviceInterface(), getRelayDeviceDescriptor(&relay));
    addLocalDevice(getColorSensorDeviceInterface(), getColorSensorDeviceDescriptor(&colorSensor));
    addLocalDevice(getTofDeviceInterface(), getTofDeviceDescriptor(&tofSensorList));
    addLocalDevice(getGameboardDeviceInterface(), getGameboardDeviceDescriptor(gameBoard));
    
    addLocalDevice(getIOExpanderDeviceInterface(), getIOExpanderDeviceDescriptor(&ioExpanderList));

    // 2018 specific
    addLocalDevice(getNavigationDeviceInterface(), getNavigationDeviceDescriptor(navigation));
    addLocalDevice(getStrategy2018DeviceInterface(), getStrategy2018DeviceDescriptor(&distributor));
}

/**
 * @private
 */
void addMotorRemoteDevices(void) {
    // MOTOR BOARD -> UART
    addUartRemoteDevice(getTestDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getMotorDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getCodersDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getPidDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDeviceWithNotification(getTrajectoryDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR, &mainBoardDeviceHandleTrajectoryDeviceNotification);
    addUartRemoteDeviceWithNotification(getMotionDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR, &mainBoardDeviceHandleMotionDeviceNotification);
    addUartRemoteDevice(getExtendedMotionDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getRobotKinematicsDeviceInterface(), MAIN_BOARD_SERIAL_PORT_MOTOR);
}

/**
 * @private. 
 */
void addMeca1RemoteDevices(void) {
    // Mechanical Board 1->UART
    addUartRemoteDevice(getLauncher2018DeviceInterface(), MAIN_BOARD_SERIAL_PORT_MECA_1);
}

/**
 * @private
 */
void initMainBoardDevicesDescriptor() {
    initDeviceList(&deviceListArray, MAIN_BOARD_DEVICE_LENGTH);

    addLocalDevices();
    addMotorRemoteDevices();
    addMeca1RemoteDevices();

    // Init the devices
    initDevices();
}

void initMainBoardDriverDataDispatcherList(void) {
    // Initializes the DriverDataDispatcherList
    initDriverDataDispatcherList(&driverDataDispatcherListArray, MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH);

    // Configure data dispatcher
    addLocalDriverDataDispatcher();

    // SERIAL

    // Uart Stream for motorBoard
    addUartDriverDataDispatcher(
        &motorSerialStreamLink,
        "MOTOR_BOARD_UART_DISPATCHER",
        MAIN_BOARD_SERIAL_PORT_MOTOR);

    // Uart Stream for mechanicalBoard 1
    addUartDriverDataDispatcher(
        &meca1SerialStreamLink,
        "MECA_1_UART_DISPATCHER",
        MAIN_BOARD_SERIAL_PORT_MECA_1);
    
    // Uart Stream for motorBoard Notification
    addUartDriverDataDispatcher(
        &motorNotifySerialStreamLink,
        "MOTOR_BOARD_NOTIFY_UART_DISPATCHER",
        MAIN_BOARD_SERIAL_PORT_MOTOR_NOTIFY);
    
}

void handleTofSensorList() {
    // We only lookup if the match is started !
    if (!isMatchStarted32(&startMatch)) {
        return;
    }
    // If Sonar is disabled, we don't check it !
    if (!isSonarActivated(&robotConfig)) {
        return;
    }
    unsigned int index;
    enum TrajectoryType trajectoryType = gameStrategyContext->trajectoryType;
    if (trajectoryType == TRAJECTORY_TYPE_NONE || trajectoryType == TRAJECTORY_TYPE_ROTATION) {
        return;
    }
    for (index = 0; index < tofSensorList.size; index++) {
        TofSensor* tofSensor = getTofSensorByIndex(&tofSensorList, index);
        
        bool tofBackward = isTofSensorBackwardOriented(tofSensor);
        
        // Don't manage Backward TofSensor if we go forward
        if (tofBackward && trajectoryType == TRAJECTORY_TYPE_FORWARD) {
            continue;
        }
        
        // Don't manage Forward TofSensor if we go backward
        if (!tofBackward && trajectoryType == TRAJECTORY_TYPE_BACKWARD) {
            continue;
        }
        
        // TO DO : Manage if we must use Back Sonar or Front Sonar !
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        if (distance <= SENSOR_DISTANCE_MIN_TRESHOLD) {
            continue;
        }
        // DetectedPoint if any
        Point detectedPoint;
        Point* pointOfView = gameStrategyContext->robotPosition;
        float pointOfViewAngleRadian = gameStrategyContext->robotAngleRadian;
        bool detected = tofComputeDetectedPointIfAny(tofSensor, pointOfView, pointOfViewAngleRadian, &detectedPoint);
        
        if (!detected) {
            continue;
        }
        // We must know if it's in the gameboard
        if (isPointInTheCollisionArea(gameBoard, &detectedPoint)) {
            // motionDriverStop();
            motionDriverCancel();
            // Then we notify !
            OutputStream* alwaysOutputStream = getAlwaysOutputStreamLogger();
            println(alwaysOutputStream);
            appendStringAndDec(alwaysOutputStream, "Tof:", index);
            appendString(alwaysOutputStream, ",");
            printPoint(alwaysOutputStream, &detectedPoint, "");
            println(alwaysOutputStream);
            // Block the notification system !
            gameStrategyContext->trajectoryType = TRAJECTORY_TYPE_NONE;
            break;
        }
    }
}

bool mainBoardWaitForInstruction(StartMatch* startMatchParam) {
    // Handle Notification
    while (handleNotificationFromDispatcherList(TRANSMIT_UART, MAIN_BOARD_SERIAL_PORT_MOTOR_NOTIFY)) {
        
    }
    // loop for all notification
    // notification handler must avoid to directly information in notification callback
    // and never to the call back device
    
    // Listen instruction from debugStream->Devices
    handleStreamInstruction(
            &debugInputBuffer,
            &debugOutputBuffer,
            &debugOutputStream,
            &filterRemoveCRLF,
            NULL);
    
    // Listen instruction from motorNotifyStream->Devices
    handleStreamInstruction(
            &motorNotifyInputBuffer,
            &motorNotifyOutputBuffer,
            &motorNotifyOutputStream,
            &filterRemoveCRLF,
            NULL);

    handleTofSensorList();
    return true;
}

int main(void) {
    setBoardName("MAIN BOARD");
    setRobotMustStop(false);

    // LOG Global Configuration
    initLogs(LOG_LEVEL_INFO, &logHandlerListArray, MAIN_BOARD_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);

    // LCD (LCD via Parallel interface)
    initLCDOutputStream(&lcdOutputStream);
    addLogHandler("LCD", &lcdOutputStream, LOG_LEVEL_ERROR, LOG_HANDLER_CATEGORY_ALL_MASK);

    // CONFIG
    initRobotConfigPic32(&robotConfig);

    // Backlight the LCD is needed
    setBacklight(isConfigSet(&robotConfig, CONFIG_LCD_MASK));

    // SERIAL

    initSerialLinkList(&serialLinkListArray, MAIN_BOARD_SERIAL_LINK_LIST_LENGTH);

    // Open the serial Link for the PC : No Log, only instruction
    openSerialLink(&motorNotifySerialStreamLink,
                   "MOTOR_NOTIFY", 
                    &motorNotifyInputBuffer, &motorNotifyInputBufferArray, MAIN_BOARD_MOTOR_NOTIFY_INPUT_BUFFER_LENGTH,
                    &motorNotifyOutputBuffer, &motorNotifyOutputBufferArray, MAIN_BOARD_MOTOR_NOTIFY_OUTPUT_BUFFER_LENGTH,
                    &motorNotifyOutputStream,
                    MAIN_BOARD_SERIAL_PORT_MOTOR_NOTIFY,
                    DEFAULT_SERIAL_SPEED);

    // Open the serial Link for debug and LOG !
    openSerialLink(&debugSerialStreamLink, 
            "SERIAL_DEBUG",
            &debugInputBuffer, &debugInputBufferArray, MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
            &debugOutputBuffer, &debugOutputBufferArray, MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
            &debugOutputStream,
            MAIN_BOARD_SERIAL_PORT_DEBUG,
            DEFAULT_SERIAL_SPEED);
    // Serial Debug LOG
    addLogHandler("UART", &debugOutputStream, LOG_LEVEL_DEBUG, LOG_HANDLER_CATEGORY_ALL_MASK);

    // LOG the BoardName
    appendString(getAlwaysOutputStreamLogger(), getBoardName());
    println(getAlwaysOutputStreamLogger());
    
    // Increase the Log Level to INFO
    Logger* logger = getLoggerInstance();
    if (isConfigSet(&robotConfig, CONFIG_DEBUG)) {
        logger->globalLogLevel = LOG_LEVEL_DEBUG;
    }
    appendString(getInfoOutputStreamLogger(), "GLOBAL LEVEL : ");
    appendLevelAsString(getInfoOutputStreamLogger(), logger->globalLogLevel);
    println(getInfoOutputStreamLogger());
    
    // Open the serial Link for the Motor Board
    openSerialLink(&motorSerialStreamLink,
                   "SERIAL_MOTOR", 
                   &motorInputBuffer, &motorInputBufferArray, MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH,
                   &motorOutputBuffer, &motorOutputBufferArray, MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH,
                   &motorOutputStream,
                   MAIN_BOARD_SERIAL_PORT_MOTOR,
                   DEFAULT_SERIAL_SPEED);

    // Open the serial Link for the Mechanical Board
    openSerialLink(&meca1SerialStreamLink,
                   "SERIAL_MECA_1", 
                   &meca1InputBuffer, &meca1InputBufferArray, MAIN_BOARD_MECA_1_INPUT_BUFFER_LENGTH,
                   &meca1OutputBuffer, &meca1OutputBufferArray, MAIN_BOARD_MECA_1_OUTPUT_BUFFER_LENGTH,
                   &meca1OutputStream,
                   MAIN_BOARD_SERIAL_PORT_MECA_1,
                   DEFAULT_SERIAL_SPEED);

    // MAIN I2C
    initI2cBusList((I2cBus(*)[]) &i2cBusListArray, MAIN_BOARD_I2C_BUS_LIST_LENGTH);
	initI2cBusConnectionList((I2cBusConnection(*)[]) &i2cBusConnectionListArray, MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH);

    // MAIN I2C BUS
    i2cBus = addI2cBus(I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_1);
    i2cMasterInitialize(i2cBus);

    // ALTERNATIVE I2C BUS
    i2cBus4 = addI2cBus(I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_4);
    i2cMasterInitialize(i2cBus4);

    // -> Eeproms
    appendString(getDebugOutputStreamLogger(), "EEPROM ...");
    eepromI2cBusConnection = addI2cBusConnection(i2cBus, ST24C512_ADDRESS_0, true);
    init24C512Eeprom(&eeprom, eepromI2cBusConnection);
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    
    // -> Clock
    appendString(getDebugOutputStreamLogger(), "CLOCK ...");
    clockI2cBusConnection = addI2cBusConnection(i2cBus, PCF8563_WRITE_ADDRESS, true);
    initClockPCF8563(&clock, clockI2cBusConnection);
    appendStringLN(getDebugOutputStreamLogger(), "OK");

    // -> Temperature
    appendString(getDebugOutputStreamLogger(), "TEMPERATURE ...");
    temperatureI2cBusConnection = addI2cBusConnection(i2cBus, LM75A_ADDRESS, true);
    initTemperatureLM75A(&temperature, temperatureI2cBusConnection);
    appendStringLN(getDebugOutputStreamLogger(), "OK");

    // IO Expander
    appendString(getDebugOutputStreamLogger(), "PCF ...");
    tofIoExpanderBusConnection = addI2cBusConnection(i2cBus, PCF8574_ADDRESS_0, true);
    initIOExpanderList(&ioExpanderList, (IOExpander(*)[]) &ioExpanderArray, MAIN_BOARD_IO_EXPANDER_LIST_LENGTH);
    IOExpander* tofIoExpander = getIOExpanderByIndex(&ioExpanderList, 0);
    initIOExpanderPCF8574(tofIoExpander, tofIoExpanderBusConnection);
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    
    // Relay is on PORT 4 => ONLY FOR TEST
    appendString(getDebugOutputStreamLogger(), "RELAY ...");
    relayBusConnection = addI2cBusConnection(i2cBus4, RLY08_ADDRESS_0, true);
    initRelayRLY08(&relay, relayBusConnection);
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    
    // TOF
    appendStringLN(getDebugOutputStreamLogger(), "TOF ...");
    initTofSensorListVL53L0X(&tofSensorList,
                             (TofSensor(*)[]) &tofSensorArray,
                             (TofSensorVL53L0X(*)[]) &tofSensorVL53L0XArray,
                              // Size
                              MAIN_BOARD_TOF_SENSOR_LIST_LENGTH,
                              i2cBus,
                              // IO Expander, if null, we will not be able to
                              // Manage several tof
                              tofIoExpander,
                              // debug
                              true,
                              // enabledAllSensors
                              true,
                              // changeAddressAllSensors
                              true
            );
    appendStringLN(getDebugOutputStreamLogger(), "OK");

        
    // -> Color : IMPORTANT !!! : Initialize COLOR after TOF because they share the same address
    // And not the same bus, but it uses "getI2cBusConnectionBySlaveAddress" ... which does not distinguish the bus ...
    appendStringLN(getDebugOutputStreamLogger(), "COLOR ...");
    colorBusConnection = addI2cBusConnection(i2cBus4, TCS34725_ADDRESS, true);
    initTcs34725Struct(&tcs34725, colorBusConnection);
    initColorSensorTcs34725(&colorSensor, &colorValue, &colorSensorFindColorType2018, &tcs34725);
    appendStringLN(getDebugOutputStreamLogger(), "OK");

    // TIMERS
    initTimerList(&timerListArray, MAIN_BOARD_TIMER_LENGTH);
    
    initEndMatch(&endMatch, &robotConfig, MATCH_DURATION);
    initStartMatch(&startMatch, &robotConfig, &endMatch, isMatchStarted32, mainBoardWaitForInstruction);
    
    // 2018
    navigation = initNavigation2018();
    gameStrategyContext = initGameStrategyContext2018(&robotConfig, &endMatch, &tofSensorList);
    gameBoard = initGameBoard2018(gameStrategyContext);
    initDistributor(&distributor, gameStrategyContext->color, &colorSensor);

    // DEVICES, DRIVERS, DISPATCHERS
    initMainBoardDevicesDescriptor();
    initMainBoardDriversDescriptor();
    initMainBoardDriverDataDispatcherList();

    // Start interruptions
    startTimerList(false);
    getTimerByCode(SERVO_TIMER_CODE)->enabled = true;
    getTimerByCode(END_MATCH_DETECTOR_TIMER_CODE)->enabled = true;

    // MOTOR BOARD
    // UART Device
    clearBuffer(&motorInputBuffer);
    // Send a clear Buffer to the remote board to avoid to keep bad data in the link when rebooting
    append(&motorOutputStream, HEADER_CLEAR_INPUT_STREAM);
    append(&motorOutputStream, HEADER_WRITE_CONTENT_AND_DEEP_CLEAR_BUFFER);
    motorOutputStream.flush(&motorOutputStream);
    
    // UART Notification
    clearBuffer(&motorNotifyInputBuffer);
    // Send a clear Buffer to the remote board to avoid to keep bad data in the link when rebooting
    append(&motorNotifyOutputStream, HEADER_CLEAR_INPUT_STREAM);
    append(&motorNotifyOutputStream, HEADER_WRITE_CONTENT_AND_DEEP_CLEAR_BUFFER);
    motorNotifyOutputStream.flush(&motorNotifyOutputStream);
    
    // MECA 1
    clearBuffer(&meca1InputBuffer);
    // Send a clear Buffer to the remote board to avoid to keep bad data in the link when rebooting
    append(&meca1OutputStream, HEADER_CLEAR_INPUT_STREAM);
    append(&meca1OutputStream, HEADER_WRITE_CONTENT_AND_DEEP_CLEAR_BUFFER);
    motorOutputStream.flush(&meca1OutputStream);
    
    // To let the MOTOR BOARD clearing the cache
    delaymSec(200);
      
    // Update this on the MOTOR BOARD to be synchronized !
    updateMotorBoardRobotPosition(gameStrategyContext);
    
    // Wait until the match start
    loopUntilStart(&startMatch);

    // Just after, we could increment the counter
    gameStrategyContext->instructionCounter = 1;
    
    while (1) {
        if (!mainBoardWaitForInstruction(&startMatch)) {
            break;
        }
        
        // Show the end of the match
        showEndAndScoreIfNeeded(&endMatch, getAlwaysOutputStreamLogger());
    }

    while (1) {
        // Avoid reboot even at end
    }
}
