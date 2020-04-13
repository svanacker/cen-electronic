#include "lightHouse2020Actions.h"
#include "lightHouse2020Debug.h"

#include <stdlib.h>

#include "../../../common/error/error.h"

#include "../../../common/pwm/servo/servoList.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/io/pin.h"

#include "../../../common/log/logger.h"

#include "../../../common/timer/timerConstants.h"
#include "../../../common/timer/delayTimer.h"
#include "../../../common/timer/timerList.h"

#include "../../../client/io/clientIO.h"
#include "../../../client/motor/clientMotor.h"


// TIMER INTERRUPT

/**
 * The interrupt timer.
 */
void lightHouse2020CallbackFunc(Timer* timer) {
    LightHouse2020* lightHouse = (LightHouse2020*) timer->object;
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    lightHouse->timerCount++;
    
    if (!lightHouse->rotateServo) {
        return;
    }

    ServoList* servoList = lightHouse->servoList;
    Servo* servo = getServo(servoList, LIGHT_HOUSE_2020_SERVO_INDEX);

    // To initialize rotation
    unsigned int servoTargetPosition = pwmServoReadTargetPosition(servo);
    if (servoTargetPosition != LIGHT_HOUSE_2020_SERVO_LEFT_VALUE && servoTargetPosition != LIGHT_HOUSE_2020_SERVO_RIGHT_VALUE) {
        pwmServo(servo, LIGHT_HOUSE_2020_SERVO_SPEED, LIGHT_HOUSE_2020_SERVO_LEFT_VALUE, false);
    }

    unsigned int servoCurrentPosition = pwmServoReadCurrentPosition(servo);

    // Change sense when reaching current
    if (servoCurrentPosition >= LIGHT_HOUSE_2020_SERVO_RIGHT_VALUE) {
        pwmServo(servo, LIGHT_HOUSE_2020_SERVO_SPEED, LIGHT_HOUSE_2020_SERVO_LEFT_VALUE, false);
    } else if (servoCurrentPosition <= LIGHT_HOUSE_2020_SERVO_LEFT_VALUE) {
        pwmServo(servo, LIGHT_HOUSE_2020_SERVO_SPEED, LIGHT_HOUSE_2020_SERVO_RIGHT_VALUE, false);
    }
}

// ACTIONS

void lightHouse2020Up(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    // Up And Down are on the "Right" PWM
    clientMotorRight(LIGHT_HOUSE_2020_MOTOR_FORWARD_SPEED);
}

void lightHouse2020Bottom(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    // Up And Down are on the "Right" PWM
    clientMotorRight(LIGHT_HOUSE_2020_MOTOR_BACKWARD_SPEED);
    lightHouse->doNextAction = true;
}

void lightHouse2020On(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    clientMotorLeft(LIGHT_HOUSE_2020_LIGHT_ON_VALUE);
}

void lightHouse2020Off(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    clientMotorLeft(LIGHT_HOUSE_2020_LIGHT_OFF_VALUE);
}

void lightHouse2020RotationOn(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    lightHouse->rotateServo = true;
}

void lightHouse2020RotationOff(LightHouse2020* lightHouse) {
    if (lightHouse == NULL) {
        writeError(LIGHT_HOUSE_2020_NULL);
        return;
    }
    lightHouse->rotateServo = false;
}