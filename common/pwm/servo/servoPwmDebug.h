#ifndef SERVO_PWM_DEBUG_H
#define SERVO_PWM_DEBUG_H

#include "servoPwm.h"
#include "servoList.h"

#include "../../../common/io/outputStream.h"

/**
 * Print the values of the specified servo.
 * @param outputStream the stream in which we print debug values for the specified servo.
 * @param servo the pointer on the servo
 */
void printServo(OutputStream* outputStream, Servo* servo, unsigned int servoIndex);

/**
* Print the Servo List loaded in the system.
* @param outputStream the stream in which we write information.
* @param servoList the list of servo to write
*/
void printServoList(OutputStream* outputStream, ServoList* servoList);

/**
 * Debug function to be sure that Pwm Servos are ok !
 */
void testAllPwmServos(ServoList* servoList);

// SERVO TYPE

unsigned int appendServoTypeAsString(OutputStream* outputStream, enum ServoType servoType);

unsigned int addServoTypeTableData(OutputStream* outputStream, enum ServoType servoType, int columnSize);

#endif
