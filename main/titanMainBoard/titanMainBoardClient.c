#include "../../common/commons.h"

#ifdef PROG_32
    #include <plib.h>
    #include "../../common/setup/32/picSetup32.h"
#else
    #include <i2c.h>
    #include "../../common/setup/30F/picSetup30F.h"
#endif

#include <stdlib.h>
#include <math.h>

#include "titanMainBoardClient.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cDebug.h"

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
#include "../../common/io/stream.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/cenMath.h"

#include "../../common/pwm/pwmPic.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../device/device.h"
#include "../../device/deviceDebug.h"
#include "../../device/deviceUsage.h"
#include "../../device/deviceList.h"
#include "../../device/dispatcher/deviceDataDispatcher.h"


#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"

#include "../../drivers/driverStreamListener.h"
#include "../../drivers/dispatcher/driverDataDispatcher.h"
#include "../../drivers/dispatcher/driverDataDispatcherDebug.h"
#include "../../drivers/dispatcher/i2cDriverDataDispatcher.h"
#include "../../drivers/dispatcher/localDriverDataDispatcher.h"

// CLOCK
#include "../../common/clock/clock.h"
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// TEMPERATURE SENSOR
#include "../../device/temperatureSensor/temperatureSensor.h"
#include "../../device/temperatureSensor/temperatureSensorDevice.h"
#include "../../device/temperatureSensor/temperatureSensorDeviceInterface.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// SYSTEM DEBUG
#include "../../device/system/systemDebugDevice.h"
#include "../../device/system/systemDebugDeviceInterface.h"

// I2C MASTER DEBUG
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// TEST
//#include "../../device/test/deviceTest.h"
//#include "../../device/test/deviceTestInterface.h"

// SERVO
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// LCD
#include "../../drivers/lcd/lcd.h"
#include "../../device/lcd/lcdDevice.h"
#include "../../device/lcd/lcdDeviceInterface.h"

// Motor
#include "../../device/motor/pwmMotorDeviceInterface.h"

// Motion
#include "../../device/motion/pid/pidDeviceInterface.h"
#include "../../device/motion/position/codersDeviceInterface.h"
#include "../../device/motion/position/trajectoryDeviceInterface.h"
#include "../../device/motion/simple/motionDeviceInterface.h"

// Sonar
#include "../../device/sonar/sonarDevice.h"
#include "../../device/sonar/sonarDeviceInterface.h"

// Strategy
#include "../../device/strategy/strategyDevice.h"
#include "../../device/strategy/strategyDeviceInterface.h"

// Specific 2011
#include "../../device/adc/adcDevice.h"
#include "../../device/adc/adcDeviceInterface.h"

// Air conditioning
#include "../../device/airconditioning/airConditioningDeviceInterface.h"

// Beacon Receiver
#include "../../device/beacon/beaconReceiverDeviceInterface.h"

// Drivers
#include "../../drivers/clock/PCF8563.h"
#include "../../drivers/io/pcf8574.h"
//#include "../../drivers/test/driverTest.h"
#include "../../drivers/system/systemDriver.h"
#include "../../drivers/motion/motionDriver.h"
#include "../../drivers/motion/trajectoryDriver.h"
#include "../../drivers/motor/md22.h"
#include "../../drivers/driverTransmitter.h"
#include "../../drivers/strategy/strategyDriver.h"
#include "../../drivers/sensor/LM75A.h"
//#include "../../drivers/robotConfig/PIC32/robotConfigPic32.h"

#include "../../common/eeprom/eeprom.h"

#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// Robot
#include "../../robot/config/32/robotConfigPic32.h"
#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"
#include "../../robot/config/robotConfigDeviceInterface.h"
#include "../../robot/match/32/startMatchDetector32.h"
#include "../../robot/match/startMatchDetector.h"
#include "../../robot/match/startMatchDetectorDevice.h"
#include "../../robot/match/startMatchDetectorDeviceInterface.h"
#include "../../robot/match/endMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDeviceInterface.h"

