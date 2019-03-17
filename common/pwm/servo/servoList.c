#include "servoList.h"

#include "../../../common/error/error.h"
#include "../../../common/pwm/servo/servoPwm.h"

#include "../../../common/timer/timerConstants.h"
#include "../../../common/timer/timerList.h"
#include "../../../common/log/logger.h"

#include <stdlib.h>

/**
 * This means that each time callback, the factor is to increment or decrement.
 * between PWM_SERVO_LEFT_POSITION and PWM_SERVO_RIGHT_POSITION
 */
#define SERVO_SPEED_TIMER_FACTOR               3

/**
 * The interrupt timer.
 */
void interruptServoTimerCallbackFunc(Timer* timer) {
    ServoList* servoList = (ServoList*) timer->object;
    if (!servoList->useTimer) {
        return;
    }
    unsigned int i;
    unsigned size = servoList->size;
    for (i = 0; i < size; i++) {
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
            // Avoid to have negative value
            if (servo->currentPosition > servo->speed * SERVO_SPEED_TIMER_FACTOR) {
                servo->currentPosition -= servo->speed * SERVO_SPEED_TIMER_FACTOR;
            }
            else {
                servo->currentPosition = 0;
            }
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

bool servoListContainsServoType(ServoList* servoList, enum ServoType servoType) {
    unsigned int i;
    for (i = 0; i < servoList->maxSize; i++) {
        Servo* servo = getServo(servoList, i);
        if (servo->servoType == servoType) {
            return true;
        }
    }
    return false;
}

Servo* addServo(ServoList* servoList,
    enum ServoType servoType,
    unsigned int internalServoIndex,
    char* name,
    ServoTypeInitFunction* typeInitFunction,
    ServoInitFunction* initFunction,
    ServoUpdateConfigFunction* updateConfigFunction,
    ServoInternalPwmFunction* internalPwmFunction,
    int* object
    ) {
    if (servoList == NULL) {
        writeError(SERVO_LIST_NULL);
        return NULL;
    }
    if (servoList->maxSize == 0) {
        writeError(SERVO_LIST_NOT_INITIALIZED);
        return NULL;
    }
    unsigned char size = servoList->size;

    if (size < servoList->maxSize) {
        Servo* result = getServo(servoList, size);
        if (result == NULL) {
            writeError(SERVO_LIST_SERVO_NULL);
            return NULL;
        }
        // If we add a new type of servo, we initializes the "class" of servo
        if (!servoListContainsServoType(servoList, servoType)) {
            typeInitFunction(servoType, object);
        }
        initServo(result,
                  servoType,
                  internalServoIndex,
                  name,
                  typeInitFunction,
                  initFunction,
                  updateConfigFunction,
                  internalPwmFunction,
                  object);
        result->servoList = (int*)servoList;
        servoList->size++;
        return result;
    }
    else {
        writeError(SERVO_LIST_TOO_MUCH_SERVOS);
        return NULL;
    }
}

unsigned int getServoCount(ServoList* servoList) {
    return servoList->size;
}

Servo* getServo(ServoList* servoList, unsigned int servoIndex) {
    if (servoList == NULL || servoList->maxSize == 0) {
        writeError(SERVO_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (servoIndex < 0 || servoIndex >= servoList->maxSize) {
        OutputStream* debugOutputStream = getErrorOutputStreamLogger();
        appendStringAndDecLN(debugOutputStream, "maxSize=", servoList->maxSize);
        appendStringAndDecLN(debugOutputStream, "servoIndex=", servoIndex);
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
    unsigned int i;
    for (i = 0; i < servoList->maxSize; i++) {
        Servo* servo = getServo(servoList, i);
        pwmServo(servo, speed, targetPosition);
    }
}

void servoEnableAll(ServoList* servoList, bool enabled) {
    unsigned int i;
    for (i = 0; i < servoList->maxSize; i++) {
        Servo* servo = getServo(servoList, i);
        pwmServoSetEnabled(servo, enabled);
    }
}