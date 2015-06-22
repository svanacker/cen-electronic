#include "systemDeviceTest.h"


#include "../../../common/error/error.h"
#include "../../../common/io/nullOutputStream.h"

#include "../../../device/deviceUsage.h"
#include "../../../device/deviceList.h"
#include "../../../device/device.h"

// BATTERY
#include "../../../device/battery/batteryDevice.h"
#include "../../../device/battery/batteryDeviceInterface.h"

// CLOCK
#include "../../../device/clock/clockDevice.h"
#include "../../../device/clock/clockDeviceInterface.h"

// DISPATCHER DEVICE
#include "../../../device/dispatcher/dataDispatcherDevice.h"
#include "../../../device/dispatcher/dataDispatcherDeviceInterface.h"

// I2C -> Master
#include "../../../device/i2c/master/i2cMasterDebugDevice.h"
#include "../../../device/i2c/master/i2cMasterDebugDeviceInterface.h"

// CONFIG
#include "../../../robot/config/pc/robotConfigPc.h"
#include "../../../robot/config/robotConfigDevice.h"
#include "../../../robot/config/robotConfigDeviceInterface.h"

// EEPROM
#include "../../../device/eeprom/eepromDevice.h"
#include "../../../device/eeprom/eepromDeviceInterface.h"

// FILE
// #include "../../../device/file/fileDevice.h"
// #include "../../../device/file/fileDeviceInterface.h"

// KINEMATICS
#include "../../../robot/kinematics/robotKinematicsDeviceInterface.h"

// ADC
#include "../../../device/adc/adcDevice.h"
#include "../../../device/adc/adcDeviceInterface.h"

// LCD
#include "../../../device/lcd/lcdDevice.h"
#include "../../../device/lcd/lcdDeviceInterface.h"

// LOGS
#include "../../../device/log/logDevice.h"
#include "../../../device/log/logDeviceInterface.h"

// MOTION
#include "../../../device/motion/pid/pidDeviceInterface.h"
#include "../../../device/motion/position/codersDeviceInterface.h"
#include "../../../device/motion/position/trajectoryDeviceInterface.h"
#include "../../../device/motion/simple/motionDeviceInterface.h"
#include "../../../device/motion/simulation/motionSimulationDeviceInterface.h"

// PWM
#include "../../../device/motor/pwmMotorDevice.h"
#include "../../../device/motor/pwmMotorDeviceInterface.h"

// SENSOR->TEMPERATURE
#include "../../../device/sensor/temperature/temperatureSensor.h"
#include "../../../device/sensor/temperature/temperatureSensorDevice.h"
#include "../../../device/sensor/temperature/temperatureSensorDeviceInterface.h"

// SERVO
#include "../../../device/servo/servoDevice.h"
#include "../../../device/servo/servoDeviceInterface.h"

// STRATEGY
#include "../../../device/strategy/strategyDevice.h"
#include "../../../device/strategy/strategyDeviceInterface.h"

// SYSTEM
#include "../../../device/system/systemDevice.h"
#include "../../../device/system/systemDeviceInterface.h"

// TEST
#include "../../../device/test/testDevice.h"
#include "../../../device/test/testDeviceInterface.h"

// TIMER
#include "../../../device/timer/timerDevice.h"
#include "../../../device/timer/timerDeviceInterface.h"

// I2C -> Slave
#include "../../../device/i2c/slave/i2cSlaveDebugDevice.h"
#include "../../../device/i2c/slave/i2cSlaveDebugDeviceInterface.h"

// BATTERY
#include "../../../device/battery/batteryDevice.h"
#include "../../../device/battery/batteryDeviceInterface.h"

// CLOCK
#include "../../../device/clock/clockDevice.h"
#include "../../../device/clock/clockDeviceInterface.h"

// EEPROM
#include "../../../device/eeprom/eepromDevice.h"
#include "../../../device/eeprom/eepromDeviceInterface.h"

// TIMERS
#include "../../../device/timer/timerDevice.h"
#include "../../../device/timer/timerDeviceInterface.h"

