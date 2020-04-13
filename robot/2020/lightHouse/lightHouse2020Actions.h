#ifndef LIGHT_HOUSE_2020_ACTIONS_H
#define LIGHT_HOUSE_2020_ACTIONS_H

#include <stdbool.h>

#include "lightHouse2020.h"

#include "../../../common/pwm/servo/servoList.h"
#include "../../../common/timer/timerList.h"
#include "../../../drivers/tof/tofList.h"

#include "../../../robot/config/robotConfig.h"
#include "../../../robot/match/endMatch.h"

// SERVO INDEX

#define LIGHT_HOUSE_2020_SERVO_INDEX                             0

// SERVO VALUE
#define LIGHT_HOUSE_2020_SERVO_LEFT_VALUE                        500
#define LIGHT_HOUSE_2020_SERVO_RIGHT_VALUE                       2500
#define LIGHT_HOUSE_2020_SERVO_SPEED                             10

// PWM FOR LIGHT
#define LIGHT_HOUSE_2020_LIGHT_ON_VALUE                                   0x60
#define LIGHT_HOUSE_2020_LIGHT_OFF_VALUE                                  0x00

// PWM FOR MOTOR
#define LIGHT_HOUSE_2020_MOTOR_FORWARD_SPEED                               40
#define LIGHT_HOUSE_2020_MOTOR_BACKWARD_SPEED                             -20

// TIMER
void lightHouse2020CallbackFunc(Timer* timer);

// UP / DOWN

void lightHouse2020Up(LightHouse2020* lightHouse);

void lightHouse2020Bottom(LightHouse2020* lightHouse);

// LIGHT ON / OFF

void lightHouse2020On(LightHouse2020* lightHouse);

void lightHouse2020Off(LightHouse2020* lightHouse);

// ROTATION ON / OFF

void lightHouse2020RotationOn(LightHouse2020* lightHouse);

void lightHouse2020RotationOff(LightHouse2020* lightHouse);

#endif
