#include <i2c.h>
#include <stdlib.h>

#include "mainBoardClient.h"

#include "../../common/setup/pic30FSetup.h"

#include "../../common/delay/delay30F.h"

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

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/pwm/pwmPic.h"

#include "../../common/serial/serial.h"
#include "../../common/serial/serialLink.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

#include "../../device/device.h"
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

#include "../../robot/robotSonarDetectorDevice.h"
#include "../../robot/robotSonarDetectorDeviceInterface.h"


// Robot 2012
#include "../../robot/2012/homologation2012.h"
#include "../../robot/2012/armDeviceInterface2012.h"

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
#define SERIAL_PORT_DEBUG 		SERIAL_PORT_1
#define SERIAL_PORT_PC	 		SERIAL_PORT_2
#else
// We use the same port for both
#define SERIAL_PORT_PC	 		SERIAL_PORT_1
#define SERIAL_PORT_DEBUG 		SERIAL_PORT_1
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

OutputStream* getPcOutputStream() {
    return &pcOutputStream;
}

/**
 * Call-back when Data send some notification message (like Position Reached, Position failed ...)
 */
void mainBoardCallbackRawData(const Device* device,
        char header,
        InputStream* inputStream) {

//    if (header == NOTIFY_MOTION_STATUS || header == COMMAND_NOTIFY_TEST || header == COMMAND_PLIERS_2011_OPEN) {
    if (header == NOTIFY_MOTION_STATUS || header == COMMAND_NOTIFY_TEST) {
        forwardCallbackRawDataTo(inputStream, &(compositePcAndDebugOutputStream.outputStream), device, header, DEVICE_MODE_OUTPUT);
        // ready for next motion instruction Index
        setReadyForNextMotion(TRUE);
    }
	// When Strategy ask by notification message to go somewhere
	else if (header == COMMAND_MOTION_SPLINE_ABSOLUTE || header == COMMAND_MOTION_SPLINE_RELATIVE 
			 || header == COMMAND_MOTION_LEFT_IN_DECI_DEGREE || header == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
		forwardCallbackRawDataTo(inputStream, &(compositeDriverAndDebugOutputStream.outputStream), device, header, DEVICE_MODE_INPUT);
		transmitFromDriverRequestBuffer();
	} 
	// When Strategy ask by notification message to arm up or Down
	else if (header == COMMAND_ARM_2012_UP || header == COMMAND_ARM_2012_DOWN) {
		forwardCallbackRawDataTo(inputStream, &(compositeDriverAndDebugOutputStream.outputStream), device, header, DEVICE_MODE_INPUT);
		transmitFromDriverRequestBuffer();
		// we are ready for next motion
        setReadyForNextMotion(TRUE);
	} 
	else {
	    appendString(getOutputStreamLogger(ERROR), "Notification lost:");
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
    setPicName("MAIN BOARD");

    // Local
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    // addLocalDevice(&servoDevice, getServoDeviceInterface(), getServoDeviceDescriptor());
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor());
    addLocalDevice(getStartMatchDetectorDeviceInterface(), getStartMatchDetectorDeviceDescriptor());
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor());
    addLocalDevice(getSonarDeviceInterface(), getSonarDeviceDescriptor());
    addLocalDevice(getRobotSonarDetectorDeviceInterface(), getRobotSonarDetectorDeviceDescriptor());

    // Motor Board->I2C
    addI2CRemoteDevice(getPIDDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(getMotorDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(getCodersDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    Device* trajectoryDevice = addI2CRemoteDevice(getTrajectoryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    Device* motionDevice = addI2CRemoteDevice(getMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);

    // Mechanical Board 2->I2C
    Device* armDevice = addI2CRemoteDevice(getArm2012DeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);

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
    // printDeviceListUsage(getOutputStreamLogger(INFO));
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

    // Listen instructions from Devices (I2C Slave) -> Main Board (I2C Master)
    handleNotificationFromDispatcherList(TRANSMIT_I2C);
	
	/*
    delaymSec(10);

    if (notifyObstacle()) {
        appendString(getOutputStreamLogger(ALWAYS), "Obstacle !\n");
        setRobotMustStop(TRUE);
    }
	*/
}

int main(void) {

    setRobotMustStop(FALSE);
    // Open the serial Link for debug
    openSerialLink(&debugSerialStreamLink,
            &debugInputBuffer,
            &debugInputBufferArray,
			MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH,
            &debugOutputBuffer,
			&debugOutputBufferArray,
			MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH,
            &debugOutputStream,
            SERIAL_PORT_DEBUG);

    // Open the serial Link for the PC
    openSerialLink(&pcSerialStreamLink,
            &pcInputBuffer,
			&pcInputBufferArray,
			MAIN_BOARD_PC_INPUT_BUFFER_LENGTH,
            &pcOutputBuffer,
			&pcOutputBufferArray,
			MAIN_BOARD_PC_OUTPUT_BUFFER_LENGTH,
            &pcOutputStream,
            SERIAL_PORT_PC);

    // LCD
    initLCDOutputStream(&lcdOutputStream);

	initTimerList(&timerListArray, MAIN_BOARD_TIMER_LENGTH);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&debugSerialLogHandler, "UART", &debugOutputStream, DEBUG);
    addLogHandler(&lcdLogHandler, "LCD", &lcdOutputStream, ERROR);

    appendString(getOutputStreamLogger(ALWAYS), "MAIN BOARD CLIENT");
    println(getOutputStreamLogger(ALWAYS));

    initDevicesDescriptor();
    initDriversDescriptor();

    // Creates a composite to notify both PC and Debug
    initCompositeOutputStream(&compositePcAndDebugOutputStream);
    addOutputStream(&compositePcAndDebugOutputStream, &debugOutputStream);
    addOutputStream(&compositePcAndDebugOutputStream, &pcOutputStream);

    // Creates a composite to redirect to driverRequest and Debug
    initCompositeOutputStream(&compositeDriverAndDebugOutputStream);
    addOutputStream(&compositeDriverAndDebugOutputStream, &debugOutputStream);
    addOutputStream(&compositeDriverAndDebugOutputStream, getDriverRequestOutputStream());

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
            &motorBoardInputStream,
            &motorBoardOutputStream,
            MOTOR_BOARD_I2C_ADDRESS);
	
    // Stream for Mechanical Board 2
    addI2CDriverDataDispatcher(&mechanical2I2cDispatcher,
            "MECHANICAL_BOARD_2_DISPATCHER",
            &mechanical2BoardInputBuffer,
			&mechanical2BoardInputBufferArray,
			MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH,
            &mechanical2BoardInputStream,
            &mechanical2BoardOutputStream,
            MECHANICAL_BOARD_2_I2C_ADDRESS);

    // Stream for Beacon Receiver Board
    addI2CDriverDataDispatcher( &beaconReceiverI2cDispatcher,
                                                            "BEACON_RECEIVER_DISPATCHER",
                                                            &beaconReceiverBoardInputBuffer,
															&beaconReceiverBoardInputBufferArray,
															MAIN_BOARD_LINK_TO_BEACON_BOARD_BUFFER_LENGTH,
                                                            &beaconReceiverBoardInputStream,
                                                            &beaconReceiverBoardOutputStream,
                                                            BEACON_RECEIVER_I2C_ADDRESS);

    // Stream for Strategy Board
    addI2CDriverDataDispatcher( &strategyI2cDispatcher,
                                                            "STRATEGY_DISPATCHER",
                                                            &strategyBoardInputBuffer,
															&strategyBoardInputBufferArray,
															MAIN_BOARD_LINK_TO_STRATEGY_BOARD_BUFFER_LENGTH,
                                                            &strategyBoardInputStream,
                                                            &strategyBoardOutputStream,
                                                            STRATEGY_BOARD_I2C_ADDRESS);

    // printDriverDataDispatcherList(getOutputStreamLogger(DEBUG), getDispatcherList());

    // pingDriverDataDispatcherList(getOutputStreamLogger(DEBUG));

    // Inform PC waiting
    showWaitingStart(&pcOutputStream);

	// wait other board initialization
    delaymSec(1000);

	// 2012 VALUE
    int configValue = getConfigValue();
    unsigned int homologationIndex = configValue & CONFIG_STRATEGY_MASK;
    unsigned int color = configValue & CONFIG_COLOR_BLUE_MASK;
	appendString(getOutputStreamLogger(ALWAYS), "Homologation:");
	appendDec(getOutputStreamLogger(ALWAYS), homologationIndex);
	appendCRLF(getOutputStreamLogger(ALWAYS));
	if (color != 0) {
		appendString(getOutputStreamLogger(ALWAYS), "COLOR:VIOLET\n");
	}
	else {
		appendString(getOutputStreamLogger(ALWAYS), "COLOR:RED\n");
	}
	
    if (configValue & CONFIG_SPEED_LOW_MASK) {
        motionSetParameters(MOTION_TYPE_FORWARD_OR_BACKWARD, 0x10, 0x20);
        motionSetParameters(MOTION_TYPE_ROTATION, 0x10, 0x20);
        motionSetParameters(MOTION_TYPE_ROTATION_ONE_WHEEL, 0x08, 0x08);
    } else if (configValue & CONFIG_SPEED_VERY_LOW_MASK) {
        motionSetParameters(MOTION_TYPE_FORWARD_OR_BACKWARD, 0x08, 0x10);
        motionSetParameters(MOTION_TYPE_ROTATION, 0x08, 0x10);
        motionSetParameters(MOTION_TYPE_ROTATION_ONE_WHEEL, 0x08, 0x08);
    } else {
        motionSetParameters(MOTION_TYPE_FORWARD_OR_BACKWARD, 0x24, 0x40);
        motionSetParameters(MOTION_TYPE_ROTATION, 0x28, 0x18);
        motionSetParameters(MOTION_TYPE_ROTATION_ONE_WHEEL, 0x12, 0x10);
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
        setReadyForNextMotion(TRUE);

        while (1) {
            waitForInstruction();
            homologation(homologationIndex, color);

            // Listen instructions from Devices (I2C Slave) -> Main Board (I2C Master)
            handleNotificationFromDispatcherList(TRANSMIT_I2C);

            // We stop if we are in homologation mode
            if (isRobotMustStop()) {
				motionDriverStop();
                break;
            }
        }
    }

    showEnd(&lcdOutputStream);

    while (1) {
        // Avoid reboot even at end
    }
}
