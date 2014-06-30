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

#include "mainBoardClient.h"


#include "../../common/delay/cenDelay.h"

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

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// TEST
#include "../../device/test/deviceTest.h"
#include "../../device/test/deviceTestInterface.h"

// SERVO
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// LCD
#include "../../drivers/lcd/lcd.h"
#include "../../drivers/lcd/lcd4d.h"
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
#include "../../device/adc/adcDeviceInterface.h"

// Beacon Receiver
#include "../../device/beacon/beaconReceiverDeviceInterface.h"

// Drivers

#include "../../drivers/io/pcf8574.h"
#include "../../drivers/test/driverTest.h"
#include "../../drivers/system/systemDriver.h"
#include "../../drivers/motion/motionDriver.h"
#include "../../drivers/motion/trajectoryDriver.h"
#include "../../drivers/motor/md22.h"
#include "../../drivers/driverTransmitter.h"
#include "../../drivers/strategy/strategyDriver.h"

// Robot
#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"
#include "../../robot/config/robotConfigDeviceInterface.h"
#include "../../robot/match/startMatchDetectorDevice.h"
#include "../../robot/match/startMatchDetectorDeviceInterface.h"
#include "../../robot/match/endMatchDetectorDevice.h"
#include "../../robot/match/endMatchDetectorDeviceInterface.h"

#include "../../robot/opponent/robotInfraredDetectorDeviceInterface.h"
#include "../../robot/opponent/robotInfraredDetectorDriver.h"
#include "../../robot/opponent/robotSonarDetectorDevice.h"
#include "../../robot/opponent/robotSonarDetectorDeviceInterface.h"
#include "../../robot/opponent/opponentRobot.h"

// Robot 2012
#include "../../robot/2012/homologation2012.h"
#include "../../robot/2012/armDeviceInterface2012.h"
#include "../../robot/2012/armDriver2012.h"

// Other boards interface
#include "../../main/motorBoard/motorBoard.h"
#include "../../main/meca1/mechanicalBoard1.h"
#include "../../main/meca2/mechanicalBoard2.h"
#include "../../main/beaconReceiver/beaconReceiverBoard.h"
#include "../../main/strategy/strategyMain.h"

#include "../../motion/simple/motion.h"

#include "../../robot/robot.h"

#include "../../drivers/sonar/srf02.h"

#ifndef MPLAB_SIMULATION
    #ifdef PROG_32
        #define SERIAL_PORT_DEBUG         SERIAL_PORT_2
        #define SERIAL_PORT_PC             SERIAL_PORT_1
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

// serial link LCD
/*
static Lcd4d lcd4d;
static char lcd4dInputBufferArray[MAIN_BOARD_LCD_INPUT_BUFFER_LENGTH];
static Buffer lcd4dInputBuffer;
static char lcd4dOutputBufferArray[MAIN_BOARD_LCD_OUTPUT_BUFFER_LENGTH];
static Buffer lcd4dOutputBuffer;
static OutputStream lcd4dOutputStream;
static StreamLink lcd4dSerialStreamLink;
*/

// both OutputStream as composite
static CompositeOutputStream compositePcAndDebugOutputStream;
static CompositeOutputStream compositeDriverAndDebugOutputStream;

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

// DISPATCHER I2C

// i2c->Motor
static DriverDataDispatcher motorI2cDispatcher;
static char motorBoardInputBufferArray[MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH];
static Buffer motorBoardInputBuffer;
static InputStream motorBoardInputStream;
static OutputStream motorBoardOutputStream;

// i2c->Mechanical 2
static DriverDataDispatcher mechanical2I2cDispatcher;
static char mechanical2BoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer mechanical2BoardInputBuffer;
static InputStream mechanical2BoardInputStream;
static OutputStream mechanical2BoardOutputStream;

// i2c->BeaconReceiver
static DriverDataDispatcher beaconReceiverI2cDispatcher;
static char beaconReceiverBoardInputBufferArray[MAIN_BOARD_LINK_TO_BEACON_BOARD_BUFFER_LENGTH];
static Buffer beaconReceiverBoardInputBuffer;
static InputStream beaconReceiverBoardInputStream;
static OutputStream beaconReceiverBoardOutputStream;

