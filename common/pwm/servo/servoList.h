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
    unsigned int size;
    /** the max size of the list. */
    unsigned int maxSize;
    /** Use Timer, if false, update immediately the value of the servo ! .*/
    bool useTimer;
    /**
     * Timer Update Flag. If On, the main loop must call the method to update all values.
     * We must not update it in the callback function, because the function is itself
     * called by a timer with an interruption, and it could cause problem if it takes
     * too much time (like sending instruction through I2C for example)
     */
    bool timerUpdateFlag;
} ServoList;

/**
 * Initialize a list of Servo with a mask to select each pwm must be activated.
 */
void initServoList(ServoList* servoList, Servo(*servoArray)[], unsigned int servoListSize);

/**
 * A function which detect if there is some update to do to any servo.
 * It is useful to implement some method which waits after input
 * @param servoList
 * @return true if there still a servo which must be updated, false else
 */
bool servoListStillWorking(ServoList* servoList);

/**
 * This function ensure that we call the servoListMainUpdateCall until there
 * is something to do
 * @param servoList
 */
void servoListUpdateUntilFinished(ServoList* servoList);

/**
 * The function which must be called by the main loop method to avoid
 * to be called in the interruption.
 * @param servoList
 * @return true if there was an update, false else
 */
bool servoListMainUpdateCall(ServoList* servoList);

/**
 * Returns if the servo List contains already a servo with the same type.
 * @param servoList
 * @param servoType
 * @return 
 */
bool servoListContainsServoType(ServoList* servoList, enum ServoType servoType);

/**
 * Add a servo to the list.
 * @param servoList the list of servo
 * @param servo the servo to add to the list
 */
Servo* addServo(ServoList* servoList,
        enum ServoType servoType,
        unsigned int internalServoIndex,
        char* name,
        ServoTypeInitFunction* typeInitFunction,
        ServoInitFunction* initFunction,
        ServoUpdateConfigFunction* updateConfigFunction,
        ServoInternalPwmFunction* internalPwmFunction,
        int* object
        );

/**
 * Get a servo object at the specified index.
 * @param servoList the list of servo
 * @param servoIndex the servo Index in the list. Between 0 and n - 1
 * @return 
 */
Servo* getServo(ServoList* servoList, unsigned int servoIndex);

/**
 * Returns the amount of servo which is configured.
 * @param servoList the list of servo
 */
unsigned int getServoCount(ServoList* servoList);

// UTILS FUNCTION

/**
 * Do a pwm on all pwm of the servoList
 * @param servoList the list of servo 
 * @param speed the speed to reach the value
 * @param targetPosition duration of pwm to 1 typical value between
 * PWM_SERVO_LEFT_POSITION and PWM_SERVO_RIGHT_POSITION 
 */
void pwmServoAll(ServoList* servoList, unsigned int speed, unsigned int targetPosition);

/**
 * Enable or Disable all servo at the same time.
 */
void servoEnableAll(ServoList* servoList, bool enabled);

#endif
