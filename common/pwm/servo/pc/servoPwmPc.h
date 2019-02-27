#ifndef SERVO_PWM_PC_H
#define SERVO_PWM_PC_H

#include "../servoPwm.h"

// SERVO CALL BACK IMPLEMENTATION

void servoInitPc(Servo* servo);

void servoInternalPwmPc(Servo* servo, unsigned int dutyms);

#endif