// i2c->Strategy
static DriverDataDispatcher strategyI2cDispatcher;
static char strategyBoardInputBufferArray[MAIN_BOARD_LINK_TO_STRATEGY_BOARD_BUFFER_LENGTH];
static Buffer strategyBoardInputBuffer;
static InputStream strategyBoardInputStream;
static OutputStream strategyBoardOutputStream;

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


// Specific 2012
static bool armOpen;

/**
 * Call-back when Data send some notification message (like Position Reached, Position failed ...)
 */
void mainBoardCallbackRawData(const Device* device,
        char header,
        InputStream* inputStream) {

//    if (header == NOTIFY_MOTION_STATUS || header == COMMAND_NOTIFY_TEST || header == COMMAND_PLIERS_2011_OPEN) {
    // MOTOR BOARD notification
    if (header == NOTIFY_MOTION_STATUS) {
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
    }
    // STRATEGY BOARD notification message of MOTOR => Must be relayed TO MOTOR
    else if (header == COMMAND_MOTION_SPLINE_ABSOLUTE || header == COMMAND_MOTION_SPLINE_RELATIVE) {
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
    } else if (header == COMMAND_MOTION_LEFT_IN_DECI_DEGREE || header == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        appendString(getOutputStreamLogger(INFO), "Notification : Rotation : From STRATEGY BOARD : relayed to MOTOR_BOARD \n");
        instructionType = INSTRUCTION_TYPE_ROTATION;
        forwardCallbackRawDataTo(inputStream, &(compositeDriverAndDebugOutputStream.outputStream), device, header, DEVICE_MODE_INPUT);
        transmitFromDriverRequestBuffer();
    } 
    // When Strategy ask by notification message to arm up or Down
    else if (header == COMMAND_ARM_2012_UP || header == COMMAND_ARM_2012_DOWN) {
        armOpen = (header == COMMAND_ARM_2012_DOWN);
        appendString(getOutputStreamLogger(INFO), "\nNotification : From STRATEGY BOARD : relayed to MECHANICAL BOARD :\n");
        instructionType = INSTRUCTION_TYPE_NO_MOVE;

        forwardCallbackRawDataTo(inputStream, &(compositeDriverAndDebugOutputStream.outputStream), device, header, DEVICE_MODE_INPUT);
        transmitFromDriverRequestBuffer();
        delaymSec(500);
        // we are ready for next motion
        setReadyForNextMotion(true);
    } 
    // Mechanical Board notification
    else if (header == NOTIFY_INFRARED_DETECTOR_DETECTION) {
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
    addDriver(driverTestGetDescriptor(), TRANSMIT_LOCAL);

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

    // Local
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    // addLocalDevice(&servoDevice, getServoDeviceInterface(), getServoDeviceDescriptor());
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor());
    addLocalDevice(getStartMatchDetectorDeviceInterface(), getStartMatchDetectorDeviceDescriptor());
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor());
    addLocalDevice(getSonarDeviceInterface(), getSonarDeviceDescriptor());
    addLocalDevice(getRobotSonarDetectorDeviceInterface(), getRobotSonarDetectorDeviceDescriptor());

    // Mechanical Board 2->I2C
    Device* armDevice = addI2CRemoteDevice(getArm2012DeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);
    Device* infraredDetectorDevice = addI2CRemoteDevice(getRobotInfraredDetectorDeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);

    // Motor Board->I2C
    addI2CRemoteDevice(getPIDDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(getMotorDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(getCodersDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    Device* trajectoryDevice = addI2CRemoteDevice(getTrajectoryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    Device* motionDevice = addI2CRemoteDevice(getMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);


    // Beacon Receiver Board->I2C
    addI2CRemoteDevice(getBeaconReceiverDeviceInterface(), BEACON_RECEIVER_I2C_ADDRESS);

    // Strategy Board->I2C
    addI2CRemoteDevice(getStrategyDeviceInterface(), STRATEGY_BOARD_I2C_ADDRESS);


    // Init the devices
    initDevices();  

    // Manage the callback notification
    trajectoryDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // testDevice.deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    motionDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    armDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    infraredDetectorDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
}

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

    /*
    // Listen instructions from Devices (I2C Slave) -> Main Board (I2C Master)
    while (handleNotificationFromDispatcherList(TRANSMIT_I2C)) {
        // loop for all notification
        // notification handler must avoid to directly information in notification callback
        // and never to the call back device
    }

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
    setPicName("MAIN BOARD");

    setRobotMustStop(false);
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
            0);

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
            0);

    /*
    // Opens the serial link for the lcd
    openSerialLink(&lcd4dSerialStreamLink,
                    &lcd4dInputBuffer,
                    &lcd4dInputBufferArray,
                    MAIN_BOARD_LCD_INPUT_BUFFER_LENGTH,
                    &lcd4dOutputBuffer,
                    &lcd4dOutputBufferArray,
                    MAIN_BOARD_LCD_OUTPUT_BUFFER_LENGTH,
                    &lcd4dOutputStream,
                    SERIAL_PORT_LCD,
                    9600);

     */
    
    // LCD (LCD03 via Serial interface)
    initLCDOutputStream(&lcdOutputStream);

    initTimerList(&timerListArray, MAIN_BOARD_TIMER_LENGTH);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&debugSerialLogHandler, "UART", &debugOutputStream, DEBUG);
    addLogHandler(&lcdLogHandler, "LCD", &lcdOutputStream, ERROR);

    appendString(getOutputStreamLogger(ALWAYS), getPicName());
    println(getOutputStreamLogger(ALWAYS));

    // appendString(&pcOutputStream, getPicName());
    // println(&pcOutputStream);

    appendString(&debugOutputStream, getPicName());
    println(&debugOutputStream);

    initDevicesDescriptor();
    initDriversDescriptor();

    // Initializes the opponent robot
    initOpponentRobot();

    // Creates a composite to notify both PC and Debug
    initCompositeOutputStream(&compositePcAndDebugOutputStream);
    addOutputStream(&compositePcAndDebugOutputStream, &debugOutputStream);
    addOutputStream(&compositePcAndDebugOutputStream, &pcOutputStream);

    // Creates a composite to redirect to driverRequest and Debug
    initCompositeOutputStream(&compositeDriverAndDebugOutputStream);
    addOutputStream(&compositeDriverAndDebugOutputStream, &debugOutputStream);
    addOutputStream(&compositeDriverAndDebugOutputStream, getDriverRequestOutputStream());

    appendString(&debugOutputStream, "DEBUG");
//     appendString(&pcOutputStream, "PC");


    /*
    delaymSec(1500);
    appendString(&debugOutputStream, "Printing U");
    appendString(&pcOutputStream, "U");

    delaymSec(2000);
    appendString(&debugOutputStream, "Printing E");
    appendString(&pcOutputStream, "E");
    delaymSec(500);
    appendString(&debugOutputStream, "Printing E");
    appendString(&pcOutputStream, "E");
    delaymSec(500);
    appendString(&debugOutputStream, "Printing VV");
    appendString(&pcOutputStream, "VV");
    
    while (1) {

    }
    */

    // Start interruptions
    startTimerList();

    // Configure data dispatcher
    addLocalDriverDataDispatcher();

    // Stream for motorBoard
    addI2CDriverDataDispatcher(&motorI2cDispatcher,
            "MOTOR_BOARD_DISPATCHER",
            &motorBoardInputBuffer,
            &motorBoardInputBufferArray,
            MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH,
            &motorBoardOutputStream,
            &motorBoardInputStream,
            MOTOR_BOARD_I2C_ADDRESS);
    
    // Stream for Mechanical Board 2
    addI2CDriverDataDispatcher(&mechanical2I2cDispatcher,
            "MECHANICAL_BOARD_2_DISPATCHER",
            &mechanical2BoardInputBuffer,
            &mechanical2BoardInputBufferArray,
            MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH,
            &mechanical2BoardOutputStream,
            &mechanical2BoardInputStream,
            MECHANICAL_BOARD_2_I2C_ADDRESS);

    // printDeviceList(getOutputStreamLogger(DEBUG));
    // printDriverDataDispatcherList(getOutputStreamLogger(DEBUG), getDispatcherList());

    /* PROG 32

    // Stream for Beacon Receiver Board
    addI2CDriverDataDispatcher( &beaconReceiverI2cDispatcher,
                                                            "BEACON_RECEIVER_DISPATCHER",
                                                            &beaconReceiverBoardInputBuffer,
                                                            &beaconReceiverBoardInputBufferArray,
                                                            MAIN_BOARD_LINK_TO_BEACON_BOARD_BUFFER_LENGTH,
                                                            &beaconReceiverBoardOutputStream,
                                                            &beaconReceiverBoardInputStream,
                                                            BEACON_RECEIVER_I2C_ADDRESS);

    // Stream for Strategy Board
    addI2CDriverDataDispatcher( &strategyI2cDispatcher,
                                                            "STRATEGY_DISPATCHER",
                                                            &strategyBoardInputBuffer,
                                                            &strategyBoardInputBufferArray,
                                                            MAIN_BOARD_LINK_TO_STRATEGY_BOARD_BUFFER_LENGTH,
                                                            &strategyBoardOutputStream,
                                                            &strategyBoardInputStream,
                                                            STRATEGY_BOARD_I2C_ADDRESS);

    // printDriverDataDispatcherList(getOutputStreamLogger(DEBUG), getDispatcherList());
    */

        /*
    appendString(getOutputStreamLogger(ALWAYS), "Init LCD:");
    initLcd4d(&lcd4d, &(lcd4dOutputStream), &(lcd4dInputBuffer.inputStream), &lcd4dInputBuffer);
    delaymSec(5000);

    setAutoBaud(&lcd4d);
    delaymSec(1000);

    appendString(getOutputStreamLogger(ERROR), "CLS\n");
    Lcd4dVersion version;
    Point point;
    lcd4dTouchControl(&lcd4d, true);

    delaymSec(500);

    lcd4dClearScreen(&lcd4d);
    delaymSec(500);
    appendString(getOutputStreamLogger(ERROR), "INIT MEMORY\n");
    lcd4dInitializeMemoryCardFAT(&lcd4d);
    delaymSec(500);
    
    appendString(getOutputStreamLogger(ERROR), "READ WAV\n");
    lcd4dPlayAudioWAVFileFromCardFAT(&lcd4d, LCD4D_PLAY_WAV_OPTION_RETURN_IMMEDIATELY, "test.wav");
    delaymSec(4000);

    appendString(getOutputStreamLogger(ERROR), "DISPLAY IMAGE\n");
    lcd4dDisplayImageIconFromCardFAT(&lcd4d, 0, 0, "CybeLogo.Gci", 0L);
    delaymSec(4000);

    lcd4dSetDisplayResolution(&lcd4d, LCD4D_ORIENTATION_270);

    
    // appendString(getOutputStreamLogger(ERROR), "READ FILE LIST\n");
    // lcddListDirectoryOfCardFAT(&lcd4d, "test.wav", getOutputStreamLogger(ERROR));
    // appendString(getOutputStreamLogger(ERROR), "SCREEN COPY SAVE\n");
    // lcd4dScreenCopySaveToCardFAT(&lcd4d, 0, 0, 320, 240, "screenDat.bmp");

    while (1) {
        delaymSec(500);

        lcd4dClearScreen(&lcd4d);
        delaymSec(500);
    */
        /*
        getLcd4dVersionCommand(&lcd4d, &version);
        delaymSec(500);
        lcd4dPrintVersion(getOutputStreamLogger(ERROR), &version);
        */

        /*
        delaymSec(500);
        lcd4dDisplay(&lcd4d, true);
        delaymSec(500);
        lcd4dDisplay(&lcd4d, false);
        */
        /*
        lcd4dSetPenType(&lcd4d, LCD4D_PEN_SIZE_DRAW_SOLID);
        lcd4dDrawEllipse(&lcd4d, 100, 100, 50, 100);
        delaymSec(500);

        lcd4dSetPenType(&lcd4d, LCD4D_PEN_SIZE_DRAW_WIRE_FRAME);
        lcd4dDrawEllipse(&lcd4d, 200, 200, 30, 30);
        delaymSec(500);
        */
        /*
        lcd4dSetFont(&lcd4d, LCD4D_FONT_LARGEST);
        delaymSec(500);
        lcd4dDrawChar(&lcd4d, '8', 10, 10);
        delaymSec(500);
        lcd4dDrawGraphicChar(&lcd4d, '7', 50, 200, 2, 2);
        delaymSec(200);
        lcd4dDrawString(&lcd4d, 10, 10, LCD4D_FONT_LARGEST, "Hello");
        delaymSec(200);
        lcd4dDrawGraphicString(&lcd4d, 50, 200, LCD4D_FONT_LARGEST, 2, 2, " World");

#define        LCD4D_GET_TOUCH_COORDINATES_COMMAND        'o'
#define        LCD4D_TOUCH_WAIT_UNTIL_ANY_TOUCH        0x00
#define        LCD4D_TOUCH_WAIT_PRESS                    0x01
#define        LCD4D_TOUCH_WAIT_RELEASE                0x02
#define        LCD4D_TOUCH_WAIT_MOVING                    0x03
#define        LCD4D_TOUCH_GET_STATUS                    0x04
#define        LCD4D_TOUCH_GET_COORDINATES                0x05

                 *         bool result = lcd4dWaitUntilTouch(&lcd4d, 5000);
        if (result) {
            lcd4dWaitTouchAndGetTouchCoordinates(&lcd4d, LCD4D_TOUCH_GET_COORDINATES, &point);
            appendStringAndDec(getOutputStreamLogger(ERROR), "x=", point.x);
            println(getOutputStreamLogger(ERROR));
            appendStringAndDec(getOutputStreamLogger(ERROR), "y=", point.y);
            println(getOutputStreamLogger(ERROR));
            lcd4dDrawEllipse(&lcd4d, point.x, point.y, 10, 10);
            delaymSec(1000);
        }
    }
        */

    while (1) {
        waitForInstruction();
    }

    // pingDriverDataDispatcherList(getOutputStreamLogger(DEBUG));

    // Inform PC waiting
    showWaitingStart(&pcOutputStream);

    // wait other board initialization
    delaymSec(1500);

    //initStrategyDriver();

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

    /*
    if (configValue & CONFIG_SPEED_LOW_MASK) {
        motionSetParameters(MOTION_TYPE_FORWARD_OR_BACKWARD, 0x0C, 0x24);
        motionSetParameters(MOTION_TYPE_ROTATION, 0x12, 0x24);
        motionSetParameters(MOTION_TYPE_ROTATION_ONE_WHEEL, 0x08, 0x08);
        appendString(getOutputStreamLogger(ALWAYS), "SPEED LOW\n");
    } else if (configValue & CONFIG_SPEED_VERY_LOW_MASK) {
        motionSetParameters(MOTION_TYPE_FORWARD_OR_BACKWARD, 0x08, 0x10);
        motionSetParameters(MOTION_TYPE_ROTATION, 0x08, 0x10);
        motionSetParameters(MOTION_TYPE_ROTATION_ONE_WHEEL, 0x08, 0x08);
        appendString(getOutputStreamLogger(ALWAYS), "SPEED VERY LOW\n");
    } else if (configValue & CONFIG_SPEED_ULTRA_LOW_MASK) {
        motionSetParameters(MOTION_TYPE_FORWARD_OR_BACKWARD, 0x06, 0x06);
        motionSetParameters(MOTION_TYPE_ROTATION, 0x04, 0x04);
        motionSetParameters(MOTION_TYPE_ROTATION_ONE_WHEEL, 0x04, 0x04);
        appendString(getOutputStreamLogger(ALWAYS), "SPEED ULTRA LOW\n");
    } else {
        motionSetParameters(MOTION_TYPE_FORWARD_OR_BACKWARD, 0x12, 0x36);
        motionSetParameters(MOTION_TYPE_ROTATION, 0x16, 0x16);
        motionSetParameters(MOTION_TYPE_ROTATION_ONE_WHEEL, 0x12, 0x10);
        appendString(getOutputStreamLogger(ALWAYS), "SPEED NORMAL \n");
    }
    */

    while (1) {
        waitForInstruction();
    }



    // TODO 2012 SV motionDriverMaintainPosition();

    // wait for start
    setInitialPosition(color);

    // notify game strategy
    sendStrategyConfiguration(configValue);

    loopUntilStart(&waitForInstruction);

    // Enable the sonar Status only after start
    setSonarStatus(configValue & CONFIG_USE_SONAR_MASK);

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
