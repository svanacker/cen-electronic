#ifndef SERVO_PWM_DEBUG_H
#define SERVO_PWM_DEBUG_H

#include "servoPwm.h"

#include "../../../common/io/outputStream.h"

/**
 * Print the values of the specified servo.
 * @param outputStream the stream in which we print debug values for the specified servo.
 * @param servo the pointer on the servo
 * @param index the index of the servo
 */
void printServo(OutputStream* outputStream, Servo* servo, int index);

/**
* Print the Servo List loaded in the system.
* @param outputStream the stream in which we write information.
*/
void printServoList(OutputStream* outputStream);

/**
 * Debug function to be sure that Pwm Servos are ok !
 */
void testAllPwmServos();

#endif
