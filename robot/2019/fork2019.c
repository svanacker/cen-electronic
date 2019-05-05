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

#include "../../common/timer/delayTimer.h"

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

void moveElevatorDistributorScan(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_DISTRIBUTOR_SCAN_SERVO_VALUE);
}

void moveElevatorInitPosition(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_INIT_POSITION_SERVO_VALUE);
}

void moveElevatorUp(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_UP_SERVO_VALUE);
}

void moveElevatorToTakeGoldenium(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_GOLDENIUM_SERVO_VALUE);
}

void moveElevatorToScanGoldenium(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_GOLDENIUM_SCAN_SERVO_VALUE);
}

void moveElevatorLeft(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_LEFT_SERVO_VALUE);
    timerDelayMilliSeconds(500);
}

void moveElevatorMiddle(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_MIDDLE_SERVO_VALUE);
    timerDelayMilliSeconds(500);
}

void moveElevatorRight(ServoList* servoList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_RIGHT_SERVO_VALUE);
    timerDelayMilliSeconds(500);
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

void setForkTofListNameAndThreshold(TofSensorList* tofSensorList) {
    unsigned int tofSensorListSize = getTofSensorListSize(tofSensorList);

    if (tofSensorListSize > FORK_2019_LEFT_TOF_INDEX) {
        TofSensor* backMiddleSensor = getTofSensorByIndex(tofSensorList, FORK_2019_LEFT_TOF_INDEX);
        backMiddleSensor->orientationRadian = 0.0f;
        backMiddleSensor->thresholdDistanceMM = FORK_2019_LEFT_THRESHOLD;
        backMiddleSensor->name = "FORK LEFT";
    }

    if (tofSensorListSize > FORK_2019_RIGHT_TOF_INDEX) {
        TofSensor* backRightSensor = getTofSensorByIndex(tofSensorList, FORK_2019_RIGHT_TOF_INDEX);
        backRightSensor->orientationRadian = 0.0f;
        backRightSensor->thresholdDistanceMM = FORK_2019_RIGHT_THRESHOLD;
        backRightSensor->name = "FORK RIGHT";
    }
}

bool forkScan(ServoList* servoList, TofSensorList* tofSensorList, unsigned int leftRight) {
    if (leftRight == FORK_2019_LEFT_INDEX) {
        return forkScanFromLeftToRight(servoList, tofSensorList);
    } else if (leftRight == FORK_2019_RIGHT_INDEX) {
        return forkScanFromRightToLeft(servoList, tofSensorList);
    } else {
        Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
        bool scanOk = forkScanFromLeftToRight(servoList, tofSensorList);
        if (!scanOk) {
            return false;
        }
        unsigned int servoPosition = servo->currentPosition;
        scanOk = forkScanFromRightToLeft(servoList, tofSensorList);
        if (!scanOk) {
            return false;
        }
        unsigned int middleServoPosition = (servoPosition + servo->currentPosition) / 2;
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, middleServoPosition);
        timerDelayMilliSeconds(500);
        return true;
    }
}

bool internalForkScan(TofSensor* tofSensor) {
    unsigned int j = 0;
    unsigned int matchCount = 0;
    for (j = 0; j < FORK_2019_SCAN_MEASURE_COUNT; j++) {
        timerDelayMilliSeconds(FORK_2019_SCAN_TIME_BETWEEN_MEASURE_MILLISECONDS);
        unsigned int distance = tofSensor->tofGetDistanceMM(tofSensor);
        if (distance > 0 && distance < tofSensor->thresholdDistanceMM) {
            appendStringAndDecLN(getDebugOutputStreamLogger(), "threshold=", tofSensor->thresholdDistanceMM);
            appendStringAndDecLN(getDebugOutputStreamLogger(), "distance=", distance);
            matchCount++;
        }

    }
    if (matchCount >= FORK_2019_SCAN_MATCH_COUNT) {
        return true;
    }
    return false;
}

