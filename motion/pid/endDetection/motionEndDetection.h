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
 * Necessary to call isEndOfMotion, or isRobotBlocked.
 */
void updateEndMotionData(PidComputationValues* computationValues, enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter, unsigned int time);

/**
 * Detects if the robot has end his motion and if it can continue to next instruction.
 */
bool isEndOfMotion(enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter);

/**
 * Detects if the robot is blocked, and if it must be stopped to avoid problems with motors.
 */
bool isRobotBlocked(PidMotionDefinition* motionDefinition, enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter);

#endif