#include "../../robot/opponent/robotInfraredDetectorDeviceInterface.h"
#include "../../robot/opponent/robotInfraredDetectorDriver.h"
#include "../../robot/opponent/robotSonarDetectorDevice.h"
#include "../../robot/opponent/robotSonarDetectorDeviceInterface.h"
#include "../../robot/opponent/opponentRobot.h"

// Other boards interface
#include "../../main/motorboard/motorBoard.h"
#include "../../main/meca1/mechanicalBoard1.h"
#include "../../main/meca2/mechanicalBoard2.h"
#include "../../main/airconditioning/airConditioningMain.h"

#include "../../motion/simple/motion.h"

#include "../../robot/robot.h"

#include "../../drivers/sonar/srf02.h"

#ifndef MPLAB_SIMULATION
    #ifdef PROG_32
        #define SERIAL_PORT_DEBUG          SERIAL_PORT_2
        #define SERIAL_PORT_PC             SERIAL_PORT_6
        #define SERIAL_PORT_LCD            SERIAL_PORT_5
    #else
        #define SERIAL_PORT_DEBUG         SERIAL_PORT_1
        #define SERIAL_PORT_PC             SERIAL_PORT_2
    #endif
#else
    // We use the same port for both
    #define SERIAL_PORT_PC             SERIAL_PORT_1
    #define SERIAL_PORT_DEBUG         SERIAL_PORT_1
#endif

