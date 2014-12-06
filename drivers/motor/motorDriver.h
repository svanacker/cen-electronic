#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "../driver.h"

/**
* Stops the motors.
*/
void stopMotors(void);

/**
* Write speeds to left and right motors
* @param leftSpeed the left motor speed (value between -255 and 255)
* @param rightSpeed the right motor speed (value between -255 and 255)
*/
void setMotorSpeeds(int leftSpeed, int rightSpeed);

const DriverDescriptor* getMotorDriverDescriptor();

#endif
