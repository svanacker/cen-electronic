#ifndef MOTION_SHOCKED_DETECTION_H
#define MOTION_SHOCKED_DETECTION_H

#include <stdbool.h>

#include "../../../../common/commons.h"

#include "../../pidMotion.h"
#include "../parameters/motionEndDetectionParameter.h"
#include "../../instructionType.h"

/**
 * Detect if the robot is shocked or not.
 * @param pidMotion
 * @param motionDefinition
 * @return 
 */
bool detectIfRobotIsShocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
