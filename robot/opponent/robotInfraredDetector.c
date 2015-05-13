#include "robotInfraredDetector.h"

#include "../../drivers/sharp/gp2d12.h"
#include "../../drivers/sharp/gp2y0a02yk.h"

#include "../../common/commons.h"
#include "../../common/adc/adcutils.h"

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
#define NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE                          120

/** Thresholds. */
#define DETECTED_THRESHOLD                                          6
#define NEG_VALUE                                                   6

/** The pointer on the global robotInfraredDetector system. */
static RobotInfraredDetector* robotInfraredDetector;

RobotInfraredDetector* getRobotInfraredDetector(void) {
    return robotInfraredDetector;
}

bool getRobotInfraredObstacleGroup(InfraredDetectorGroup* group) {
    // no detection
    if (group->wasDetectedCount < DETECTED_THRESHOLD) {
        return false;
    };
    // To avoid that notification continue
    group->wasDetectedCount = 0;
    group->doNotCheckBeforeCounter = NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE;
    // we must notify one time !
    return true;
}

bool getRobotInfraredObstacleForward(void) {
    return getRobotInfraredObstacleGroup(&(robotInfraredDetector->forwardDetectorGroup));
}

bool getRobotInfraredObstacleBackward(void) {
    return getRobotInfraredObstacleGroup(&(robotInfraredDetector->backwardDetectorGroup));
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
    group->interruptCounter++;
    // return if we placed a delay to notify, but continue
    // in the normal case
    if (group->interruptCounter <= group->doNotCheckBeforeCounter) {
        return;
    }
    group->doNotCheckBeforeCounter = 0;
    // rearm flags
    group->interruptCounter = 0;

    bool currentDetection = group->function();
    if (currentDetection) {
        group->wasDetectedCount++;
    }
    else {
        if (group->wasDetectedCount > NEG_VALUE) {
            group->wasDetectedCount -= NEG_VALUE;
        }
    }
}

void robotInfraredDetectorCallback(Timer* timer) {
    updateInfraredDetector(&(robotInfraredDetector->forwardDetectorGroup));
    updateInfraredDetector(&(robotInfraredDetector->backwardDetectorGroup));
}

void initInfraredDetectorGroup(InfraredDetectorGroup* group, enum InfraredDetectorGroupType type, InfraredDetectorFunction* function) {
    group->type = type;
    group->function = function;
    // By default, we don't want it notify at the beginning, because other boards are maybe not available to receive
    // the information ....
    group->notifyIfDetected = false;
}

void initRobotInfraredDetector(RobotInfraredDetector* robotInfraredDetectorParam) {
    robotInfraredDetector = robotInfraredDetectorParam;
    initInfraredDetectorGroup(&(robotInfraredDetector->forwardDetectorGroup), DETECTOR_GROUP_TYPE_FORWARD, &forwardDetection);
    initInfraredDetectorGroup(&(robotInfraredDetector->backwardDetectorGroup), DETECTOR_GROUP_TYPE_BACKWARD, &backwardDetection);
    addTimer(ROBOT_INFRARED_DETECTOR_TIMER_INDEX, TIME_DIVIDER_30_HERTZ, &robotInfraredDetectorCallback, "ROBOT_INFRARED");
}

void setInfraredRobotNotification(enum InfraredDetectorGroupType type, bool enable) {
    if (type == DETECTOR_GROUP_TYPE_FORWARD) {
        robotInfraredDetector->forwardDetectorGroup.notifyIfDetected = enable;
    }
    else if (type == DETECTOR_GROUP_TYPE_BACKWARD) {
        robotInfraredDetector->backwardDetectorGroup.notifyIfDetected = enable;
    }
}
