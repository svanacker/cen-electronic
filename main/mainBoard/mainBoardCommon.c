#include "mainBoardCommon.h"

#include <stdlib.h>
#include <math.h>

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

// ACCELEROMETER
#include "../../device/accelerometer/accelerometerDevice.h"
#include "../../device/accelerometer/accelerometerDeviceInterface.h"

// CLOCK
#include "../../device/clock/clockDevice.h"
#include "../../device/clock/clockDeviceInterface.h"

// DATA DISPATCHER
#include "../../device/dispatcher/dataDispatcherDevice.h"
#include "../../device/dispatcher/dataDispatcherDeviceInterface.h"

// EEPROM
#include "../../device/eeprom/eepromDevice.h"
#include "../../device/eeprom/eepromDeviceInterface.h"

// LOG
#include "../../device/log/logDevice.h"
#include "../../device/log/logDeviceInterface.h"

// I2C
#include "../../device/i2c/i2cCommonDebugDevice.h"
#include "../../device/i2c/i2cCommonDebugDeviceInterface.h"

// I2C MASTER DEBUG
#include "../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// SERIAL
#include "../../device/serial/serialDebugDevice.h"
#include "../../device/serial/serialDebugDeviceInterface.h"

// SERVO
#include "../../device/servo/servoDevice.h"
#include "../../device/servo/servoDeviceInterface.h"

// SYSTEM
#include "../../device/system/systemDevice.h"
#include "../../device/system/systemDeviceInterface.h"

// TEST 2
#include "../../device/test/test2Device.h"
#include "../../device/test/test2DeviceInterface.h"

// TIMER
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

// TEMPERATURE
#include "../../device/sensor/temperature/temperatureSensorDevice.h"
#include "../../device/sensor/temperature/temperatureSensorDeviceInterface.h"

// TIMER
#include "../../device/timer/timerDevice.h"
#include "../../device/timer/timerDeviceInterface.h"

#include "../../device/adc/adcDevice.h"
#include "../../device/adc/adcDeviceInterface.h"

// Drivers
// -> Accelerometer
#include "../../drivers/accelerometer/adxl345.h"

// -> Clock
#include "../../drivers/clock/PCF8563.h"

// DRIVER TRANSMITTER
#include "../../drivers/driverTransmitter.h"

// -> Eeprom
#include "../../drivers/eeprom/24c512.h"

// -> System
#include "../../drivers/system/systemDriver.h"

// -> Temperature
#include "../../drivers/sensor/temperature/LM75A.h"

// -> Test
#include "../../drivers/test/testDriver.h"

// Robot
#include "../../robot/config/robotConfig.h"
#include "../../robot/config/robotConfigDevice.h"
#include "../../robot/config/robotConfigDeviceInterface.h"
#include "../../robot/config/32/robotConfigPic32.h"
#include "32/servoList32.h"


// COMMON TO ALL MAIN BOARD

// I2C => PORT 1 (for All Peripherical, including Eeprom / Clock / Temperatur)
static I2cBus i2cBusListArray[MAIN_BOARD_I2C_BUS_LIST_LENGTH];
static I2cBusConnection i2cBusConnectionListArray[MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH];
static I2cBus* i2cBus;
static I2cBus* i2cBus4;

// ACCELEROMETER
static Accelerometer accelerometer;
// static AccelerometerData accelerometerData;

// EEPROM
static Eeprom eeprom;
static I2cBusConnection* eepromI2cBusConnection;

// CLOCK
static Clock clock;
static I2cBusConnection* clockI2cBusConnection;


// SPECIFIC

// TEMPERATURE
static Temperature temperature;
static I2cBusConnection* temperatureI2cBusConnection;


// SERIAL
static SerialLink serialLinkListArray[MAIN_BOARD_SERIAL_LINK_LIST_LENGTH];

