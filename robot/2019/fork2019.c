#include "fork2019.h"

#include <stdbool.h>

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/pwm/servo/servoPwm.h"
#include "../../common/pwm/servo/servoList.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../drivers/tof/tofList.h"

/**
 * @private
 * @param servoList the list of servo
 * @param leftRight
 * @param leftServoIndex
 * @param rightServoIndex
 * @param leftSpeed
 * @param rightSpeed
 * @param leftPosition
 * @param rightPosition
 */
void moveServo(ServoList* servoList,
               unsigned int leftRight,
               unsigned int leftServoIndex,
               unsigned int rightServoIndex,
               unsigned int leftSpeed,
               unsigned int rightSpeed,
               unsigned int leftPosition,
               unsigned rightPosition) {
    if (leftRight == FORK_2019_LEFT_AND_RIGHT_INDEX || leftRight == FORK_2019_LEFT_INDEX) {
        Servo* servo = getServo(servoList, leftServoIndex);
        pwmServo(servo, leftSpeed, leftPosition);
    }
    if (leftRight == FORK_2019_LEFT_AND_RIGHT_INDEX || leftRight == FORK_2019_RIGHT_INDEX) {
        Servo* servo = getServo(servoList, rightServoIndex);
        pwmServo(servo, rightSpeed, rightPosition);
    }    
}

void moveElevatorAtValue(ServoList* servoList, unsigned int value) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, value);
}

void moveElevatorBottom(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_BOTTOM_SERVO_VALUE);
}

void moveElevatorInitPosition(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_INIT_POSITION_SERVO_VALUE);
}

void moveElevatorUp(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_UP_SERVO_VALUE);
}

void moveElevatorDoublePuck(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_DOUBLE_PUCK_SERVO_VALUE);
}

void moveElevatorLeft(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_LEFT_SERVO_VALUE);
    delaymSec(500);
}

void moveElevatorRight(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_RIGHT_SERVO_VALUE);
    delaymSec(500);
}


void moveForkBack(ServoList* servoList, unsigned int leftRight) {
    moveServo(servoList, leftRight, 
            FORK_2019_LEFT_SERVO_FORK_INDEX, FORK_2019_RIGHT_SERVO_FORK_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_RETRACTED_SERVO_VALUE, FORK_2019_SERVO_RIGHT_RETRACTED_SERVO_VALUE);
}

void moveForkSimplePuck(ServoList* servoList, unsigned int leftRight) {
    moveServo(servoList, leftRight, 
            FORK_2019_LEFT_SERVO_FORK_INDEX, FORK_2019_RIGHT_SERVO_FORK_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_SIMPLE_PUCK_SERVO_VALUE, FORK_2019_SERVO_RIGHT_SIMPLE_PUCK_SERVO_VALUE);
}

void moveForkDoublePuck(ServoList* servoList, unsigned int leftRight) {
    moveServo(servoList, leftRight, 
            FORK_2019_LEFT_SERVO_FORK_INDEX, FORK_2019_RIGHT_SERVO_FORK_INDEX,
            FORK_2019_SERVO_LEFT_SPEED_FACTOR, FORK_2019_SERVO_RIGHT_SPEED_FACTOR,
            FORK_2019_SERVO_LEFT_DOUBLE_PUCK_SERVO_VALUE, FORK_2019_SERVO_RIGHT_DOUBLE_PUCK_SERVO_VALUE);
}

void moveForkPushOff(ServoList* servoList, unsigned int leftRight) {
    moveServo(servoList, leftRight, 
            FORK_2019_LEFT_SERVO_PUSH_INDEX, FORK_2019_RIGHT_SERVO_PUSH_INDEX,
            FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR, FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR,
            FORK_2019_SERVO_PUSH_LEFT_OFF_SERVO_VALUE, FORK_2019_SERVO_PUSH_RIGHT_OFF_SERVO_VALUE);
}

void moveForkPushOn(ServoList* servoList, unsigned int leftRight) {
    moveServo(servoList, leftRight, 
            FORK_2019_LEFT_SERVO_PUSH_INDEX, FORK_2019_RIGHT_SERVO_PUSH_INDEX,
            FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR, FORK_2019_SERVO_PUSH_LEFT_SPEED_FACTOR,
            FORK_2019_SERVO_PUSH_LEFT_ON_SERVO_VALUE, FORK_2019_SERVO_PUSH_RIGHT_ON_SERVO_VALUE);
}

