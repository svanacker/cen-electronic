#ifndef SERVO_PWM_32_H
#define SERVO_PWM_32_H

#include "../../../../common/pwm/servo/servoList.h"

#define PWM_SERVO_ENABLED_MASK_SERVO_1     0b00001
#define PWM_SERVO_ENABLED_MASK_SERVO_2     0b00010
#define PWM_SERVO_ENABLED_MASK_SERVO_3     0b00100
#define PWM_SERVO_ENABLED_MASK_SERVO_4     0b01000
#define PWM_SERVO_ENABLED_MASK_SERVO_5     0b10000

#define PWM_SERVO_ENABLED_MASK_SERVO_ALL   0b11111
#define PWM_SERVO_ENABLED_MASK_SERVO_1_2_5 0b10011
/**
 * Init a list of Servo.
 */
void initServoList32(ServoList* servoList, Servo(*servoArray)[], unsigned int servoListSize);

/**
* initPwm for a 50 Hz operation with a position
* Initialize the cycle of OC1 and OC2 to 20ms
* Use TIMER2
* @param posInt : Duty start cycle from 0 to 20000
*/
void initPwmForServo32 (ServoList* servoList, unsigned int servoToActivateMask, int dutyms);


#endif
