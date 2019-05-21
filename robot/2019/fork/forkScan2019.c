#include "forkScan2019.h"

#include "fork2019.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/error/error.h"
#include "../../../common/log/logger.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/timer/delayTimer.h"
#include "i2cCommon.h"

// ELEVATOR SCAN

void moveElevatorLeft(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_LEFT_SERVO_VALUE, wait);
}

void moveElevatorMiddle(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_MIDDLE_SERVO_VALUE, wait);
}

void moveElevatorRight(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);
    pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, FORK_2019_SCAN_RIGHT_SERVO_VALUE, wait);
}

// TOF

void setForkTofListNameAndThreshold(TofSensorList* tofSensorList) {
    unsigned int tofSensorListSize = getTofSensorListSize(tofSensorList);

    if (tofSensorListSize > FORK_2019_LEFT_TOF_INDEX) {
        TofSensor* backMiddleSensor = getTofSensorByIndex(tofSensorList, FORK_2019_LEFT_TOF_INDEX);
        backMiddleSensor->type = TOF_SENSOR_TYPE_ACTION;
        backMiddleSensor->orientationRadian = 0.0f;
        backMiddleSensor->thresholdDistanceMM = FORK_2019_SCAN_DISTANCE_LEFT_THRESHOLD;
        backMiddleSensor->name = "FORK LEFT";
    }

    if (tofSensorListSize > FORK_2019_RIGHT_TOF_INDEX) {
        TofSensor* backRightSensor = getTofSensorByIndex(tofSensorList, FORK_2019_RIGHT_TOF_INDEX);
        backRightSensor->type = TOF_SENSOR_TYPE_ACTION;
        backRightSensor->orientationRadian = 0.0f;
        backRightSensor->thresholdDistanceMM = FORK_2019_SCAN_DISTANCE_RIGHT_THRESHOLD;
        backRightSensor->name = "FORK RIGHT";
    }
}


void moveElevatorDistributorScan(ServoList* servoList, bool wait) {
    Servo* servo = getServo(servoList, FORK_2019_ELEVATOR_SERVO_INDEX);
    pwmServo(servo, FORK_2019_ELEVATOR_SPEED_FACTOR, FORK_2019_ELEVATOR_DISTRIBUTOR_SCAN_SERVO_VALUE, wait);
}

bool forkScan(ServoList* servoList, TofSensorList* tofSensorList, unsigned int leftRight) {
    if (leftRight == FORK_2019_LEFT_INDEX) {
        return forkScanFromLeftToRight(servoList, tofSensorList);
    }
    else if (leftRight == FORK_2019_RIGHT_INDEX) {
        return forkScanFromRightToLeft(servoList, tofSensorList);
    }
    // Double Scan for small Distributor
    else {
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
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, middleServoPosition, true);
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

    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, FORK_2019_RIGHT_TOF_INDEX);
    if (internalForkScan(tofSensor)) {
        return true;
    }
    if (!tofSensor->enabled) {
        return false;
    }
    else {
        moveElevatorRight(servoList, true);

        unsigned int i;
        for (i = FORK_2019_SCAN_RIGHT_SERVO_VALUE; i < FORK_2019_SCAN_LEFT_SERVO_VALUE; i += FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION) {
            pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i, false);
            timerDelayMilliSeconds(FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS);
        }
    }
    
    // If disabled or not found, we try to go back on the middle
    moveElevatorMiddle(servoList, true);

    return false;
}

bool forkScanFromLeftToRight(ServoList* servoList, TofSensorList* tofSensorList) {
    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);

    unsigned int i;
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, FORK_2019_LEFT_TOF_INDEX);
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_NULL);
        return false;
    }
    if (!tofSensor->enabled) {
        return false;
    }
    else {
        moveElevatorLeft(servoList, true);
        for (i = FORK_2019_SCAN_LEFT_SERVO_VALUE; i > FORK_2019_SCAN_RIGHT_SERVO_VALUE; i -= FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION) {
            pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i, false);
            timerDelayMilliSeconds(FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS);
            if (internalForkScan(tofSensor)) {
                return true;
            }
        }
    }
    // If disabled or not found, we try to go back on the middle
    moveElevatorMiddle(servoList, true);

    return false;
}
