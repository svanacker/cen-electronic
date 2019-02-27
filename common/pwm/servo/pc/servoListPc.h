#ifndef SERVO_LIST_PC_H
#define SERVO_LIST_PC_H

#include "../servoList.h"
#include "../servoPwm.h"

/**
 * Initialize a servoList simulation for PC test.
 */
void initServoListPc(ServoList* servoList, Servo(*servoArray)[], unsigned int servoListSize);

#endif