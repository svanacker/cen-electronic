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

// PUBLIC WRITE FUNCTIONS

void pwmServo(Servo* servo, unsigned int speed, int targetPosition) {
    if (!servo->enabled) {
        return;
    }
    servo->speed = speed;
    servo->targetPosition = targetPosition;
    // By default, we update the value immediately, if we want some speed, we need a timer !
    ServoList* servoList = getServoList(servo);
    if (!servoList->useTimer) {
        servo->internalPwmFunction(servo, targetPosition);
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