// serial link DEBUG 
static char debugInputBufferArray[MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// serial link PC
static char pcInputBufferArray[MAIN_BOARD_PC_INPUT_BUFFER_LENGTH];
static Buffer pcInputBuffer;
static char pcOutputBufferArray[MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH];
static Buffer pcOutputBuffer;
static OutputStream pcOutputStream;
static StreamLink pcSerialStreamLink;

// both OutputStream as composite
// static CompositeOutputStream compositePcAndDebugOutputStream;
// static CompositeOutputStream compositeDriverAndDebugOutputStream;

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

// DEBUG I2C
static char i2cMasterDebugOutputBufferArray[MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH];
static Buffer i2cMasterDebugOutputBuffer;
static char i2cMasterDebugInputBufferArray[MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH];
static Buffer i2cMasterDebugInputBuffer;

// DISPATCHER I2C

// i2c->Motor
static DriverDataDispatcher motorI2cDispatcher;
static char motorBoardInputBufferArray[MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH];
static Buffer motorBoardInputBuffer;
static InputStream motorBoardInputStream;
static OutputStream motorBoardOutputStream;

// i2c->Air Conditioning
static DriverDataDispatcher airConditioningI2cDispatcher;
static char airConditioningBoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer airConditioningBoardInputBuffer;
static InputStream airConditioningBoardInputStream;
static OutputStream airConditioningBoardOutputStream;

// i2c->Mechanical 2
static DriverDataDispatcher mechanical2I2cDispatcher;
static char mechanical2BoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer mechanical2BoardInputBuffer;
static InputStream mechanical2BoardInputStream;
static OutputStream mechanical2BoardOutputStream;

// i2c->Clock
static Clock globalClock;

// i2c->Eeprom
static Buffer eepromBuffer;
static char eepromBufferArray[EEPROM_BUFFER_LENGTH];
static Eeprom eeprom_;

// StartMatchDetector
static StartMatchDetector startMatchDetector;

// Robot Configuration
static RobotConfig robotConfig;

// lcd DEBUG 
static OutputStream lcdOutputStream;

// logs
static LogHandler debugSerialLogHandler;
static LogHandler lcdLogHandler;

// Devices
static Device deviceListArray[MAIN_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[MAIN_BOARD_TIMER_LENGTH];

// Obstacle management
static bool mustNotifyObstacle;
static unsigned int instructionType;
static bool useInfrared;
static bool useBalise;

#define INSTRUCTION_TYPE_NO_MOVE        0
#define INSTRUCTION_TYPE_FORWARD        1
#define INSTRUCTION_TYPE_BACKWARD        2
#define INSTRUCTION_TYPE_ROTATION        3

/**
 * Call-back when Data send some notification message (like Position Reached, Position failed ...)
 */
void mainBoardCallbackRawData(const Device* device,
        char header,
        InputStream* inputStream) {

//    if (header == NOTIFY_MOTION_STATUS || header == COMMAND_NOTIFY_TEST || header == COMMAND_PLIERS_2011_OPEN) {
    // MOTOR BOARD notification
    if (header == NOTIFY_MOTION_STATUS) {
        /*
        appendString(getOutputStreamLogger(INFO), "\nNotification : From MOTOR BOARD \n");
        // NOTIFY_MOTION_STATUS / COMMAND_NOTIFY_TEST
        checkIsChar(inputStream, header);
        // status
        unsigned char status = readHex2(inputStream);
        // separator
        checkIsChar(inputStream, '-');
        // x
        unsigned int x = readHex4(inputStream);
        // separator
        checkIsChar(inputStream, '-');
        // y
        unsigned int y = readHex4(inputStream);
        // separator
        checkIsChar(inputStream, '-');
        // angle in ddeg
        unsigned int angle = readHex4(inputStream);

        updateRobotPosition(x, y, angle);
        setRobotPositionChanged();
        
        // FOR DEBUG AND MOTHER BOARD
        OutputStream* outputStream = &(compositePcAndDebugOutputStream.outputStream);
        append(outputStream, header);
        appendHex2(outputStream, status);
        appendSeparator(outputStream);
        appendHex4(outputStream, x);
        appendSeparator(outputStream);
        appendHex4(outputStream, y);
        appendSeparator(outputStream);
        appendHex4(outputStream, angle);

        // ready for next motion instruction Index
        setReadyForNextMotion(true);
        // Robot finished the trajectory
        instructionType = INSTRUCTION_TYPE_NO_MOVE;
        */
    }
    // STRATEGY BOARD notification message of MOTOR => Must be relayed TO MOTOR
    else if (header == COMMAND_MOTION_SPLINE_ABSOLUTE || header == COMMAND_MOTION_SPLINE_RELATIVE) {
        /*
        appendString(getOutputStreamLogger(INFO), "Notification : Spline : From STRATEGY BOARD : relayed to MOTOR_BOARD \n");
        appendStringAndDec(getOutputStreamLogger(INFO), "getDriverResponseBuffer:", getBufferElementsCount(getDriverResponseBuffer()));
        // forwardCallbackRawDataTo(inputStream, &debugOutputStream, device, header, DEVICE_MODE_INPUT);
        OutputStream* outputStream = &(compositeDriverAndDebugOutputStream.outputStream);
        // OutputStream* outputStream = &debugOutputStream;

        readHex(inputStream);
        // appendString(outputStream, ",header=");
        append(outputStream, header);

        float x = readHex4(inputStream);
        // appendString(outputStream, ",x=");
        appendHex4(outputStream, x);

        checkIsChar(inputStream, '-');
        appendSeparator(outputStream);

        float y = readHex4(inputStream);
        // appendString(outputStream, ",y=");
        appendHex4(outputStream, y);

        checkIsChar(inputStream, '-');
        appendSeparator(outputStream);

        float angle = readHex4(inputStream);
        // appendString(outputStream, ",angle=");
        appendHex4(outputStream, angle);

        checkIsChar(inputStream, '-');
        appendSeparator(outputStream);

        signed char dist0 = readHex2(inputStream);
        // appendString(outputStream, ",dist0=");
        appendHex2(outputStream, dist0);

        checkIsChar(inputStream, '-');
        appendSeparator(outputStream);

        signed char dist1 = readHex2(inputStream);
        // appendString(outputStream, ",dist1=");
        appendHex2(outputStream, dist1);

        checkIsChar(inputStream, '-');
        appendSeparator(outputStream);

        signed char a = readHex(inputStream);
        // appendString(outputStream, ",a=");
        appendHex(outputStream, a);

        signed char s = readHex(inputStream);
        // appendString(outputStream, ",s=");
        appendHex(outputStream, s);
    
        if (dist0 < 0) {
            appendString(getOutputStreamLogger(INFO), "\nMotion Backward !");
            instructionType = INSTRUCTION_TYPE_BACKWARD;
        }
        else {
            appendString(getOutputStreamLogger(INFO), "\nMotion Forward !");
            instructionType = INSTRUCTION_TYPE_FORWARD;
        }        
        // forwardCallbackRawDataTo(inputStream, &(compositeDriverAndDebugOutputStream.outputStream), device, header, DEVICE_MODE_INPUT);
        transmitFromDriverRequestBuffer();
        */
    } else if (header == COMMAND_MOTION_LEFT_IN_DECI_DEGREE || header == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        /*
        appendString(getOutputStreamLogger(INFO), "Notification : Rotation : From STRATEGY BOARD : relayed to MOTOR_BOARD \n");
        instructionType = INSTRUCTION_TYPE_ROTATION;
        forwardCallbackRawDataTo(inputStream, &(compositeDriverAndDebugOutputStream.outputStream), device, header, DEVICE_MODE_INPUT);
        transmitFromDriverRequestBuffer();
        */
    } 
    // Mechanical Board notification
    else if (header == NOTIFY_INFRARED_DETECTOR_DETECTION) {
        /*
        appendString(getOutputStreamLogger(INFO), "\nNotification : From MECHANICAL BOARD :\n");
        checkIsChar(inputStream, NOTIFY_INFRARED_DETECTOR_DETECTION);
        // type
        unsigned char type = readHex2(inputStream);
        OutputStream* outputStream = &(compositePcAndDebugOutputStream.outputStream);
        append(outputStream, NOTIFY_INFRARED_DETECTOR_DETECTION);
        appendHex2(outputStream, type);
        if (useInfrared) {
            // Notify only if we are in a compatible move !
            if ((instructionType == INSTRUCTION_TYPE_BACKWARD) && (type == DETECTOR_BACKWARD_INDEX)) {
                mustNotifyObstacle = true;
            }
            else if ((instructionType == INSTRUCTION_TYPE_FORWARD) && (type == DETECTOR_FORWARD_INDEX)) {
                mustNotifyObstacle = true;
            }
        }
        */
    }
    // Cannot not handle the notification !
    else {
        appendString(getOutputStreamLogger(ERROR), "\nNotification lost:\n");
        copyInputToOutputStream(inputStream, getOutputStreamLogger(ERROR), NULL, COPY_ALL);
        println(getOutputStreamLogger(ERROR));
    }
}

/**
 * @private
 */
void initDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
                &driverResponseBuffer, &driverResponseBufferArray, MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);

    // Get test driver for debug purpose
//    addDriver(driverTestGetDescriptor(), TRANSMIT_LOCAL);

    // Direct Devantech Driver
    addDriver(getMD22DriverDescriptor(), TRANSMIT_NONE);
}

