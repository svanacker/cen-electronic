#include "forkScan2019.h"

#include "fork2019.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/error/error.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cConstants.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../common/log/logger.h"

#include "../../../common/timer/delayTimer.h"

#include "../../../drivers/tof/tofDetectionUtils.h"

#include "../../../drivers/ioExpander/ioExpanderList.h"

#include "../../../drivers/i2c/multiplexer/multiplexerList.h"

// TOF CONFIG

void forkScan2019ConfigTofList(TofSensor* leftForkScanSensor,
                              TofSensor* rightForkScanSensor,
                              MultiplexerList* multiplexerList,
                              IOExpanderList* ioExpanderList) {
    if (leftForkScanSensor != NULL) {
        leftForkScanSensor->name = "FORK LEFT";
        leftForkScanSensor->enabled = true;
        leftForkScanSensor->usageType = TOF_SENSOR_USAGE_TYPE_ACTION;
        leftForkScanSensor->orientationRadian = 0.0f;
        leftForkScanSensor->thresholdMinDistanceMM = FORK_2019_SCAN_DISTANCE_LEFT_MIN_THRESHOLD;
        leftForkScanSensor->thresholdMaxDistanceMM = FORK_2019_SCAN_DISTANCE_LEFT_MAX_THRESHOLD;
        
        leftForkScanSensor->changeAddress = true;
        leftForkScanSensor->targetAddress = VL530X_ADDRESS_12;
        leftForkScanSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 0);
        leftForkScanSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_4;
        
        // RESTART
        leftForkScanSensor->hardwareRestartable = true;
        leftForkScanSensor->hardwareRestartIOExpander = getIOExpanderByIndex(ioExpanderList, FORK_2019_HARDWARE_IO_EXPANDER_INDEX);
        leftForkScanSensor->hardwareRestartIOExpanderIoIndex = FORK_2019_LEFT_HARDWARE_IO_EXPANDER_IO_INDEX;
    }
    if (rightForkScanSensor != NULL) {
        rightForkScanSensor->name = "FORK RIGHT";
        rightForkScanSensor->enabled = true;
        rightForkScanSensor->usageType = TOF_SENSOR_USAGE_TYPE_ACTION;
        
        rightForkScanSensor->orientationRadian = 0.0f;
        rightForkScanSensor->thresholdMinDistanceMM = FORK_2019_SCAN_DISTANCE_RIGHT_MIN_THRESHOLD;
        rightForkScanSensor->thresholdMaxDistanceMM = FORK_2019_SCAN_DISTANCE_RIGHT_MAX_THRESHOLD;
        
        rightForkScanSensor->changeAddress = true;
        rightForkScanSensor->targetAddress = VL530X_ADDRESS_11;
        rightForkScanSensor->multiplexer = getMultiplexerByIndex(multiplexerList, 0);
        rightForkScanSensor->multiplexerChannel = MULTIPLEXER_CHANNEL_3;
        rightForkScanSensor->hardwareRestartable = true;
        rightForkScanSensor->hardwareRestartIOExpander = getIOExpanderByIndex(ioExpanderList, FORK_2019_HARDWARE_IO_EXPANDER_INDEX);
        rightForkScanSensor->hardwareRestartIOExpanderIoIndex = FORK_2019_RIGHT_HARDWARE_IO_EXPANDER_IO_INDEX;
    }
}

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
        if (isTofDistanceInRange(tofSensor)) {
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
    appendStringLN(getDebugOutputStreamLogger(),  "forkScanFromRightToLeft");

    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);

    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, FORK_2019_RIGHT_TOF_INDEX);
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_NULL);
        return false;
    }
    if (!tofSensor->enabled) {
        // If disabled , we try to go back on the middle
        moveElevatorMiddle(servoList, true);
        return false;
    }
    
    moveElevatorRight(servoList, true);

    unsigned int i;
    for (i = FORK_2019_SCAN_RIGHT_SERVO_VALUE; i < FORK_2019_SCAN_LEFT_SERVO_VALUE; i += FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION) {
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i, false);
        timerDelayMilliSeconds(FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS);
        // Scan several time
        if (internalForkScan(tofSensor)) {
            return true;
        }
    }
    
    // If not found, we try to go back on the middle
    moveElevatorMiddle(servoList, true);

    return false;
}

bool forkScanFromLeftToRight(ServoList* servoList, TofSensorList* tofSensorList) {
    appendStringLN(getDebugOutputStreamLogger(),  "forkScanFromLeftToRight");
    
    // Avoid to do the scan if 
    TofSensor* tofSensor = getTofSensorByIndex(tofSensorList, FORK_2019_LEFT_TOF_INDEX);
    if (tofSensor == NULL) {
        writeError(TOF_SENSOR_NULL);
        return false;
    }
    if (!tofSensor->enabled) {
        // If disabled , we try to go back on the middle
        moveElevatorMiddle(servoList, true);
        return false;
    }

    Servo* servo = getServo(servoList, FORK_2019_SCAN_SERVO_INDEX);

    unsigned int i;
    moveElevatorLeft(servoList, true);
    for (i = FORK_2019_SCAN_LEFT_SERVO_VALUE; i > FORK_2019_SCAN_RIGHT_SERVO_VALUE; i -= FORK_2019_SCAN_SERVO_DELTA_SERVO_POSITION) {
        pwmServo(servo, FORK_2019_SCAN_SPEED_FACTOR, i, false);
        timerDelayMilliSeconds(FORK_2019_SCAN_SERVO_DELTA_MILLISECONDS);
        // Scan several time
        if (internalForkScan(tofSensor)) {
            return true;
        }
    }
    // If not found, we try to go back on the middle
    moveElevatorMiddle(servoList, true);

    return false;
}
