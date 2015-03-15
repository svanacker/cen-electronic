#ifndef MOTION_H
#define MOTION_H

#include <stdbool.h>
#include "parameters/motionParameterType.h"
#include "pid/detectedMotionType.h"
// TODO : To Remove
#include "extended/bspline.h"

// HANDLING FUNCTION

/**
 * Handle function so the robot is aware of asking.
 */
enum DetectedMotionType handleInstructionAndMotion(void);

/**
 * Wait after the end of a position, or a position which is maintained.
 */
enum DetectedMotionType handleAndWaitFreeMotion(void);

/**
 * Handle and wait after a delay of milliseconds.
 * TODO : breaks if there is another instruction ???
 */
void handleAndWaitMSec(unsigned long delayMs);



#endif
