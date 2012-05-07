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

#ifndef MPBLAB_SIMULATION
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
static CompositeOutputStream pcAndDebugOutputStream;

// i2c->Motor
static DriverDataDispatcher motorI2cDispatcher;
static char motorBoardInputBufferArray[MAIN_BOARD_LINK_TO_MOTOR_BOARD_BUFFER_LENGTH];
static Buffer motorBoardInputBuffer;
static InputStream motorBoardInputStream;
static OutputStream motorBoardOutputStream;

// DRIVER

// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

// DISPATCHER

// i2c->Mechanical 1
/*
static DriverDataDispatcher mechanical1I2cDispatcher;
static Buffer mechanical1BoardInputBuffer;
static InputStream mechanical1BoardInputStream;
static OutputStream mechanical1BoardOutputStream;
*/

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

// i2c->BeaconReceiver
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
// static Device testDevice;
static Device systemDevice;
static Device lcdDevice;
// static Device servoDevice;
static Device robotConfigDevice;
static Device startMatchDetectorDevice;
static Device endMatchDetectorDevice;
static Device sonarDevice;
static Device robotSonarDevice;

static Device pidDevice;
static Device motorDevice;
static Device codersDevice;
static Device trajectoryDevice;
static Device motionDevice;
static Device beaconReceiverDevice;
static Device strategyDevice;


// Specific 2012
static Device armDevice;
// static Device adcDevice;

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
        forwardCallbackRawDataTo(inputStream, &(pcAndDebugOutputStream.outputStream), device, header);
        // ready for next motion instruction Index
        setReadyForNextMotion(TRUE);
        return;
    }
    appendString(getOutputStreamLogger(ERROR), "Notification lost:");
    append(getOutputStreamLogger(ERROR), header);
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
    // Test & System
    // addI2CRemoteDevice(&testDevice, getTestDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addLocalDevice(&systemDevice, getSystemDeviceInterface(), getSystemDeviceDescriptor());
    setPicName("MAIN BOARD");

    // Local
    addLocalDevice(&lcdDevice, getLCDDeviceInterface(), getLCDDeviceDescriptor());
    // addLocalDevice(&servoDevice, getServoDeviceInterface(), getServoDeviceDescriptor());
    addLocalDevice(&robotConfigDevice, getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor());
    addLocalDevice(&startMatchDetectorDevice, getStartMatchDetectorDeviceInterface(), getStartMatchDetectorDeviceDescriptor());
    addLocalDevice(&endMatchDetectorDevice, getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor());
    addLocalDevice(&sonarDevice, getSonarDeviceInterface(), getSonarDeviceDescriptor());
    addLocalDevice(&robotSonarDevice, getRobotSonarDetectorDeviceInterface(), getRobotSonarDetectorDeviceDescriptor());

    // Motor Board->I2C
    addI2CRemoteDevice(&pidDevice, getPIDDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(&motorDevice, getMotorDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(&codersDevice, getCodersDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(&trajectoryDevice, getTrajectoryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2CRemoteDevice(&motionDevice, getMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);

    // Mechanical Board 1->I2C
    // addI2CRemoteDevice(&pliersDevice, getPliers2011DeviceInterface(), MECHANICAL_BOARD_1_I2C_ADDRESS);

    // Mechanical Board 2->I2C
 	addI2CRemoteDevice(&armDevice, getArm2012DeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);
    // addI2CRemoteDevice(&adcDevice, getADCDeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);

    // Beacon Receiver Board->I2C
    addI2CRemoteDevice(&beaconReceiverDevice, getBeaconReceiverDeviceInterface(), BEACON_RECEIVER_I2C_ADDRESS);

    // Strategy Board->I2C
    addI2CRemoteDevice(&strategyDevice, getStrategyDeviceInterface(), STRATEGY_BOARD_I2C_ADDRESS);


    // Init the devices
    initDevices();  

    // Manage the callback notification
    trajectoryDevice.deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // testDevice.deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    motionDevice.deviceHandleCallbackRawData = &mainBoardCallbackRawData;

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

    delaymSec(10);

    if (notifyObstacle()) {
        appendString(getOutputStreamLogger(ALWAYS), "Obstacle !\n");
        setRobotMustStop(TRUE);
    }
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

    // Creates a composite to notify both PC and Debug
    initCompositeOutputStream(&pcAndDebugOutputStream);
    addOutputStream(&pcAndDebugOutputStream, &debugOutputStream);
    addOutputStream(&pcAndDebugOutputStream, &pcOutputStream);

    // LCD
    initLCDOutputStream(&lcdOutputStream);

    // Init the logs
    initLog(DEBUG);
    addLogHandler(&debugSerialLogHandler, "UART", &debugOutputStream, DEBUG);
    addLogHandler(&lcdLogHandler, "LCD", &lcdOutputStream, ERROR);

    appendString(getOutputStreamLogger(ALWAYS), "MAIN BOARD CLIENT");
    println(getOutputStreamLogger(ALWAYS));

    initDevicesDescriptor();
    initDriversDescriptor();

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

    // Stream for Mechanical Board 1
	/*
    addI2CDriverDataDispatcher(&mechanical1I2cDispatcher,
            "MECHANICAL_BOARD_1_DISPATCHER",
            &mechanical1BoardInputBuffer,
            &mechanical1BoardInputStream,
            &mechanical1BoardOutputStream,
            MECHANICAL_BOARD_1_I2C_ADDRESS);
	*/

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