// serial link DEBUG 
static char debugInputBufferArray[MAIN_BOARD_DEBUG_INPUT_BUFFER_LENGTH];
static Buffer debugInputBuffer;
static char debugOutputBufferArray[MAIN_BOARD_DEBUG_OUTPUT_BUFFER_LENGTH];
static Buffer debugOutputBuffer;
static OutputStream debugOutputStream;
static StreamLink debugSerialStreamLink;



// DRIVERS
static Buffer driverRequestBuffer;
static char driverRequestBufferArray[MAIN_BOARD_REQUEST_DRIVER_BUFFER_LENGTH];
static Buffer driverResponseBuffer;
static char driverResponseBufferArray[MAIN_BOARD_RESPONSE_DRIVER_BUFFER_LENGTH];

// DISPATCHER I2C
static DriverDataDispatcher driverDataDispatcherListArray[MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH];

// Logs
static LogHandler logHandlerListArray[MAIN_BOARD_LOG_HANDLER_LIST_LENGTH];

// Devices
static Device deviceListArray[MAIN_BOARD_DEVICE_LENGTH];

// Relay
// static Relay relay;
// static I2cBusConnection* relayBusConnection;

// Servos
static ServoList servoList;
static Servo servoListArray[MAIN_BOARD_SERVO_LIST_LENGTH];

// Timers
static Timer timerListArray[MAIN_BOARD_TIMER_LIST_LENGTH];

ServoList* mainBoardCommonGetServoList(void) {
    return &servoList;
}

// LOG LIST

void mainBoardCommonInitLogs(void) {
    // LOG Global Configuration
    initLogs(LOG_LEVEL_INFO, &logHandlerListArray, MAIN_BOARD_LOG_HANDLER_LIST_LENGTH, LOG_HANDLER_CATEGORY_ALL_MASK);
}

// SERIAL LIST

void mainBoardCommonInitSerialList(void) {
    initSerialLinkList(&serialLinkListArray, MAIN_BOARD_SERIAL_LINK_LIST_LENGTH);
}

void mainBoardCommonDebugOpenSerialLink(void) {
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
}

// I2C BUS LIST

void mainBoardCommonInitBusList(void) {
        // MAIN I2C
    initI2cBusList((I2cBus(*)[]) &i2cBusListArray, MAIN_BOARD_I2C_BUS_LIST_LENGTH);
	initI2cBusConnectionList((I2cBusConnection(*)[]) &i2cBusConnectionListArray, MAIN_BOARD_I2C_BUS_CONNECTION_LIST_LENGTH);

    // MAIN I2C BUS
    i2cBus = addI2cBus(I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_1);
    i2cMasterInitialize(i2cBus);

    // ALTERNATIVE I2C BUS
    i2cBus4 = addI2cBus(I2C_BUS_TYPE_MASTER, I2C_BUS_PORT_4);
    i2cMasterInitialize(i2cBus4);
}

I2cBus* mainBoardCommonGetMainI2cBus(void) {
    return i2cBus;
}

// SERVO LIST

void mainBoardCommonInitServoList(void) {
    initServoList(&servoList, &servoListArray, MAIN_BOARD_SERVO_LIST_LENGTH);
    addServos_1_2_5(&servoList, "PWM 1", "PWM 2", "PWM 5");
}
// TIMER LIST

void mainBoardCommonInitTimerList(void) {
    initTimerList(&timerListArray, MAIN_BOARD_TIMER_LIST_LENGTH);
}

// DEVICES

void mainBoardCommonInitDeviceListArray(void) {
    initDeviceList(&deviceListArray, MAIN_BOARD_DEVICE_LENGTH);
}

