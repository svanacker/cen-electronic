#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include "parameters/motionParameterType.h"
#include "pid/detectedMotionType.h"
#include "pid/pidMotion.h"

// HANDLING FUNCTION

/**
 * Handle function so the robot is aware of asking.
 */
void handleInstructionAndMotion(PidMotion* pidMotion);

/**
 * Wait after the end of a position, or a position which is maintained.
 */
void handleAndWaitFreeMotion(PidMotion* pidMotion);

/**
 * Handle and wait after a delay of milliseconds.
 * TODO : breaks if there is another instruction ???
 */
void handleAndWaitMSec(PidMotion* pidMotion, unsigned long delayMs);



#endif
