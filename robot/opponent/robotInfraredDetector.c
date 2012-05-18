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
#define ROBOT_INFRARED_DETECTOR_TIMER_INDEX			15

#define GP2D12_LEFT_ANX_INDEX			1
#define GP2D12_RIGHT_ANX_INDEX			0
#define GP2DY0A02YK_CENTER_ANX_INDEX	2
#define GP2DY0A02YK_BACK_ANX_INDEX		3


/** Distance of detection for forward. */
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CENTER_CM		40
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_LEFT_CM			25
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_RIGHT_CM			25

/** Distance of detection for backward. */
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_BACK_CM			25


/** Avoid to notify always. */
#define NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE				400

#define DETECTED_THRESHOLD									15
#define NEG_VALUE											3

static InfraredDetectorGroup forwardDetector;
static InfraredDetectorGroup backwardDetector;

BOOL getRobotInfraredObstacleGroup(InfraredDetectorGroup* group) {
	// no detection
	if (group->wasDetectedCount < DETECTED_THRESHOLD) {
		return FALSE;
	};
	// To avoid that notification continue
	group->wasDetectedCount = 0;
	group->doNotCheckBeforeCounter = NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE;
	// we must notify one time !
	return TRUE;
}

BOOL getRobotInfraredObstacleForward() {
	return getRobotInfraredObstacleGroup(&forwardDetector);
}

BOOL getRobotInfraredObstacleBackward() {
	return getRobotInfraredObstacleGroup(&backwardDetector);
}

BOOL forwardDetection() {

	float leftMilliVolt = getANX(GP2D12_LEFT_ANX_INDEX);
	float rightMilliVolt = getANX(GP2D12_RIGHT_ANX_INDEX);
	float centerMilliVolt = getANX(GP2DY0A02YK_CENTER_ANX_INDEX);


	float leftDistance = gp2d12GetCentimerDistanceForTension(leftMilliVolt);
	float centerDistance = gp2y0a02ykGetCentimerDistanceForTension(rightMilliVolt);
	float rightDistance = gp2d12GetCentimerDistanceForTension(centerMilliVolt);

	BOOL result = (leftDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_LEFT_CM 
				|| rightDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_RIGHT_CM 
				|| centerDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CENTER_CM);

	return result;
}

BOOL backwardDetection() {
	float backMilliVolt = getANX(GP2DY0A02YK_BACK_ANX_INDEX);
	float backDistance = gp2y0a02ykGetCentimerDistanceForTension(backMilliVolt);

	BOOL result = (backDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_BACK_CM);

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

	BOOL currentDetection = group->function();
	if (currentDetection) {
		group->wasDetectedCount++;
	}
	else {
		if (group->wasDetectedCount > NEG_VALUE) {
			group->wasDetectedCount -= NEG_VALUE;
		}
	}
}

void robotInfraredDetectorCallback() {
	updateInfraredDetector(&forwardDetector);
	updateInfraredDetector(&backwardDetector);
}


void initRobotInfraredDetector() {
	addTimer(ROBOT_INFRARED_DETECTOR_TIMER_INDEX, TIME_DIVISER_100_HERTZ, &robotInfraredDetectorCallback);
	forwardDetector.function = &forwardDetection;
	backwardDetector.function = &backwardDetection;
}

