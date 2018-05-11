#ifndef MOTION_OBSTACLE_DETECTION_H
#define MOTION_OBSTACLE_DETECTION_H

#include <stdbool.h>

#include "../../../../common/commons.h"

#include "../../pidMotion.h"
#include "../parameters/motionEndDetectionParameter.h"
#include "../../instructionType.h"

/**
 * Detect if the robot has an obstacle in Front of him.
 * @param pidMotion
 * @param motionDefinition
 * @return 
 */
bool detectIfRobotHasObstacle(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
