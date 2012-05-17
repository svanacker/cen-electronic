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

/** Distance for detection for the center. */
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CENTER_CM		40
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_LEFT_CM			25
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_RIGHT_CM			25


/** Avoid to notify always. */
#define NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE				200

#define DETECTED_THRESHOLD									10
#define NEG_VALUE											3

static int wasDetectedCount;
static BOOL doNotCheckBeforeCounter;
static unsigned int interruptCounter;

BOOL getRobotInfraredObstacle() {
	// no detection
	if (wasDetectedCount < DETECTED_THRESHOLD) {
		return FALSE;
	};
	// To avoid that notification continue
	wasDetectedCount = 0;
	doNotCheckBeforeCounter = NOTIFY_INFRARED_DETECTOR_TIMER_CYCLE;
	// we must notify one time !
	return TRUE;
}

void robotInfraredDetectorCallback() {
	interruptCounter++;
    // return if we placed a delay to notify, but continue
	// in the normal case
    if (interruptCounter <= doNotCheckBeforeCounter) {
        return;
    }
    doNotCheckBeforeCounter = 0;
    // rearm flags
    interruptCounter = 0;

	float leftMilliVolt = getANX(GP2D12_LEFT_ANX_INDEX);
	float rightMilliVolt = getANX(GP2D12_RIGHT_ANX_INDEX);
	float centerMilliVolt = getANX(GP2DY0A02YK_CENTER_ANX_INDEX);


	float leftDistance = gp2d12GetCentimerDistanceForTension(leftMilliVolt);
	float centerDistance = gp2y0a02ykGetCentimerDistanceForTension(rightMilliVolt);
	float rightDistance = gp2d12GetCentimerDistanceForTension(centerMilliVolt);

	unsigned currentDetectionCount;
	
	BOOL currentDetection = (leftDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_LEFT_CM 
				|| rightDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_RIGHT_CM 
				|| centerDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CENTER_CM);
	if (currentDetection) {
		wasDetectedCount++;

	}
	else {
		if (wasDetectedCount > NEG_VALUE) {
			wasDetectedCount -= NEG_VALUE;
		}
	}
	appendStringAndDec(getOutputStreamLogger(ALWAYS), "\n", wasDetectedCount);

}


void initRobotInfraredDetector() {
	addTimer(ROBOT_INFRARED_DETECTOR_TIMER_INDEX, TIME_DIVISER_50_HERTZ, &robotInfraredDetectorCallback);
}
