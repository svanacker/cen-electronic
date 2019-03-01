#ifndef SERVO_PWM_H
#define SERVO_PWM_H

#include <stdbool.h>

#include "../pwmPic.h"

struct Servo;
typedef struct Servo Servo;

/**
 * Determine the type of servo.
 */
enum ServoType {
    /** Undefined (often because not initialized properly !) */
    SERVO_TYPE_UNKNOWN,
    /** The pwm is managed internally by the microcontroller */
    SERVO_TYPE_INTERNAL_PWM,
    /** The PCA_8695. */
    SERVO_TYPE_PCA_8695,
    /** Devantech SD21. */
    SERVO_TYPE_SD_21,
    /** PC (simulation). */
    SERVO_TYPE_PC
};

// SERVO CALL BACK FUNCTION

/**
 * Function raised when we initialize the first type of servo.
 * A list of servo could be composed by several types of servo, and for specific
 * Servo Type, we must initialize something at the beginning.
 * The servo List and the kind of servoType
 */
typedef void ServoTypeInitFunction(enum ServoType servoType, int* object);

/**
 * Function raised when we initialize a servo.
 */
typedef void ServoInitFunction(Servo* servo);

/**
 * Function raised when we change the change a parameter of config (like enabled)
 */
typedef void ServoUpdateConfigFunction(Servo* servo);

/**
 * Set pwm to the Servo.
 * @param dutyms : typical value is 1500, and 90° amplitude is done between
 * 1000 & 2000
 */
typedef void ServoInternalPwmFunction(Servo* servo, unsigned int dutyms);

/**
* Defines the structure to manages Servos.
 * Be careful to NOT change any record of this struct after Initialization 
 * to avoid some hazardous problem !!
*/
struct Servo {
    /** The type of servo. */
    enum ServoType servoType;
    /**
     * The internal index of the servo linked to the hardware. As several
     * servo could use different type of servo (PCA8695, internal PWM).
     * Ex : 3 for the pin 3 of the PCA8695 or the pin 3
     */
    unsigned int internalServoIndex;
    /**
    * Name of the servo so that we can easily understand the target of the servo.
    */
    char* name;
    /** If we use it, in PIC, some PWM use UART, so we don't activate them always
     * This property must NOT be used  */
    bool enabled;
    /** The speed to reach the final position. */
    unsigned int speed;
    /** The current position. */
    unsigned int currentPosition;
    /** The target position. */
    unsigned int targetPosition;
    /** The function which must be used when a new type is added. */
    ServoTypeInitFunction* typeInitFunction;
    /** The function which must be called at first init. */
    ServoInitFunction* initFunction;
    /** 
     * The function which must be called back when we change the configuration
     * of the servo (like by enabled).
     */
    ServoUpdateConfigFunction* updateConfigFunction;
    /** The function to apply the pwm : must NOT be called outside the framework. */
    ServoInternalPwmFunction* internalPwmFunction;
    /** Back pointer to the servoList (untyped to avoid circular reference) */
    int* servoList;
    /** Pointer to a specific object (for example I2cBusConnection */
    int* object;
};



// POSITION

/**
* Middle position for a servo
*/
#define PWM_SERVO_MIDDLE_POSITION        1500

/**
* Left position (around 45° / middle position).
*/
#define PWM_SERVO_LEFT_POSITION          1000

/**
* Right position (around 45° / middle position).
*/
#define PWM_SERVO_RIGHT_POSITION         2000

// SPEED

#define PWM_SERVO_SPEED_MIN                 1

#define PWM_SERVO_SPEED_MAX               255

// INIT

void initServo(Servo* servo, 
                enum ServoType servoType,
                unsigned int internalServoIndex,
                char* name,
                ServoTypeInitFunction* typeInitFunction,
                ServoInitFunction* initFunction,
                ServoUpdateConfigFunction* updateConfigFunction,
                ServoInternalPwmFunction* internalPwmFunction,
                int* object);

// INTERFACE

/**
* Do a pwm servo on a specified servo
* @param speed the speed to reach the targetPosition
* @param targetPosition duration of pwm to 1 typical value between
* PWM_SERVO_LEFT_POSITION and PWM_SERVO_RIGHT_POSITION 
*/
void pwmServo(Servo* servo, unsigned int newSpeed, int newTargetPosition);

/**
 * Change the enabled property by a new value.
 * @param servo
 * @param enabled
 */
void pwmServoSetEnabled(Servo* servo, bool enabled);

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
