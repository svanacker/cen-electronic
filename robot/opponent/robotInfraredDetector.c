#include "robotInfraredDetector.h"

#include <stdbool.h>

#include "../../drivers/sharp/gp2d12.h"
#include "../../drivers/sharp/gp2y0a02yk.h"

#include "../../common/commons.h"
#include "../../common/adc/adcutils.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/timer/timerList.h"
#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerConstants.h"

// INDEX OF ADC
#define GP2D12_LEFT_ANX_INDEX             1
#define GP2D12_RIGHT_ANX_INDEX            0
#define GP2DY0A02YK_CENTER_ANX_INDEX      2
#define GP2DY0A02YK_BACK_ANX_INDEX        3


/** Distance of detection for forward. */
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CENTER_CM        40
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_LEFT_CM            25
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_RIGHT_CM            25

/** Distance of detection for backward. */
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_BACK_CM            5

/** Avoid to notify always. */
#define NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE                         20

/** Thresholds. */
#define DETECTED_THRESHOLD                                          6
#define NEG_VALUE                                                   3

/** The pointer on the global robotInfraredDetector system. */
static RobotInfraredDetector* robotInfraredDetector;

RobotInfraredDetector* getRobotInfraredDetector(void) {
    return robotInfraredDetector;
}

// Value

bool getRobotInfraredObstacleForward(void) {
    return robotInfraredDetector->forwardDetectorGroup.lastResult;
}

bool getRobotInfraredObstacleBackward(void) {
    return robotInfraredDetector->backwardDetectorGroup.lastResult;
}

// notify ?

bool mustNotifyRobotInfraredObstacleForward(void) {
    return robotInfraredDetector->forwardDetectorGroup.notifyIfDetected & robotInfraredDetector->forwardDetectorGroup.notifyFlag;
}

bool mustNotifyRobotInfraredObstacleBackward(void) {
    return robotInfraredDetector->backwardDetectorGroup.notifyIfDetected & robotInfraredDetector->backwardDetectorGroup.notifyFlag;
}

// reset Notify Flag

void resetNotifyRobotInfraredObstacleForward(void) {
    robotInfraredDetector->forwardDetectorGroup.notifyFlag = false;
}

void resetNotifyRobotInfraredObstacleBackward(void) {
    robotInfraredDetector->backwardDetectorGroup.notifyFlag = false;
}

bool forwardDetection(void) {

    float leftMilliVolt = getANX(GP2D12_LEFT_ANX_INDEX);
    float rightMilliVolt = getANX(GP2D12_RIGHT_ANX_INDEX);
    float centerMilliVolt = getANX(GP2DY0A02YK_CENTER_ANX_INDEX);


    float leftDistance = gp2d12GetCentimerDistanceForTension(leftMilliVolt);
    float centerDistance = gp2y0a02ykGetCentimerDistanceForTension(centerMilliVolt);
    float rightDistance = gp2d12GetCentimerDistanceForTension(rightMilliVolt);

    bool result = (leftDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_LEFT_CM
            || rightDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_RIGHT_CM
            || centerDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CENTER_CM);

    return result;
}

bool backwardDetection(void) {
    float backMilliVolt = getANX(GP2DY0A02YK_BACK_ANX_INDEX);
    float backDistance = gp2y0a02ykGetCentimerDistanceForTension(backMilliVolt);

    bool result = (backDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_BACK_CM);

    return result;
}

void updateInfraredDetector(InfraredDetectorGroup* group) {
    group->nextNotifyCounter++;
    /*
    if ((group->type == DETECTOR_GROUP_TYPE_FORWARD) & (group->nextNotifyCounter % 15 == 0)) {
        printRobotInfraredDetectorGroup(getDebugOutputStreamLogger(), group);
    }
     */

    // Call the detect function
    bool currentDetection = group->function();
    if (currentDetection) {
        group->detectedCount++;
    } else {
        // Try to balance that we see more than X% of time something
        if (group->detectedCount >= NEG_VALUE) {
            group->detectedCount -= NEG_VALUE;
        } else {
            group->detectedCount = 0;
        }
    }

    // instantaneous value
    group->lastResult = group->detectedCount >= DETECTED_THRESHOLD;

    if (group->lastResult) {
        group->result = true;

        // reset the value of detection
        group->detectedCount = 0;

        // We can only notify if the delay is ok
        if (group->nextNotifyCounter >= NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE) {
            // The board must notify !
            group->notifyFlag = true;

            // delay next notification
            group->nextNotifyCounter = 0;
        }
    } else {
        if (group->nextNotifyCounter >= NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE) {
            // only after a time, we consider that there is no value anymore and that we dont notify anymore
            group->result = false;
        }
    }
}

void robotInfraredDetectorCallback(Timer* timer) {
    updateInfraredDetector(&(robotInfraredDetector->forwardDetectorGroup));
    // updateInfraredDetector(&(robotInfraredDetector->backwardDetectorGroup));
}

void initInfraredDetectorGroup(InfraredDetectorGroup* group, enum InfraredDetectorGroupType type, InfraredDetectorFunction* function) {
    group->type = type;
    group->function = function;
    // By default, we don't want it notify at the beginning, because other boards are maybe not available to receive
    // the information ....
    group->notifyIfDetected = true;
}

void initRobotInfraredDetector(RobotInfraredDetector* robotInfraredDetectorParam) {
    robotInfraredDetector = robotInfraredDetectorParam;
    initInfraredDetectorGroup(&(robotInfraredDetector->forwardDetectorGroup), DETECTOR_GROUP_TYPE_FORWARD, &forwardDetection);
    initInfraredDetectorGroup(&(robotInfraredDetector->backwardDetectorGroup), DETECTOR_GROUP_TYPE_BACKWARD, &backwardDetection);
    addTimer(ROBOT_INFRARED_DETECTOR_TIMER_INDEX, TIME_DIVIDER_30_HERTZ, &robotInfraredDetectorCallback, "ROBOT_INFRARED");
}

void setInfraredRobotNotification(enum InfraredDetectorGroupType type, bool enabled) {
    if (type == DETECTOR_GROUP_TYPE_FORWARD) {
        robotInfraredDetector->forwardDetectorGroup.notifyIfDetected = enabled;
    } else if (type == DETECTOR_GROUP_TYPE_BACKWARD) {
        robotInfraredDetector->backwardDetectorGroup.notifyIfDetected = enabled;
    }
}

// DEBUG

void printRobotInfraredDetectorGroup(OutputStream* outputStream, InfraredDetectorGroup* group) {
    appendStringAndDec(outputStream, "notifyIfDetected=", group->notifyIfDetected);
    appendStringAndDec(outputStream, ", lastResult=", group->lastResult);
    appendStringAndDec(outputStream, ", result=", group->result);
    appendStringAndDec(outputStream, ", notifyFlag=", group->notifyFlag);
    appendStringAndDec(outputStream, ", nextNotifyCounter=", group->nextNotifyCounter);
    appendStringAndDec(outputStream, ", detectedCount=", group->detectedCount);
    appendCRLF(outputStream);
}
