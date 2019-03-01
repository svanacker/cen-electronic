#ifndef SERVO_PWM_PCA9685_H
#define SERVO_PWM_PCA9685_H

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/pwm/servo/servoList.h"
#include "i2cCommon.h"

/**
 * Add a servo of the type PCA9685
 * @param servoList the servo list in which we add the servo
 * @param i2cBusConnection the bus + address of the PCA9685
 * @param internalServoIndex the internal servo index of the pca
 * @param servoName
 * @return 
 */
Servo* addServoPca9685(ServoList* servoList, I2cBusConnection* i2cBusConnection, unsigned int internalServoIndex, char* servoName);

/**
 * Add all servo of a specific PCA9685
 * @param servoList the servo list in which we add the servo
 * @param i2cBusConnection the bus + address of the PCA9685
 */
void addServoAllPca9685(ServoList* servoList, I2cBusConnection* i2cBusConnection);

#endif
