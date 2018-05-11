#ifndef MOTION_FAILED_DETECTION_H
#define MOTION_FAILED_DETECTION_H

#include <stdbool.h>

#include "../../../../common/commons.h"

#include "../../pidMotion.h"
#include "../parameters/motionEndDetectionParameter.h"
#include "../../instructionType.h"

/**
 * Detect if this is the end of the motion because we did not succeed to stabilize it before a timeout
 */
bool isMotionFailed(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