void forkScanFromRightToLeft(ServoList* servoList, TofSensorList* tofSensorList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    moveElevatorRight(servoList);

    unsigned int i;
    for (i = FORK_2019_SCAN_RIGHT_SERVO_VALUE; i < FORK_2019_SCAN_LEFT_SERVO_VALUE; i+= 10) {
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i);
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, 0);
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        if (distance > 0 && distance < 16) {
            appendStringAndDecLN(getDebugOutputStreamLogger(), "distance=", distance);
            break;
        }
        delaymSec(10);
    }
}

void forkScanFromLeftToRight(ServoList* servoList, TofSensorList* tofSensorList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_LEFT_SERVO_VALUE);
    delaymSec(500);
    unsigned int i;
    for (i = FORK_2019_SCAN_LEFT_SERVO_VALUE; i < FORK_2019_SCAN_LEFT_SERVO_VALUE; i-= 10) {
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i);
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, 0);
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        if (distance > 0 && distance < 16) {
            appendStringAndDecLN(getDebugOutputStreamLogger(), "distance=", distance);
            break;
        }
        delaymSec(10);
    }
}

// COMPLEXE OPERATIONS

void fork2019Init(ServoList* servoList) {
    // TODO : To Check Elevator 
    moveElevatorBottom(servoList);

    // Fork Push Off)
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);

    // Fork Retracted
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
}

bool fork2019TakeSimplePuck(ServoList* servoList) {
    // Fork Push Off
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);

    // Elevator
    // TODO : Which Height
    moveElevatorBottom(servoList);
    delaymSec(1000);
    
    // TODO : Scan to do => Return false if the scan is KO

    // Fork Single Puck
    moveForkSimplePuck(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    delaymSec(1000);

    // Elevator Up to free the Puck
    moveElevatorUp(servoList);
    delaymSec(1000);
    
    return true;
}

bool fork2019TakeGoldenium(ServoList* servoList) {
    // Fork Push Off
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);

    // Elevator
    moveElevatorBottom(servoList);
    delaymSec(1000);
    
    // TODO : Scan to do => Return false if the scan is KO

    // Fork Single Puck
    moveForkSimplePuck(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    delaymSec(1000);

    // Elevator Up to free the Puck
    moveElevatorUp(servoList);
    delaymSec(1000);
    
    return true;
}

void fork2019Release(ServoList* servoList) {
    // Elevator Up 
    moveElevatorUp(servoList);
    delaymSec(1000);

    // Fork Push On
    moveForkPushOn(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    delaymSec(500);

    // Fork 
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    delaymSec(1000);

    // Fork Push Off
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    delaymSec(500);
}


// ARM On for Small Robot
void arm2019On(ServoList* servoList, unsigned int leftRight) {
    moveServo(servoList, leftRight,
        FORK_2019_LEFT_ARM_SERVO_INDEX, FORK_2019_RIGHT_ARM_SERVO_INDEX,
        FORK_2019_LEFT_ARM_SPEED_FACTOR, FORK_2019_RIGHT_ARM_SPEED_FACTOR,
        FORK_2019_LEFT_ARM_SERVO_ON, FORK_2019_RIGHT_ARM_SERVO_ON);
}

// ARM Off for Small Robot
void arm2019Off(ServoList* servoList, unsigned int leftRight) {
    moveServo(servoList, leftRight,
        FORK_2019_LEFT_ARM_SERVO_INDEX, FORK_2019_RIGHT_ARM_SERVO_INDEX,
        FORK_2019_LEFT_ARM_SPEED_FACTOR, FORK_2019_RIGHT_ARM_SPEED_FACTOR,
        FORK_2019_LEFT_ARM_SERVO_OFF, FORK_2019_RIGHT_ARM_SERVO_OFF);
}

void updateServoListName2019(ServoList* servoList) {
    
    // Arm (For small Robot only))
    getServo(servoList, FORK_2019_LEFT_ARM_SERVO_INDEX)->name = "ARM LEFT";
    getServo(servoList, FORK_2019_RIGHT_ARM_SERVO_INDEX)->name = "ARM RIGHT";
    
    // Elevator
    getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX)->name = "ELEV. UP/DOWN";
    getServo(servoList, FORK_2019_SCAN_SERVO_INDEX)->name = "ELEV SCAN";
    // Fork
    getServo(servoList, FORK_2019_LEFT_SERVO_FORK_INDEX)->name = "FORK LEFT";
    getServo(servoList, FORK_2019_RIGHT_SERVO_FORK_INDEX)->name = "FORK RIGHT";

    // Push
    getServo(servoList, FORK_2019_LEFT_SERVO_PUSH_INDEX)->name = "PUSH LEFT";
    getServo(servoList, FORK_2019_RIGHT_SERVO_PUSH_INDEX)->name = "PUSH RIGHT";
}