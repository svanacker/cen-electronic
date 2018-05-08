#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include "parameters/motionParameterType.h"
#include "pid/detectedMotionType.h"
#include "pid/pidMotion.h"


// HANDLING FUNCTION

#define SPEED_MM_BY_SEC_DIGIT_PRECISION              0
#define ACCELERATION_MM_BY_SEC_2_DIGIT_PRECISION       0


/**
 * Handle function so the robot is aware of asking.
 */
void handleInstructionAndMotion(PidMotion* pidMotion, OutputStream* notificationOutputStream);

/**
 * Wait after the end of a position, or a position which is maintained.
 */
void handleAndWaitFreeMotion(PidMotion* pidMotion, OutputStream* notificationOutputStream);

/**
 * Handle and wait after a delay of milliseconds.
 * TODO : breaks if there is another instruction ???
 */
void handleAndWaitMSec(PidMotion* pidMotion, OutputStream* notificationOutputStream, unsigned long delayMs);



#endif
