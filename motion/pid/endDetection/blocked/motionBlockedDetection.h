#ifndef MOTION_BLOCKED_DETECTION_H
#define MOTION_BLOCKED_DETECTION_H

#include <stdbool.h>

#include "../../../../common/commons.h"

#include "../../pidMotion.h"
#include "../parameters/motionEndDetectionParameter.h"
#include "../../instructionType.h"

/**
 * Detect if this is the end of the motion because the robot is blocked
 */
bool isMotionBlocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
