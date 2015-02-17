#include "../../common/commons.h"

#include <plib.h>
#include "../../common/setup/32/picSetup32.h"

#include <stdlib.h>
#include <math.h>

#include "mainBoardClient.h"


#include "../../common/delay/cenDelay.h"

#include "../../common/eeprom/eeprom.h"

#include "../../common/i2c/i2cCommon.h"
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

// DATA DISPATCHER
#include "../../device/dispatcher/dataDispatcherDevice.h"
#include "../../device/dispatcher/dataDispatcherDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// SERIAL
#include "../../device/serial/serialDebugDevice.h"
#include "../../device/serial/serialDebugDeviceInterface.h"

// TIMER
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// LOG
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// I2C MASTER DEBUG
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// TEST
#include "../../device/test/testDevice.h"
#include "../../device/test/testDeviceInterface.h"

// TEST
#include "../../device/test/test2Device.h"
#include "../../device/test/test2DeviceInterface.h"

// TIMER
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// SENSOR->TEMPERATURE
#include "../../device/sensor/temperature/temperatureSensorDevice.h"
#include "../../device/sensor/temperature/temperatureSensorDeviceInterface.h"

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

// Air conditioning
#include "../../device/airconditioning/airConditioningDeviceInterface.h"

// Beacon Receiver
#include "../../device/beacon/beaconReceiverDeviceInterface.h"

// Drivers
#include "../../drivers/clock/PCF8563.h"
#include "../../drivers/eeprom/24c512.h"
#include "../../drivers/io/pcf8574.h"
#include "../../drivers/test/testDriver.h"
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
#include "../../robot/config/32/robotConfigPic32.h"

#include "../../robot/match/startMatchDetector.h"
#include "../../robot/match/32/startMatchDetector32.h"
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
#include "../../main/motorBoard/motorBoard.h"
#include "../../main/meca1/mechanicalBoard1.h"
#include "../../main/meca2/mechanicalBoard2.h"
#include "../../main/airconditioning/airConditioningMain.h"

#include "../../motion/simple/motion.h"

#include "../../robot/robot.h"

#include "../../drivers/sonar/srf02.h"

#define SERIAL_PORT_DEBUG         SERIAL_PORT_2 
#define SERIAL_PORT_PC            SERIAL_PORT_6
#define SERIAL_PORT_MOTOR         SERIAL_PORT_5

// EEPROM
static Eeprom eeprom;

// CLOCK
static Clock clock;

// I2C
static I2cBus i2cBus;

