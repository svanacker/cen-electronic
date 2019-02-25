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

#define SERVO_SPEED_TIMER_FACTOR 3

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
        servo->setFunction(servo, targetPosition);
    }
}

void pwmServoAll(unsigned int speed, int dutyms) {
    int i;
    for (i = 1; i <= PWM_COUNT; i++) {
        pwmServo(i, speed, dutyms);
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
