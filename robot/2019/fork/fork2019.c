#include "fork2019.h"

#include <stdbool.h>

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/error/error.h"

#include "../../../common/delay/cenDelay.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/pwm/servo/servoPwm.h"
#include "../../../common/pwm/servo/servoList.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/tof/tofList.h"

#include "forkScan2019.h"
#include "../elevator/elevator2019.h"
#include "../arm/arm2019.h"

/**
 * @param servoList the list of servo
 * @param leftRight
 * @param leftServoIndex
 * @param rightServoIndex
 * @param leftSpeed
 * @param rightSpeed
 * @param leftPosition
 * @param rightPosition
 */
void fork2019MoveServo(ServoList* servoList,
        unsigned int leftRight,
        unsigned int leftServoIndex,
        unsigned int rightServoIndex,
        unsigned int leftSpeed,
        unsigned int rightSpeed,
        unsigned int leftPosition,
        unsigned rightPosition,
        bool wait) {
    if (leftRight == FORK_2019_LEFT_INDEX) {
        Servo* servo = getServo(servoList, leftServoIndex);
        pwmServo(servo, leftSpeed, leftPosition, wait);
    }
    else if (leftRight == FORK_2019_RIGHT_INDEX) {
        Servo* servo = getServo(servoList, rightServoIndex);
        pwmServo(servo, rightSpeed, rightPosition, wait);
    }
    else if (leftRight == FORK_2019_LEFT_AND_RIGHT_INDEX) {
        Servo* leftServo = getServo(servoList, leftServoIndex);
        // We don't wait both time for left & right (the delay is blocking), so we don't put "wait", but false on delay parameter
        pwmServo(leftServo, leftSpeed, leftPosition, false);
        Servo* rightServo = getServo(servoList, rightServoIndex);
        pwmServo(rightServo, rightSpeed, rightPosition, wait);
    }
}

void moveForkBack(ServoList* servoList, unsigned int leftRight, bool wait) {
    fork2019MoveServo(servoList, leftRight,
            FORK_2019_LEFT_SERVO_FORK_INDEX, FORK_2019_RIGHT_SERVO_FORK_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_RETRACTED_SERVO_VALUE, FORK_2019_SERVO_RIGHT_RETRACTED_SERVO_VALUE,
            wait);
}

void moveForkBackAllWithoutWait(ServoList* servoList) {
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, false);
}

void moveForkSimplePuck(ServoList* servoList, unsigned int leftRight, bool wait) {
    fork2019MoveServo(servoList, leftRight,
            FORK_2019_LEFT_SERVO_FORK_INDEX, FORK_2019_RIGHT_SERVO_FORK_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_SIMPLE_PUCK_SERVO_VALUE, FORK_2019_SERVO_RIGHT_SIMPLE_PUCK_SERVO_VALUE,
            wait);
}

void moveForkDoublePuck(ServoList* servoList, unsigned int leftRight, bool wait) {
    fork2019MoveServo(servoList, leftRight,
            FORK_2019_LEFT_SERVO_FORK_INDEX, FORK_2019_RIGHT_SERVO_FORK_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_DOUBLE_PUCK_SERVO_VALUE, FORK_2019_SERVO_RIGHT_DOUBLE_PUCK_SERVO_VALUE,
            wait);
}

void moveForkPushOff(ServoList* servoList, unsigned int leftRight, bool wait) {
    fork2019MoveServo(servoList, leftRight,
            FORK_2019_LEFT_SERVO_PUSH_INDEX, FORK_2019_RIGHT_SERVO_PUSH_INDEX,
            FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR, FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR,
            FORK_2019_SERVO_PUSH_LEFT_OFF_SERVO_VALUE, FORK_2019_SERVO_PUSH_RIGHT_OFF_SERVO_VALUE, 
            wait);
}

void moveForkPushOn(ServoList* servoList, unsigned int leftRight, bool wait) {
    fork2019MoveServo(servoList, leftRight,
            FORK_2019_LEFT_SERVO_PUSH_INDEX, FORK_2019_RIGHT_SERVO_PUSH_INDEX,
            FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR, FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR,
            FORK_2019_SERVO_PUSH_LEFT_ON_SERVO_VALUE, FORK_2019_SERVO_PUSH_RIGHT_ON_SERVO_VALUE,
            wait);
}

void moveForkPushOffAllWithoutWait(ServoList* servoList) {
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, false);
}


// COMPLEXE OPERATIONS

void fork2019Init(ServoList* servoList) {
    // We do not wait because the robot is initializing
    bool wait = false;

    // Go to the bottom 
    moveElevatorBottom(servoList, wait);
    
    // Center the Elevator
    moveElevatorMiddle(servoList, wait);

    // Fork Push Off
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, wait);

    // Fork Retracted
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX, wait);
}


void updateServoProperties2019(ServoList* servoList) {
    if (servoList == NULL) {
        writeError(SERVO_LIST_NULL);
    }

    // Arm (For small Robot only))
    getServo(servoList, FORK_2019_LEFT_ARM_SERVO_INDEX)->name = "ARM LEFT";
    getServo(servoList, FORK_2019_RIGHT_ARM_SERVO_INDEX)->name = "ARM RIGHT";

    // Elevator
    // -> Up/Down
    getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX)->name = "ELEV. UP/DOWN";
    getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX)->maxSpeedUnderLoad = FORK_2019_ELEVATOR_MAX_SPEED_UNDER_LOAD;

    // Left / Right (Scan)
    getServo(servoList, FORK_2019_SCAN_SERVO_INDEX)->name = "ELEV SCAN";
    getServo(servoList, FORK_2019_SCAN_SERVO_INDEX)->maxSpeedUnderLoad = FORK_2019_ELEVATOR_SCAN_MAX_SPEED_UNDER_LOAD;

    // Fork
    getServo(servoList, FORK_2019_LEFT_SERVO_FORK_INDEX)->name = "FORK LEFT";
    getServo(servoList, FORK_2019_LEFT_SERVO_FORK_INDEX)->maxSpeedUnderLoad = FORK_2019_ELEVATOR_FORK_MAX_SPEED_UNDER_LOAD;
    getServo(servoList, FORK_2019_RIGHT_SERVO_FORK_INDEX)->name = "FORK RIGHT";
    getServo(servoList, FORK_2019_RIGHT_SERVO_FORK_INDEX)->maxSpeedUnderLoad = FORK_2019_ELEVATOR_FORK_MAX_SPEED_UNDER_LOAD;

    // Fork Push
    getServo(servoList, FORK_2019_LEFT_SERVO_PUSH_INDEX)->name = "PUSH LEFT";
    getServo(servoList, FORK_2019_LEFT_SERVO_PUSH_INDEX)->maxSpeedUnderLoad = FORK_2019_ELEVATOR_FORK_PUSH_MAX_SPEED_UNDER_LOAD;
    getServo(servoList, FORK_2019_RIGHT_SERVO_PUSH_INDEX)->name = "PUSH RIGHT";
    getServo(servoList, FORK_2019_RIGHT_SERVO_PUSH_INDEX)->maxSpeedUnderLoad = FORK_2019_ELEVATOR_FORK_PUSH_MAX_SPEED_UNDER_LOAD;
}