// serial link DEBUG 
static char debugInputBufferArray[MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;

// StartMatchDetector
static StartMatchDetector startMatchDetector;

// serial link Motor
static char motorInputBufferArray[MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH];
static Buffer motorInputBuffer;
static char motorOutputBufferArray[MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH];
static Buffer motorOutputBuffer;
static OutputStream motorOutputStream;
static StreamLink motorSerialStreamLink;

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

static DriverDataDispatcher driverDataDispatcherListArray[MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH];

// i2c->Motor
static char motorBoardI2cInputBufferArray[MAIN_BOARD_I2C_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH];
static Buffer motorBoardI2cInputBuffer;
static InputStream motorBoardI2cInputStream;
static OutputStream motorBoardI2cOutputStream;

// i2c->Air Conditioning
static char airConditioningBoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer airConditioningBoardInputBuffer;
static InputStream airConditioningBoardInputStream;
static OutputStream airConditioningBoardOutputStream;

// i2c->Mechanical 2
/*
static char mechanical2BoardInputBufferArray[MAIN_BOARD_LINK_TO_MECA_BOARD_2_BUFFER_LENGTH];
static Buffer mechanical2BoardInputBuffer;
static InputStream mechanical2BoardInputStream;
static OutputStream mechanical2BoardOutputStream;
*/

// DISPATCHER UART
// uart->Motor
// static char motorBoardUartInputBufferArray[MAIN_BOARD_UART_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH];
// static Buffer motorBoardUartInputBuffer;
// static InputStream motorBoardUartInputStream;
// static OutputStream motorBoardUartOutputStream;

// Robot Configuration
static RobotConfig robotConfig;

// lcd DEBUG 
static OutputStream lcdOutputStream;

// Logs
static LogHandler logHandlerListArray[MAIN_BOARD_LOG_HANDLER_LIST_LENGTH];

// Devices
static Device deviceListArray[MAIN_BOARD_DEVICE_LENGTH];

// Timers
static Timer timerListArray[MAIN_BOARD_TIMER_LENGTH];

// Obstacle management
// static bool mustNotifyObstacle;
// static unsigned int instructionType;
// static bool useInfrared;
// static bool useBalise;

#define INSTRUCTION_TYPE_NO_MOVE        0
#define INSTRUCTION_TYPE_FORWARD        1
#define INSTRUCTION_TYPE_BACKWARD        2
#define INSTRUCTION_TYPE_ROTATION        3

/**
 * @private
 */
void initDriversDescriptor() {
    // Init the drivers
    initDrivers(&driverRequestBuffer, &driverRequestBufferArray, MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH,
                &driverResponseBuffer, &driverResponseBufferArray, MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH);

    // Get test driver for debug purpose
    addDriver(testDriverGetDescriptor(), TRANSMIT_LOCAL);

    // Direct Devantech Driver
    addDriver(getMD22DriverDescriptor(&i2cBus), TRANSMIT_NONE);
}

/**
 * @private
 */
void initDevicesDescriptor() {
    initDeviceList(&deviceListArray, MAIN_BOARD_DEVICE_LENGTH);

    // SYSTEM & DEBUG
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getTest2DeviceInterface(), getTest2DeviceDescriptor());
    addLocalDevice(getDataDispatcherDeviceInterface(), getDataDispatcherDeviceDescriptor());
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());

    // LOCAL
    addLocalDevice(getLCDDeviceInterface(), getLCDDeviceDescriptor());
    // addLocalDevice(&servoDevice, getServoDeviceInterface(), getServoDeviceDescriptor());
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor(&robotConfig));

    initStartMatchDetector32(&startMatchDetector);
    addLocalDevice(getStartMatchDetectorDeviceInterface(), getStartMatchDetectorDeviceDescriptor(&startMatchDetector));
    addLocalDevice(getEndMatchDetectorDeviceInterface(), getEndMatchDetectorDeviceDescriptor());
    addLocalDevice(getSonarDeviceInterface(), getSonarDeviceDescriptor(&i2cBus));
    addLocalDevice(getRobotSonarDetectorDeviceInterface(), getRobotSonarDetectorDeviceDescriptor(&i2cBus));
    addLocalDevice(getTemperatureSensorDeviceInterface(), getTemperatureSensorDeviceDescriptor(&i2cBus));
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));

    // Mechanical Board 2->I2C
    // Device* armDevice = addI2cRemoteDevice(getArm2012DeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);
    // Device* infraredDetectorDevice = addI2cRemoteDevice(getRobotInfraredDetectorDeviceInterface(), MECHANICAL_BOARD_2_I2C_ADDRESS);

    // Motor Board->I2C
    addI2cRemoteDevice(getTestDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getMotorDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getCodersDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getPIDDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getTrajectoryDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);
    addI2cRemoteDevice(getMotionDeviceInterface(), MOTOR_BOARD_I2C_ADDRESS);

    // MOTOR BOARD -> UART
    /*
    addUartRemoteDevice(getTestDeviceInterface(), SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getMotorDeviceInterface(), SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getCodersDeviceInterface(), SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getPIDDeviceInterface(), SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getTrajectoryDeviceInterface(), SERIAL_PORT_MOTOR);
    addUartRemoteDevice(getMotionDeviceInterface(), SERIAL_PORT_MOTOR);
    */    

    // Beacon Receiver Board->I2C
    // addI2cRemoteDevice(getBeaconReceiverDeviceInterface(), BEACON_RECEIVER_I2C_ADDRESS);

    // Strategy Board->I2C
    // addI2cRemoteDevice(getStrategyDeviceInterface(), STRATEGY_BOARD_I2C_ADDRESS);

    // Air Conditioning Board
    addI2cRemoteDevice(getAirConditioningDeviceInterface(), AIR_CONDITIONING_BOARD_I2C_ADDRESS);

    // Init the devices
    initDevices();  

    // Manage the callback notification
    // trajectoryDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // testDevice.deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // motionDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
    // infraredDetectorDevice->deviceHandleCallbackRawData = &mainBoardCallbackRawData;
}

