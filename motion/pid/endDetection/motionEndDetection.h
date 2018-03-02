#ifndef MOTION_END_DETECTION_H
#define MOTION_END_DETECTION_H

#include <stdbool.h>

#include "../../../common/commons.h"

#include "../pidMotion.h"
#include "motionEndInfo.h"
#include "motionEndDetectionParameter.h"
#include "../instructionType.h"

/**
* Reset the structure to detects end of motion.
*/
void resetMotionEndData(MotionEndInfo* endMotion);

/**
 * Detect if the robot is blocked or not.
 * @param pidMotion
 * @param motionDefinition
 * @return 
 */
void detectIfRobotIsBlocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