/**
 * @private
 */
void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MAIN_BOARD_DEVICE_LENGTH);

    // Test & System
    // addI2CRemoteDevice(&testDevice, getTestDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getSystemDebugDeviceInterface(), getSystemDebugDeviceDescriptor());
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());

    // Local
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&globalClock));
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    addLocalDevice(getTemperatureSensorDeviceInterface(), getTemperatureSensorDeviceDescriptor());
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom_));

    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor());
    addLocalDevice(getADCDeviceInterface(),getADCDeviceDescriptor());
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor(&robotConfig));
    addLocalDevice(getStartMatchDetectorDeviceInterface(), getStartMatchDetectorDeviceDescriptor(&startMatchDetector));
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor());
    addLocalDevice(getSonarDeviceInterface(), getSonarDeviceDescriptor());
    addLocalDevice(getRobotSonarDetectorDeviceInterface(), getRobotSonarDetectorDeviceDescriptor());

    // Mechanical Board 2->I2C
    // Device* armDevice = addI2CRemoteDevice(getArm2012DeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);
    // Device* infraredDetectorDevice = addI2CRemoteDevice(getRobotInfraredDetectorDeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);

    // Motor Board->I2C
    addI2CRemoteDevice(getPIDDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(getMotorDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(getCodersDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    Device* trajectoryDevice = addI2CRemoteDevice(getTrajectoryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    Device* motionDevice = addI2CRemoteDevice(getMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);

    // Beacon Receiver Board->I2C
    // addI2CRemoteDevice(getBeaconReceiverDeviceInterface(), BEACON_RECEIVER_I2C_ADDRESS);

    // Strategy Board->I2C
    // addI2CRemoteDevice(getStrategyDeviceInterface(), STRATEGY_BOARD_I2C_ADDRESS);

    // Air Conditioning Board
    addI2CRemoteDevice(getAirConditioningDeviceInterface(), AIR_CONDITIONING_BOARD_I2C_ADDRESS);

    // Init the devices
    initDevices();  

    // Manage the callback notification
    trajectoryDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // testDevice.deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    motionDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // infraredDetectorDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
}

/*
bool isObstacleOutsideTheTable(int distance) {
    float a = getRobotAngle() * (PI / 1800.0);
    float dca = cosf(a) * distance;
    float dsa = sinf(a) * distance;
    int obstacleX = getRobotPositionX() + dca;
    int obstacleY = getRobotPositionY() + dsa;
    
    appendStringAndDec(getOutputStreamLogger(INFO), "\nObstacle Position:x=", obstacleX);
    appendStringAndDec(getOutputStreamLogger(INFO), ",y=", obstacleY);
    println(getOutputStreamLogger(INFO));

    
    int BORDER_THRESHOLD = 250;
    int TOTEM_THRESHOLD_X = 250;
    int TOTEM_THRESHOLD_Y = 600;

    // Table border X
    if (obstacleX < BORDER_THRESHOLD || obstacleX > GAME_BOARD_WIDTH - BORDER_THRESHOLD) {
        return true;
    }
    // Table border Y
    if (obstacleY < BORDER_THRESHOLD || obstacleY > GAME_BOARD_HEIGHT - BORDER_THRESHOLD) {
        return true;
    }
    
    // Totem Zone
    if (    (obstacleX > GAME_BOARD_MIDDLE_WIDTH - TOTEM_THRESHOLD_X) 
         && (obstacleX < GAME_BOARD_MIDDLE_WIDTH + TOTEM_THRESHOLD_X)
         && (obstacleY > GAME_BOARD_MIDDLE_HEIGHT - TOTEM_THRESHOLD_Y) 
         && (obstacleY < GAME_BOARD_MIDDLE_HEIGHT - TOTEM_THRESHOLD_Y)) {
        return true;
    }
    return false;
}
*/

void waitForInstruction() {
    
    // Listen instruction from pcStream->Devices
    handleStreamInstruction(
            &pcInputBuffer,
            &pcOutputBuffer,
            &pcOutputStream,
            &filterRemoveCRLF,
            NULL);
    
    // Listen instruction from debugStream->Devices
    handleStreamInstruction(
            &debugInputBuffer,
            &debugOutputBuffer,
            &debugOutputStream,
            &filterRemoveCRLF,
            NULL);

    // Listen instructions from Devices (I2C Slave) -> Main Board (I2C Master)
    /*
    while (handleNotificationFromDispatcherList(TRANSMIT_I2C)) {
        // loop for all notification
        // notification handler must avoid to directly information in notification callback
        // and never to the call back device
    }
    */

    /*
    // Notify to the strategy board the position of the robot
    if (isRobotPositionChanged()) {
        sentStrategyRobotPosition(0, getRobotPositionX(), getRobotPositionY(), getRobotAngle());
        resetRobotPositionChanged();
    }

    if (mustNotifyObstacle) {
        mustNotifyObstacle = false;
        // Obtain robot position
        // Ask the robot position from the MOTOR BOARD
        trajectoryDriverUpdateRobotPosition();

        // compute the obstacle position. If it's outside the table, does nothing
        int obstacleDistance = 350.0f;
        appendStringAndDec(getOutputStreamLogger(INFO), "\nInstruction Type:", instructionType);

        if (instructionType == INSTRUCTION_TYPE_BACKWARD) {
            obstacleDistance = -obstacleDistance;
        }
        if (isObstacleOutsideTheTable(obstacleDistance)) {
            appendString(getOutputStreamLogger(INFO), "\nObstacle OUT side the Table!\n");
        }
        else {
            appendString(getOutputStreamLogger(INFO), "\nObstacle !\n");
            // Send information to Strategy Board
            stopRobotObstacle();
            armDriver2012Up(ARM_LEFT);
            armDriver2012Up(ARM_RIGHT);
            // we are ready for next motion (next loop)
            setReadyForNextMotion(true);
        }
    }

    // Update the current Opponent Robot position
    if (useBalise) {
        updateOpponentRobotIfNecessary();
    }
    */    
}

int main(void) {
    setPicName("TITAN ELECTRONICAL MAIN BOARD 32bits V-JJ_7");

    i2cMasterInitialize();
    
    //setRobotMustStop(false);
    // Open the serial Link for debug
    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
            MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
            &debugOutputBuffer,
            &debugOutputBufferArray,
            MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG,
            DEFAULT_SERIAL_SPEED);

    // Open the serial Link for the PC
    openSerialLink(&pcSerialStreamLink,
            &pcInputBuffer,
            &pcInputBufferArray,
            MAIN_BOARD_PC_INPUT_BUFFER_LENGTH,
            &pcOutputBuffer,
            &pcOutputBufferArray,
            MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH,
            &pcOutputStream,
            SERIAL_PORT_PC,
            DEFAULT_SERIAL_SPEED);

    // LCD (LCD03 via Serial interface)
    initLCDOutputStream(&lcdOutputStream);

    initTimerList(&timerListArray, MAIN_BOARD_TIMER_LENGTH);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&debugSerialLogHandler, "UART", &debugOutputStream, DEBUG);
    addLogHandler(&lcdLogHandler, "LCD", &lcdOutputStream, ERROR);

    appendString(getOutputStreamLogger(ALWAYS), getPicName());
    println(getOutputStreamLogger(ALWAYS));

    initDevicesDescriptor();
    initDriversDescriptor();

    i2cMasterInitialize();
    // Initialize EEPROM and RTC
    initClockPCF8563(&globalClock);
    init24C512Eeprom(&eeprom_);


    while (1){
            //CLOCK Read
        globalClock.readClock(&globalClock);
        printClock(&debugOutputStream,&globalClock);
        appendCR(&debugOutputStream);
        delaymSec(300);
    }



    initRobotConfigPic32(&robotConfig);

    initStartMatchDetector32(&startMatchDetector);


    // Initializes the opponent robot
    // initOpponentRobot();

    /*
    // Creates a composite to notify both PC and Debug
    initCompositeOutputStream(&compositePcAndDebugOutputStream);
    addOutputStream(&compositePcAndDebugOutputStream, &debugOutputStream);
    addOutputStream(&compositePcAndDebugOutputStream, &pcOutputStream);

    // Creates a composite to redirect to driverRequest and Debug
    initCompositeOutputStream(&compositeDriverAndDebugOutputStream);
    addOutputStream(&compositeDriverAndDebugOutputStream, &debugOutputStream);
    addOutputStream(&compositeDriverAndDebugOutputStream, getDriverRequestOutputStream());
    */

    appendString(&debugOutputStream, "DEBUG\n");
    
    // Start interruptions
    //startTimerList();  //////RALENTI FORTEMENT LE PIC!!! PLANTE I2C !!!!!!!!

    // Configure data dispatcher
    //addLocalDriverDataDispatcher();

    // Stream for motorBoard
    /*
    addI2CDriverDataDispatcher(&motorI2cDispatcher,
            "MOTOR_BOARD_DISPATCHER",
            &motorBoardInputBuffer,
            &motorBoardInputBufferArray,
            MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH,
            &motorBoardOutputStream,
            &motorBoardInputStream,
            MOTOR_BOARD_I2C_ADDRESS);
    */
    /*
    // Stream for Mechanical Board 2
    addI2CDriverDataDispatcher(&mechanical2I2cDispatcher,
            "MECHANICAL_BOARD_2_DISPATCHER",
            &mechanical2BoardInputBuffer,
            &mechanical2BoardInputBufferArray,
            MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH,
            &mechanical2BoardOutputStream,
            &mechanical2BoardInputStream,
            MECHANICAL_BOARD_2_I2C_ADDRESS);
    */

/*    // Stream for Air Conditioning
    addI2CDriverDataDispatcher(&airConditioningI2cDispatcher,
            "AIR_CONDITIONING_DISPATCHER",
            &airConditioningBoardInputBuffer,
            &airConditioningBoardInputBufferArray,
            MAIN_BOARD_LINK_TO_AIR_CONDITIONING_BOARD_BUFFER_LENGTH,
            &airConditioningBoardOutputStream,
            &airConditioningBoardInputStream,
            AIR_CONDITIONING_BOARD_I2C_ADDRESS);
*/
    // I2C Debug
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
                        &i2cMasterDebugInputBufferArray,
                        MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
                        &i2cMasterDebugOutputBuffer,
                        &i2cMasterDebugOutputBufferArray,
                        MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);


    appendStringConfig(&lcdOutputStream);

    // pingDriverDataDispatcherList(getOutputStreamLogger(DEBUG));

    // Inform PC waiting
    showWaitingStart(&debugOutputStream);



    // wait other board initialization
    delaymSec(1500);

    // 2012 VALUE
    unsigned int configValue = getConfigValue();
    unsigned int homologationIndex = configValue & CONFIG_STRATEGY_MASK;
    unsigned int color = configValue & CONFIG_COLOR_BLUE_MASK;

    appendString(getOutputStreamLogger(ALWAYS), "Homologation:");
    appendCRLF(getOutputStreamLogger(ALWAYS));
    appendDec(getOutputStreamLogger(ALWAYS), homologationIndex);
    
    appendString(getOutputStreamLogger(ALWAYS), "Config:");
    appendHex4(getOutputStreamLogger(ALWAYS), configValue);
    appendCRLF(getOutputStreamLogger(ALWAYS));
    useBalise = configValue & CONFIG_USE_BALISE_MASK;
    useInfrared = configValue & CONFIG_USE_SONAR_MASK;

    if (color != 0) {
        appendString(getOutputStreamLogger(ALWAYS), "COLOR:VIOLET\n");
    }
    else {
        appendString(getOutputStreamLogger(ALWAYS), "COLOR:RED\n");
    }    


    // TODO 2012 SV motionDriverMaintainPosition();

    // wait for start
 //   setInitialPosition(color);

    // notify game strategy
 //   sendStrategyConfiguration(configValue);

    loopUntilStart(&waitForInstruction);

    // Enable the sonar Status only after start
    //setSonarStatus(configValue & CONFIG_USE_SONAR_MASK);

    // mark that match begins
    markStartMatch();

    // write begin of match
    showStarted(&pcOutputStream);

    if (homologationIndex == 0) {
        // MATCH

        while (1) {
            waitForInstruction();

            if (isEnd()) {
                break;
            }
        }
    } else {
        setReadyForNextMotion(true);

        while (1) {
            waitForInstruction();
            homologation(homologationIndex, color);

            // We stop if we are in homologation mode
            if (isRobotMustStop()) {
                motionDriverStop();
                break;
            }

            // ultimate tentative to restart the robot if it is blocked
            forceRobotNextStepIfNecessary();
        }
    }

    showEnd(&lcdOutputStream);

    while (1) {
        // Avoid reboot even at end
    }
}
