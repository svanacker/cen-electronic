#ifndef SERVO_PWM_H
#define SERVO_PWM_H

#include <stdbool.h>

#include "../pwmPic.h"

/**
* Defines the structure to manages Servos.
*/
typedef struct Servo {
    /** The index of the servo (between 1 and n, not between 0 and n - 1 !). */
    unsigned int servoIndex;
    /** If we use it, in PIC, some PWM use UART, so we don't activate them always. */
    bool enabled;
    /** The speed to reach the final position. */
    unsigned int speed;
    /** The current position. */
    unsigned int currentPosition;
    /** The target position. */
    unsigned int targetPosition;
    /** The function to call when initializing the servo */
    ServoInitFunction* servoInit;
    /** The function to call when we want to write the servo */
    ServoPwmFunction* servoPwm;
} Servo;

/**
 * Initialize a servo to an initial Position.
 * @param servo the wrapper arround the servo
 * @param initialPosition the initial position
 */
typedef void ServoInitFunction(Servo* servo, unsigned int initialPosition);

/**
 * "Protected" method which must not be used directly by users.
 */
typedef void ServoPwmFunction(Servo* servo, unsigned int targetPosition);

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

// INIT

/**
 * Initialize the servo with the function
 * @param servoInitFunction The function to call when initializing the servo
 * @param The function to call when we want to write the servo
 */
void initServo(Servo* servo, 
               ServoInitFunction* servoInitFunction,
               ServoPwmFunction* servoPwmFunction);

// INTERFACE


// UTILS FUNCTION

/**
 * Returns the speed used to reach the position.
 * @param servoIndex the servo index that we want to get
 * @param -1 if servoIndex is not correct, speed value if ok
 */
unsigned int pwmServoReadSpeed(Servo* servo);

/**
 * Returns the current position used to reach the current position.
 * @param servoIndex the servo index that we want to get the current position
 * @param -1 if servoIndex is not correct, current position if ok
 */
unsigned int pwmServoReadCurrentPosition(Servo* servo);

/**
 * Returns the current position used to reach the target position.
 * @param servoIndex the servo index that we want to get the target position
 * @param -1 if servoIndex is not correct, current position if ok
 */
unsigned int pwmServoReadTargetPosition(Servo* servo);

#endif
