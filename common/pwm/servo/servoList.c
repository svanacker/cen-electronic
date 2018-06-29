#include "servoList.h"

#include "../../../common/error/error.h"

#include <stdlib.h>

void initServoList(ServoList* servoList, 
                   Servo(*servos)[], 
                   unsigned int servoListSize, 
                   unsigned int servoListInitServoMask) {
    servoList->servos = servos;
    servoList->maxSize = servoListSize;
    unsigned int i;
    for (i = 0; i < servoListSize; i++) {
        Servo* servo = getServo(servoList, i);
        servo->servoIndex = i + 1;
        // Enable only if this is define in the mask
        servo->enabled = (1 << i) & servoListInitServoMask;
        servo->speed = 0;
        servo->currentPosition = 1500;
        servo->targetPosition = servo->currentPosition;
        servo->servoInit(servo, servo->currentPosition);
    }
}

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