// KINEMATICS
#include "../../../robot/kinematics/robotKinematicsDevice.h"
#include "../../../robot/kinematics/robotKinematicsDeviceInterface.h"

// MOTION
#include "../../../device/motion/pid/pidDevice.h"
#include "../../../device/motion/pid/pidDeviceInterface.h"

#include "../../../device/motion/position/codersDevice.h"
#include "../../../device/motion/position/codersDeviceInterface.h"

#include "../../../device/motion/position/trajectoryDevice.h"
#include "../../../device/motion/position/trajectoryDeviceInterface.h"

#include "../../../device/motion/simple/motionDevice.h"
#include "../../../device/motion/simple/motionDeviceInterface.h"

#include "../../../device/motion/simulation/motionSimulationDevice.h"
#include "../../../device/motion/simulation/motionSimulationDeviceInterface.h"

// NAVIGATION
#include "../../../device/navigation/navigationDevice.h"
#include "../../../device/navigation/navigationDeviceInterface.h"

// SYSTEM
#include "../../../device/system/systemDevice.h"
#include "../../../device/system/systemDeviceInterface.h"

#include "../../../device/test/testDevice.h"
#include "../../../device/test/testDeviceInterface.h"

#include "../../../device/motor/pwmMotorDevice.h"
#include "../../../device/motor/pwmMotorDeviceInterface.h"

#include "../../../test/unity/unity.h"

// Devices
#define SYSTEM_DEVICE_TEST_DEVICE_LIST_LENGTH       30
static Device deviceListArray[SYSTEM_DEVICE_TEST_DEVICE_LIST_LENGTH];

// forward declaration
void testSystemDeviceUsage(void);

void systemDeviceTestSuite(void) {
    RUN_TEST(testSystemDeviceUsage);
}

void testSystemDeviceUsage(void) {
    initDeviceList((Device(*)[]) &deviceListArray, SYSTEM_DEVICE_TEST_DEVICE_LIST_LENGTH);

    addLocalDevice(getADCDeviceInterface(), NULL);
    addLocalDevice(getBatteryDeviceInterface(), NULL);
    addLocalDevice(getClockDeviceInterface(), NULL);
    addLocalDevice(getCodersDeviceInterface(), NULL);
    addLocalDevice(getDataDispatcherDeviceInterface(), NULL);
    addLocalDevice(getEepromDeviceInterface(), NULL);
    addLocalDevice(getI2cMasterDebugDeviceInterface(), NULL);
    addLocalDevice(getI2cSlaveDebugDeviceInterface(), NULL);
    addLocalDevice(getLCDDeviceInterface(), NULL);
    addLocalDevice(getLogDeviceInterface(), NULL);
    addLocalDevice(getMotionDeviceInterface(), NULL);
    addLocalDevice(getMotionSimulationDeviceInterface(), NULL);
    addLocalDevice(getMotorDeviceInterface(), getMotorDeviceDescriptor());
    addLocalDevice(getNavigationDeviceInterface(), NULL);
    addLocalDevice(getPIDDeviceInterface(), NULL);
    addLocalDevice(getRobotConfigDeviceInterface(), NULL);
    addLocalDevice(getRobotKinematicsDeviceInterface(), NULL);
    addLocalDevice(getServoDeviceInterface(), NULL);
    addLocalDevice(getStrategyDeviceInterface(), NULL);
    addLocalDevice(getSystemDeviceInterface(), NULL);
    addLocalDevice(getTemperatureSensorDeviceInterface(), NULL);
    addLocalDevice(getTrajectoryDeviceInterface(), NULL);
    addLocalDevice(getTestDeviceInterface(), getTestDeviceDescriptor());
    addLocalDevice(getTimerDeviceInterface(), NULL);

    OutputStream nullOutputStream;
    initNullOutputStream(&nullOutputStream);

    printDeviceListUsage(&nullOutputStream, true);
    bool anyError = isThereAnyError();

    TEST_ASSERT_FALSE(anyError);
}