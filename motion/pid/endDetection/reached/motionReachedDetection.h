#ifndef MOTION_REACHED_DETECTION_H
#define MOTION_REACHED_DETECTION_H

#include <stdbool.h>

#include "../../../../common/commons.h"

#include "../../pidMotion.h"
#include "../parameters/motionEndDetectionParameter.h"
#include "../../instructionType.h"

/**
 * Detect if this is the end of the motion
 */
bool isMotionReached(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