void mainBoardCommonAddDevices(RobotConfig* robotConfig) {
    // SYSTEM & DEBUG
    addLocalDevice(getSystemDeviceInterface(), getSystemDeviceDescriptor());
    addLocalDevice(getLogDeviceInterface(), getLogDeviceDescriptor());
    addLocalDevice(getSerialDebugDeviceInterface(), getSerialDebugDeviceDescriptor());
    addLocalDevice(getTimerDeviceInterface(), getTimerDeviceDescriptor());
    addLocalDevice(getDataDispatcherDeviceInterface(), getDataDispatcherDeviceDescriptor());
    addLocalDevice(getI2cCommonDebugDeviceInterface(), getI2cCommonDebugDeviceDescriptor());
    addLocalDevice(getI2cMasterDebugDeviceInterface(), getI2cMasterDebugDeviceDescriptor());
    
    // COMMON DEVICES
    addLocalDevice(getServoDeviceInterface(), getServoDeviceDescriptor(&servoList));
    addLocalDevice(getEepromDeviceInterface(), getEepromDeviceDescriptor(&eeprom));
    addLocalDevice(getClockDeviceInterface(), getClockDeviceDescriptor(&clock));
    addLocalDevice(getTemperatureSensorDeviceInterface(), getTemperatureSensorDeviceDescriptor(&temperature));
    addLocalDevice(getADCDeviceInterface(), getADCDeviceDescriptor());
    
    // ACCELEROMETER
    // addLocalDevice(getAccelerometerDeviceInterface(), getAccelerometerDeviceDescriptor(&accelerometer));

    // ROBOT CONFIG
    addLocalDevice(getRobotConfigDeviceInterface(), getRobotConfigDeviceDescriptor(robotConfig));
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

void mainBoardCommonInitDriverDataDispatcherList(void) {
    initDriverDataDispatcherList(&driverDataDispatcherListArray, MAIN_BOARD_DRIVER_DATA_DISPATCHER_LIST_LENGTH);
    
    // Configure data dispatcher
    addLocalDriverDataDispatcher();
}

void mainBoardCommonInitCommonDrivers(void) {
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
    
    // -> Servo
    initServoList(&servoList, (Servo(*)[]) &servoListArray, MAIN_BOARD_SERVO_LIST_LENGTH);
    addServos_1_2_5(&servoList, "PWM 1", "PWM 2", "PWM 5");
    
    // -> Accelerometer
    /*
    appendString(getDebugOutputStreamLogger(), "ACCELEROMETER ...");
    I2cBusConnection* adxl345BusConnection = addI2cBusConnection(i2cBus, ADXL345_ALT_ADDRESS, true);
    initADXL345AsAccelerometer(&accelerometer, &accelerometerData, adxl345BusConnection);
    adxl345_setupInterruptOnSingleTapOnInt1(&accelerometer,
                                            8000,
                                            2,
                                            TAP_AXES_ALL_ENABLE,
                                            ADXL345_RATE_400HZ,
                                            ADXL345_RANGE_16G);
    appendStringLN(getDebugOutputStreamLogger(), "OK");
    */
    
    // Start interruptions
    startTimerList(false);
    getTimerByCode(SERVO_TIMER_CODE)->enabled = true;
    // getTimerByCode(END_MATCH_DETECTOR_TIMER_CODE)->enabled = true;
}

void mainBoardCommonHandleStreamInstruction(void) {
    // Listen instruction from debugStream->Devices
    handleStreamInstruction(
            &debugInputBuffer,
            &debugOutputBuffer,
            &debugOutputStream,
            &filterRemoveCRLF_255,
            NULL); 
}

void mainBoardCommonHandleAccelerometer(void) {
    bool intRaised = adxl345_wasIntRaised(&accelerometer);
    if (intRaised) {
        appendStringLN(getDebugOutputStreamLogger(), "SHOCKED !");
    }
}

void mainBoardCommonMainInit(RobotConfig* robotConfig) {
    // LOG the BoardName
    appendStringCRLF(getAlwaysOutputStreamLogger(), getBoardName());
    // Increase the Log Level to DEBUG if the config bit are set
    Logger* logger = getLoggerInstance();
    if (isConfigSet(robotConfig, CONFIG_DEBUG)) {
        logger->globalLogLevel = LOG_LEVEL_DEBUG;
    }
    appendString(getInfoOutputStreamLogger(), "GLOBAL LEVEL : ");
    appendLevelAsString(getInfoOutputStreamLogger(), logger->globalLogLevel);
    println(getInfoOutputStreamLogger());
}