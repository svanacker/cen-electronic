#ifndef SERVO_LIST_PC_H
#define SERVO_LIST_PC_H

#include "../servoList.h"
#include "../servoPwm.h"

/**
 * Initialize a servoList simulation for PC test and a list of "fake" servo.
 */
void initServoListPc(ServoList* servoList, Servo(*servoArray)[], unsigned int servoListSize);

/**
* Add a new "fake" servo to the Pc.
*/
Servo* addServoPc(ServoList* servoList, unsigned internalIndex, char* servoName);

#endif