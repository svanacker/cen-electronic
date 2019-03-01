#include <stdbool.h>
#include <stdlib.h>

#include "servoPwm.h"
#include "servoList.h"
#include "../pwmPic.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/error/error.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/timer/cenTimer.h"
#include "../../../common/timer/timerConstants.h"
#include "../../../common/timer/timerList.h"


/**
 * Return a pointer on servoList from the servo.
 * @param servo
 * @return 
 */
ServoList* getServoList(Servo* servo) {
    return (ServoList*) servo->servoList;
}

// INIT FUNCTIONS

void initServo(Servo* servo,
        enum ServoType servoType,
        unsigned int internalServoIndex,
        char* name,
        ServoTypeInitFunction* typeInitFunction,
        ServoInitFunction* initFunction,
        ServoUpdateConfigFunction* updateConfigFunction,
        ServoInternalPwmFunction* internalPwmFunction,
        int* object) {
    servo->servoType = servoType;
    servo->internalServoIndex = internalServoIndex;
    servo->name = name;
    servo->enabled = true;
    servo->targetPosition = PWM_SERVO_MIDDLE_POSITION;
    servo->currentPosition = PWM_SERVO_MIDDLE_POSITION;
    servo->speed = PWM_SERVO_SPEED_MAX;
    servo->typeInitFunction = typeInitFunction;
    servo->initFunction = initFunction;
    servo->updateConfigFunction = updateConfigFunction;
    servo->internalPwmFunction = internalPwmFunction;
    servo->object = object;
    // Launch complete sequence to finish the initialization of the servo
    // value
    servo->initFunction(servo);
    servo->updateConfigFunction(servo);
    servo->internalPwmFunction(servo, servo->currentPosition);
}

// PUBLIC WRITE FUNCTIONS

void pwmServo(Servo* servo, unsigned int speed, int targetPosition) {
    if (servo == NULL) {
        writeError(SERVO_LIST_SERVO_NULL);
        return; 
    }
    if (!servo->enabled) {
        return;
    }
    servo->speed = speed;
    servo->targetPosition = targetPosition;
    // By default, we update the value immediately, if we want some speed, we need a timer !
    ServoList* servoList = getServoList(servo);
    if (servoList == NULL) {
        writeError(SERVO_SERVO_LIST_NULL);
        return;
    }
    if (!servoList->useTimer) {
        servo->internalPwmFunction(servo, targetPosition);
    }
}

void pwmServoSetEnabled(Servo* servo, bool enabled) {
    servo->enabled = enabled;
    if (servo->enabled != enabled) {
        servo->enabled = enabled;
        servo->updateConfigFunction(servo);
    }
}

// READ FUNCTIONS

unsigned int pwmServoReadSpeed(Servo* servo) {
    return servo->speed;
}

unsigned int pwmServoReadCurrentPosition(Servo* servo) {
    return servo->currentPosition;
}

unsigned int pwmServoReadTargetPosition(Servo* servo) {
    return servo->targetPosition;
}
