#ifndef MD22_H
#define MD22_H

#include "../driver.h"

#include "../../common/i2c/i2cCommon.h"

/**
* Stops the motors
*/
void stopMD22Motors(void);

/**
* Write speeds to left and right motors
* @param leftSpeed the left motor speed (value between -128 and 127)
* @param rightSpeed the right motor speed (value between -128 and 127)
*/
void setMD22MotorSpeeds(I2cBusConnection* i2cBusConnection, signed char leftSpeed, signed char rightSpeed);

DriverDescriptor* getMD22DriverDescriptor(I2cBusConnection* i2cBusConnection);

#endif
