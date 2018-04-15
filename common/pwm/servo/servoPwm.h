#ifndef SERVO_PWM_H
#define SERVO_PWM_H

#include <stdbool.h>

#include "../pwmPic.h"

/**
* Defines the structure to manages Servos.
*/
typedef struct Servo {
    /** If we use it, in PIC, some PWM use UART, so we don't activate them always */
    bool enabled;
    /** The speed to reach the final position. */
    unsigned int speed;
    /** The current position. */
    unsigned int currentPosition;
    /** The target position. */
    unsigned int targetPosition;
} Servo;

/**
* Tre struct defining a list of servo.
*/
typedef struct ServoList {
    /** To know if the servo List is already initialized. */
    bool initialized;
    /** The array of servos. */
    Servo servos[PWM_COUNT];
    /** Use Timer, if false, update immediately the value of the servo ! .*/
    bool useTimer;
} ServoList;

#define PWM_SERVO_ENABLED_MASK_SERVO_1     0b00001
#define PWM_SERVO_ENABLED_MASK_SERVO_2     0b00010
#define PWM_SERVO_ENABLED_MASK_SERVO_3     0b00100
#define PWM_SERVO_ENABLED_MASK_SERVO_4     0b01000
#define PWM_SERVO_ENABLED_MASK_SERVO_5     0b10000

#define PWM_SERVO_ENABLED_MASK_SERVO_ALL   0b11111
#define PWM_SERVO_ENABLED_MASK_SERVO_1_2_5 0b10011

/**
* Middle position for a servo
*/
// FOR MD22 RC MODE
#define PWM_SERVO_MIDDLE_POSITION 1480

/**
* Left position (around 45° / middle position).
*/
#define PWM_SERVO_LEFT_POSITION 1000

/**
* Right position (around 45° / middle position).
*/
#define PWM_SERVO_RIGHT_POSITION 2000

#define PWM_SERVO_SPEED_MIN 1

#define PWM_SERVO_SPEED_MAX 255

// --- SERVO MODE ---

/**
 * @private.
 */
ServoList* _getServoList();

// ABSTRACT METHOD

/**
 * Abstract method which must be defined by a hardware implementation
 * (Ex : 30F / 32)
 * @param posInit the initial position of all servos.
 */
void __internalPwmForServoHardware(unsigned int servoEnabledMask, 
                                   int posInit);

/**
 * "Protected" method which must not be used directly by users.
 */
void __internalPwmServo(int pwmIndex, int dutyms);

// INIT

/**
* initPwm for a 50 Hz operation with a position
* Initialize the cycle of OC1 and OC2 to 20ms
* Use TIMER2
* @param posInt : Duty start cycle from 0 to 20000
*/
void initPwmForServo (unsigned int servoToActivateMask, int dutyms);

// INTERFACE

/**
* do a pwm on a pwmIndex between 1 and 4
* @param targetPosition duration of pwm to 1 typical value between
* PWM_SERVO_LEFT_POSITION and PWM_SERVO_RIGHT_POSITION 
*/
void pwmServo(int pwmIndex, unsigned int speed, int targetPosition);

/**
* do a pwm on all pwm
* @param dutyms duration of pwm to 1 typical value between
* PWM_SERVO_LEFT_POSITION and PWM_SERVO_RIGHT_POSITION 
*/
void pwmServoAll(unsigned int speed, int dutyms);

/**
 * Returns the speed used to reach the position.
 * @param servoIndex the servo index that we want to get
 * @param -1 if servoIndex is not correct, speed value if ok
 */
unsigned int pwmServoReadSpeed(int servoIndex);

/**
 * Returns the current position used to reach the current position.
 * @param servoIndex the servo index that we want to get the current position
 * @param -1 if servoIndex is not correct, current position if ok
 */
unsigned int pwmServoReadCurrentPosition(int servoIndex);

/**
 * Returns the current position used to reach the target position.
 * @param servoIndex the servo index that we want to get the target position
 * @param -1 if servoIndex is not correct, current position if ok
 */
unsigned int pwmServoReadTargetPosition(int servoIndex);

#endif