void waitForInstruction() {
    // BE CAREFUL : UART 1 / UART 2 are physically connected : https://github.com/svanacker/cen-electronic-schema/issues/11
    // -> DO NOT USE IT AT THE SAME TIME !!

    // Listen instruction from pcStream->Devices
    /*
    handleStreamInstruction(
            &pcInputBuffer,
            &pcOutputBuffer,
            &pcOutputStream,
            &filterRemoveCRLF,
            NULL);
    */

    // Listen instruction from debugStream->Devices
    handleStreamInstruction(
            &debugInputBuffer,
            &debugOutputBuffer,
            &debugOutputStream,
            &filterRemoveCRLF,
            NULL);
}

int main(void) {
    setPicName("MAIN BOARD");
    i2cBus.portIndex = I2C_BUS_PORT_1;

    initRobotConfigPic32(&robotConfig);
    
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
            DEFAULT_SERIAL_SPEED);

    // Open the serial Link for the Motor Board
    openSerialLink(&motorSerialStreamLink,
            &motorInputBuffer,
            &motorInputBufferArray,
            MAIN_BOARD_MOTOR_INPUT_BUFFER_LENGTH,
            &motorOutputBuffer,
            &motorOutputBufferArray,
            MAIN_BOARD_MOTOR_OUTPUT_BUFFER_LENGTH,
            &motorOutputStream,
            SERIAL_PORT_MOTOR,
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

    // Timers
    initTimerList(&timerListArray, MAIN_BOARD_TIMER_LENGTH);

    // Eeproms
    init24C512Eeprom(&eeprom, &i2cBus);

    // Clock
    initClockPCF8563(&clock, &i2cBus);

    // Init the logs
    initLogs(DEBUG, &logHandlerListArray, MAIN_BOARD_LOG_HANDLER_LIST_LENGTH);
    addLogHandler("UART", &debugOutputStream, DEBUG);
    addLogHandler("LCD", &lcdOutputStream, LOG_LEVEL_ERROR);

    appendString(getOutputStreamLogger(ALWAYS), getPicName());
    println(getOutputStreamLogger(ALWAYS));

    initDevicesDescriptor();
    initDriversDescriptor();

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

    // Start interruptions
    // startTimerList();

    // Initializes the DriverDataDispatcherList
    initDriverDataDispatcherList(&driverDataDispatcherListArray, MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH);

    // Configure data dispatcher
    addLocalDriverDataDispatcher();

    // I2C Stream for motorBoard
    addI2CDriverDataDispatcher("MOTOR_BOARD_I2C_DISPATCHER",
        &motorBoardI2cInputBuffer,
        (char(*)[]) &motorBoardI2cInputBufferArray,
        MAIN_BOARD_I2C_INPUT_DRIVER_DATA_DISPATCHER_BUFFER_LENGTH,
        &motorBoardI2cOutputStream,
        &motorBoardI2cInputStream,
        &i2cBus,
        MOTOR_BOARD_I2C_ADDRESS);

    // Uart Stream for motorBoard
    addUartDriverDataDispatcher(
        &motorSerialStreamLink,
        "MOTOR_BOARD_UART_DISPATCHER",
        SERIAL_PORT_MOTOR);

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

    /*
    // Stream for Air Conditioning
    addI2CDriverDataDispatcher(
            "AIR_CONDITIONING_DISPATCHER",
            &airConditioningBoardInputBuffer,
            &airConditioningBoardInputBufferArray,
            MAIN_BOARD_LINK_TO_AIR_CONDITIONING_BOARD_BUFFER_LENGTH,
            &airConditioningBoardOutputStream,
            &airConditioningBoardInputStream,
            &i2cBus,
            AIR_CONDITIONING_BOARD_I2C_ADDRESS);
    */
    // I2C Debug
    initI2CDebugBuffers(&i2cMasterDebugInputBuffer,
                        &i2cMasterDebugInputBufferArray,
                        MAIN_BOARD_I2C_DEBUG_MASTER_IN_BUFFER_LENGTH,
                        &i2cMasterDebugOutputBuffer,
                        &i2cMasterDebugOutputBufferArray,
                        MAIN_BOARD_I2C_DEBUG_MASTER_OUT_BUFFER_LENGTH);

    setDebugI2cEnabled(false);

    while (1) {
        waitForInstruction();
    }

}
