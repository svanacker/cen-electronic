#ifndef SERVO_LIST_32_H
#define SERVO_LIST_32_H

#include "../servoList.h"

#define PWM_SERVO_ENABLED_MASK_SERVO_1     0b00001
#define PWM_SERVO_ENABLED_MASK_SERVO_2     0b00010
#define PWM_SERVO_ENABLED_MASK_SERVO_3     0b00100
#define PWM_SERVO_ENABLED_MASK_SERVO_4     0b01000
#define PWM_SERVO_ENABLED_MASK_SERVO_5     0b10000

#define PWM_SERVO_ENABLED_MASK_SERVO_ALL   0b11111
#define PWM_SERVO_ENABLED_MASK_SERVO_1_2_5 0b10011

/**
 * Add a servo with internal pwm implementation by the microcontroller.
 * @param servoList
 * @param internalServoIndex
 * @param servoName
 */
Servo* addServo32(ServoList* servoList, unsigned int internalServoIndex, char* servoName);

/**
 * Add the Hardwared Servo from the microcontroller 1, 2 and 5 to the servo List.
 */
void addServos_1_2_5(ServoList* servoList, 
                         char* nameServo1,
                         char* nameServo2,
                         char* nameServo5);

/**
 * Add the Hardware Servo from the microcontroller 1, 2, 3, 4 and 5
 * to the servo List.
 */
void addServos_1_2_3_4_5(ServoList* servoList,
                         char* nameServo1,
                         char* nameServo2,
                         char* nameServo3,
                         char* nameServo4,
                         char* nameServo5);

#endif
