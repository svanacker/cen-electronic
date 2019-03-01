#ifndef SERVO_PWM_PC_H
#define SERVO_PWM_PC_H

#include "../servoPwm.h"

// SERVO CALL BACK IMPLEMENTATION

void servoTypeInitPc(enum ServoType servoType, int* object);

void servoInitPc(Servo* servo);

void servoUpdateConfigPc(Servo* servo);

void servoInternalPwmPc(Servo* servo, unsigned int dutyms);

#endif
