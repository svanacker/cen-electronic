#include "servoPwmPca9685.h"
#include "pca9685.h"

#include "../../../common/i2c/i2cBusConnectionList.h"

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/pwm/servo/servoList.h"
#include "i2cCommon.h"
#include "32/servoPwm32.h"

I2cBusConnection* getServoI2CBusConnection(Servo* servo) {
    int* object = servo->object;
    return (I2cBusConnection*) object;
}

void _internalTypeInitPwmServo9685(enum ServoType servoType, int* object) {
    I2cBusConnection* i2cBusConnection = (I2cBusConnection*) object;
    pca9685_init(i2cBusConnection);
}

void _internalInitPwmServo9685(Servo* servo) {
    // TODO
}

void _internalUpdateConfigServo9685(Servo* servo) {
    // TODO
}

unsigned int servoPwmPca9685DutyMsToValue(unsigned int dutyms) {
    // Frequency is 50 Hz for Servo => 20 ms
    // dutyms is between 1000 and 2000 µs (or between 1ms and 2ms)
    // 1ms in dutyms is 4096 / 20, 2ms in dutyms is 4096 / 10
    // So for a resolution of 4096 bits
    return (4096 * dutyms / (20 * 1000));
}

void _InternalPwm9685 (Servo* servo, unsigned int dutyms) {
    I2cBusConnection* i2cBusConnection = getServoI2CBusConnection(servo);
    unsigned int value = servoPwmPca9685DutyMsToValue(servo->currentPosition);
    pca9685_setPin(i2cBusConnection, servo->internalServoIndex, value, false);
}

Servo* addServoPca9685(ServoList* servoList,
                       I2cBusConnection* i2cBusConnection,
                       unsigned int internalServoIndex,
                       char* servoName) {
        return addServo(servoList,
              SERVO_TYPE_PCA_8695,
              internalServoIndex,
              servoName,
              _internalTypeInitPwmServo9685,
              _internalInitPwmServo9685,
              _internalUpdateConfigServo9685,
              _InternalPwm9685,
              (int*) i2cBusConnection);
}

void addServoAllPca9685(ServoList* servoList,
                       I2cBusConnection* i2cBusConnection) {
    // TODO : Implementation
    addServoPca9685(servoList, i2cBusConnection, 0, "PCA 0");
    addServoPca9685(servoList, i2cBusConnection, 1, "PCA 1");
    addServoPca9685(servoList, i2cBusConnection, 2, "PCA 2");
    addServoPca9685(servoList, i2cBusConnection, 3, "PCA 3");
    
    addServoPca9685(servoList, i2cBusConnection, 4, "PCA 4");
    addServoPca9685(servoList, i2cBusConnection, 5, "PCA 5");
    addServoPca9685(servoList, i2cBusConnection, 6, "PCA 6");
    addServoPca9685(servoList, i2cBusConnection, 7, "PCA 7");
    
    addServoPca9685(servoList, i2cBusConnection, 8, "PCA 8");
    addServoPca9685(servoList, i2cBusConnection, 9, "PCA 9");
    addServoPca9685(servoList, i2cBusConnection, 10, "PCA 10");
    addServoPca9685(servoList, i2cBusConnection, 11, "PCA 11");
    
    addServoPca9685(servoList, i2cBusConnection, 12, "PCA 12");
    addServoPca9685(servoList, i2cBusConnection, 13, "PCA 13");
    addServoPca9685(servoList, i2cBusConnection, 14, "PCA 14");
    addServoPca9685(servoList, i2cBusConnection, 15, "PCA 15");
    
    
    
}
