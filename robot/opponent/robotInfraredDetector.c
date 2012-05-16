#include "robotInfraredDetector.h"

#include "../../drivers/sharp/gp2d12.h"
#include "../../drivers/sharp/gp2y0a02yk.h"

#include "../../common/commons.h"
#include "../../common/adc/adcutils.h"

#include "../../common/timer/timerList.h"
#include "../../common/timer/cenTimer.h"

// Timer Index for Robot infrared
#define ROBOT_INFRARED_DETECTOR_TIMER_INDEX			15

#define GP2D12_LEFT_ANX_INDEX			1
#define GP2D12_RIGHT_ANX_INDEX			0
#define GP2DY0A02YK_CENTER_ANX_INDEX	2

/** Distance for detection. */
#define ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CM		50

static BOOL wasDetected;

BOOL getRobotInfraredObstacle() {
	return wasDetected;
}

void robotInfraredDetectorCallback() {
	float leftMilliVolt = getANX(GP2D12_LEFT_ANX_INDEX);
	float rightMilliVolt = getANX(GP2D12_RIGHT_ANX_INDEX);
	float centerMilliVolt = getANX(GP2DY0A02YK_CENTER_ANX_INDEX);


	float leftDistance = gp2d12GetCentimerDistanceForTension(leftMilliVolt);
	float centerDistance = gp2y0a02ykGetCentimerDistanceForTension(rightMilliVolt);
	float rightDistance = gp2d12GetCentimerDistanceForTension(centerMilliVolt);

	wasDetected = (leftDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CM 
				|| rightDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CM 
				|| centerDistance < ROBOT_INFRARED_DETECTOR_DISTANCE_THRESHOLD_CM);
}


void initRobotInfraredDetector() {
	addTimer(ROBOT_INFRARED_DETECTOR_TIMER_INDEX, TIME_DIVISER_16_HERTZ, &robotInfraredDetectorCallback);
}
