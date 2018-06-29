#ifndef SERVO_LIST_H
#define SERVO_LIST_H

#include <stdbool.h>

#include "servoPwm.h"
#include "servoList.h"

/**
* The structure defining a list of servo.
*/
typedef struct ServoList {
    /** To know if the servo List is already initialized. */
    bool initialized;
    /** The array of servos. */
    Servo(*servos)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list. */
    unsigned char maxSize;
    /** Use Timer, if false, update immediately the value of the servo ! .*/
    bool useTimer;
} ServoList;

/**
 * Initialize a list of Servo with a mask to select each pwm must be activated.
 */
void initServoList(ServoList* servoList, unsigned int servoListInitServoMask);

/**
 * Get a servo object at the specified index.
 * @param servoList the list of servo
 * @param servoIndex the servo Index in the list. Between 0 and n - 1
 * @return 
 */
Servo* getServo(ServoList* servoList, unsigned int servoIndex);

// UTILS FUNCTION

/**
* do a pwm on all pwm of the servoList
* @param servoList the list of servo 
* @param speed the speed to reach the value
* @param targetPosition duration of pwm to 1 typical value between
* PWM_SERVO_LEFT_POSITION and PWM_SERVO_RIGHT_POSITION 
*/
void pwmServoAll(ServoList* servoList, unsigned int speed, unsigned int targetPosition);

#endif
