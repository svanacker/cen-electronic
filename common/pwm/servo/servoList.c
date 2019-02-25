#include "servoList.h"

#include "../../../common/error/error.h"
#include "../../../common/pwm/servo/servoPwm.h"

#include "../../../common/timer/timerConstants.h"
#include "../../../common/timer/timerList.h"

#include <stdlib.h>

/**
 * The interrupt timer.
 */
void interruptServoTimerCallbackFunc(Timer* timer) {
    ServoList* servoList = (ServoList*) timer->object;
    if (!servoList->useTimer) {
        return;
    }
    int i;
    for (i = 0; i < PWM_COUNT; i++) {
        Servo* servo = getServo(servoList, i);
        if (servo->currentPosition == servo->targetPosition) {
            continue;
        }
        if (servo->currentPosition < servo->targetPosition) {
            servo->currentPosition += servo->speed * SERVO_SPEED_TIMER_FACTOR;
            if (servo->currentPosition > servo->targetPosition) {
                servo->currentPosition = servo->targetPosition;
            }
        } else if (servo->currentPosition > servo->targetPosition) {
            servo->currentPosition -= servo->speed * SERVO_SPEED_TIMER_FACTOR;
            // Limit
            if (servo->currentPosition < servo->targetPosition) {
                servo->currentPosition = servo->targetPosition;
            }
        }
        servo->internalPwmFunction(servo, servo->currentPosition);
    }
}

void initServoList(ServoList* servoList, 
                   Servo(*servos)[], 
                   unsigned int servoListSize 
                   ) {
    servoList->servos = servos;
    servoList->maxSize = servoListSize;
    /*
    unsigned int i;
    for (i = 0; i < servoListSize; i++) {
        Servo* servo = getServo(servoList, i);
        servo->servoIndex = i + 1;
        // Enable only if this is define in the mask
        servo->enabled = (1 << i) & servoListInitServoMask;
        servo->speed = PWM_SERVO_SPEED_MAX;
        servo->currentPosition = 1500;
        servo->targetPosition = servo->currentPosition;
        servo->servoInit(servo, servo->currentPosition);
    }
    */
    
    // Init the timer for servo
    // and add the timer to the list, so that the interrupt function will
    // update at a certain frequency the position of the servo
    addTimer(SERVO_TIMER_CODE,
                            TIME_DIVIDER_50_HERTZ,
                            &interruptServoTimerCallbackFunc,
                            "SERVO", 
							(int*) servoList);
    servoList->initialized = true;
    servoList->useTimer = true;
}

/*
void initPwmForServo(unsigned int servoToActivateMask, int posInit) {
    if (servoList.initialized) {
        return;
    }
    __internalPwmForServoHardware(servoToActivateMask, posInit);
    // Init servo structure
    int i;
    for (i = 0; i < PWM_COUNT; i++) {
        Servo* servo = getServo(i);
        servo->enabled = servoToActivateMask & (1 << i);
        servo->speed = PWM_SERVO_SPEED_MAX;
        servo->currentPosition = posInit;
        servo->targetPosition = posInit;
    }
}
*/

Servo* getServo(ServoList* servoList, int servoIndex) {
    if (servoList == NULL || servoList->maxSize == 0) {
        writeError(SERVO_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (servoIndex < 0 || servoIndex >= servoList->maxSize) {
        writeError(SERVO_LIST_OUT_OF_BOUNDS);
        return NULL;
    }
    Servo* result = (Servo*)servoList->servos;
    // we don't need use sizeof because our pointer is a LogHandler* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += servoIndex;

    return result;    
}

// UTILS FUNCTION


void pwmServoAll(ServoList* servoList, unsigned int speed, unsigned int targetPosition) {
    int i;
    for (i = 1; i <= PWM_COUNT; i++) {
        Servo* servo = getServo(servoList, i);
        pwmServo(servo, speed, targetPosition);
    }
}
