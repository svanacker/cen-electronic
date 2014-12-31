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

// Timer Index for Robot infrared
#define ROBOT_INFRARED_DETECTOR_TIMER_INDEX            15

#define GP2D12_LEFT_ANX_INDEX            1
#define GP2D12_RIGHT_ANX_INDEX            0
#define GP2DY0A02YK_CENTER_ANX_INDEX    2
#define GP2DY0A02YK_BACK_ANX_INDEX        3


/** Distance of detection for forward. */
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CENTER_CM        40
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_LEFT_CM            25
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_RIGHT_CM            25

/** Distance of detection for backward. */
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_BACK_CM            5


/** Avoid to notify always. */
#define NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE                120

#define DETECTED_THRESHOLD                                    6
#define NEG_VALUE                                            6

static InfraredDetectorGroup forwardDetector;
static InfraredDetectorGroup backwardDetector;

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

bool getRobotInfraredObstacleForward() {
    return getRobotInfraredObstacleGroup(&forwardDetector);
}

bool getRobotInfraredObstacleBackward() {
    return getRobotInfraredObstacleGroup(&backwardDetector);
}

bool forwardDetection() {

    float leftMilliVolt = getANX(GP2D12_LEFT_ANX_INDEX);
    float rightMilliVolt = getANX(GP2D12_RIGHT_ANX_INDEX);
    float centerMilliVolt = getANX(GP2DY0A02YK_CENTER_ANX_INDEX);


    float leftDistance = gp2d12GetCentimerDistanceForTension(leftMilliVolt);
    float centerDistance = gp2y0a02ykGetCentimerDistanceForTension(rightMilliVolt);
    float rightDistance = gp2d12GetCentimerDistanceForTension(centerMilliVolt);

    bool result = (leftDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_LEFT_CM 
                || rightDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_RIGHT_CM 
                || centerDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CENTER_CM);

    return result;
}

bool backwardDetection() {
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
    updateInfraredDetector(&forwardDetector);
    updateInfraredDetector(&backwardDetector);
}


void initRobotInfraredDetector() {
    addTimer(ROBOT_INFRARED_DETECTOR_TIMER_INDEX, TIME_DIVIDER_30_HERTZ, &robotInfraredDetectorCallback, "ROBOT_INFRARED");
    forwardDetector.function = &forwardDetection;
    backwardDetector.function = &backwardDetection;
}