bool forkScanFromRightToLeft(ServoList* servoList, TofSensorList* tofSensorList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    moveElevatorRight(servoList);

    unsigned int i;
    for (i = FORK_2019_SCAN_RIGHT_SERVO_VALUE; i < FORK_2019_SCAN_LEFT_SERVO_VALUE; i += FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION) {
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i);
        timerDelayMilliSeconds(FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS);
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, FORK_2019_RIGHT_TOF_INDEX);
        if (internalForkScan(tofSensor)) {
            return true;
        }
    }
    return false;
}

bool forkScanFromLeftToRight(ServoList* servoList, TofSensorList* tofSensorList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    moveElevatorLeft(servoList);

    unsigned int i;
    for (i = FORK_2019_SCAN_LEFT_SERVO_VALUE; i > FORK_2019_SCAN_RIGHT_SERVO_VALUE; i -= FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION) {
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i);
        timerDelayMilliSeconds(FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS);
        TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, FORK_2019_LEFT_TOF_INDEX);
        if (internalForkScan(tofSensor)) {
            return true;
        }
    }
    return false;
}

// COMPLEXE OPERATIONS

void fork2019Init(ServoList* servoList) {
    // Go to the bottom 
    moveElevatorBottom(servoList);
    
    // Center the Elevator
    moveElevatorMiddle(servoList);

    // Fork Push Off)
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);

    // Fork Retracted
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
}

bool fork2019PrepareTakeSimplePuck(ServoList* servoList) {
    // Fork Push Off for both
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    
    // Fork Push Off for both
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);

    // Elevator
    moveElevatorDistributorScan(servoList);
    timerDelayMilliSeconds(500);
    
    return true;
}

bool fork2019TakeSimplePuck(ServoList* servoList, TofSensorList* tofSensorList) {
    // TODO : Scan to do => Return false if the scan is KO
    if (!forkScan(servoList, tofSensorList, FORK_2019_LEFT_AND_RIGHT_INDEX)) {
        return false;
    }
    
    moveElevatorBottom(servoList);
    timerDelayMilliSeconds(1000);

    // Fork Single Puck
    moveForkSimplePuck(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    timerDelayMilliSeconds(500);

    // Elevator Up to free the Puck
    moveElevatorInitPosition(servoList);
    timerDelayMilliSeconds(500);

    return true;
}

bool fork2019PrepareTakeGoldenium(ServoList* servoList, unsigned int leftRight) {
    if (leftRight == FORK_2019_LEFT_INDEX) {
        moveElevatorLeft(servoList);
    }
    else if (leftRight == FORK_2019_RIGHT_INDEX) {
        moveElevatorRight(servoList);    
    }
    
    // Fork Push Off for both !
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);

    // Fork Off for both !
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);

    // Elevator
    moveElevatorToScanGoldenium(servoList);

    return true;
}

bool fork2019TakeGoldenium(ServoList* servoList, TofSensorList* tofSensorList, unsigned int leftRight) {
    forkScan(servoList, tofSensorList, leftRight);

    moveElevatorToTakeGoldenium(servoList);
    timerDelayMilliSeconds(200);
    
    // Fork Single Puck
    moveForkDoublePuck(servoList, leftRight);
    timerDelayMilliSeconds(1000);

    // Elevator Up to free the Puck
    moveElevatorUp(servoList);
    timerDelayMilliSeconds(500);

    return true;
}

bool fork2019DropGoldenium(ServoList* servoList, unsigned int leftRight) {
    // Push
    moveForkPushOn(servoList, leftRight);

    // Fork back to let the puck without support
    moveForkBack(servoList, leftRight);

    // Push Off
    moveForkPushOff(servoList, leftRight);

    return true;
}

bool fork2019AcceleratorDrop(ServoList* servoList) {
    // Elevator Up 
    moveElevatorUp(servoList);
    timerDelayMilliSeconds(1000);

    // Fork Push On
    moveForkPushOn(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    timerDelayMilliSeconds(500);

    // Fork 
    moveForkBack(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    timerDelayMilliSeconds(1000);

    // Fork Push Off
    moveForkPushOff(servoList, FORK_2019_LEFT_AND_RIGHT_INDEX);
    timerDelayMilliSeconds(500);

    return true;
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