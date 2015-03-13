#ifndef MOTION_END_DETECTION_H
#define MOTION_END_DETECTION_H

#include <stdbool.h>

#include "motionEndDetectionParameter.h"
#include "../instructionType.h"

#include "../../../common/commons.h"

/**
 * Define the detection of end of trajectory.
 */
#define MOTION_END_MASK_STOP 1

/**
 * Define the detection of a blocking.
 */
#define MOTION_END_MASK_BLOCKED 2

/**
 * Define the number of block of history for u and deltaPosition
 */
#define MAX_HISTORY_COUNT 3

/**
 * Defines the structs about motion blocking detection to be able to detect blocking or end of motion.
 * We analyze the motion during a constant time maxTime.
 * To avoid Range analysis by block, we consider the compute of value like a Stack. When we add a value, we substracted
 * the first value to always have a sliping range
 */
typedef struct MotionEndInfo {
    unsigned int integralTime;
    /** Current index in the array. */
    unsigned int index;
    /** The integral of the absolute value of delta position. */
    float absDeltaPositionIntegralHistory[MAX_HISTORY_COUNT];
    // the compute of related array
    float absDeltaPositionIntegral;
    /** The integral of the consign determined by the pid computer */
    float absUIntegralHistory[MAX_HISTORY_COUNT];
    // the compute of related array
    float absUIntegral;
} MotionEndInfo;

// BLOCKING DETECTION

/** Defines the delta position integral for which we consider that below this value the robot don't move */
#define ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD 1.0f

/**
 * Defines the u integral factor integral for which we consider that there is a blocking.
 * For example, if the value is equal to 4, it indicates that if the average integral of U is more than
 * the normal value of u (with no load), we must consider it as a blocking
 */
#define MAX_U_INTEGRAL_FACTOR_THRESHOLD 3.0f

/**
 * When the robot is very low, the answer of the motor is not linear, and we can thing that the robot is blocked, because,
 * the consign is very high compared to the normal value
 */
#define MAX_U_INTEGRAL_CONSTANT_THRESHOLD 10.0f

/**
 * The delay for which we consider that we are blocked or if we have reached if we don't go anymore
 */
#define BLOCKING_OR_REACH_DETECTION_DELAY 10

/**
 * The delay for which we do not try to know if the robot is rolling or blocked
 */
#define BLOCKING_OR_REACH_SKIP_DETECTION_DELAY 60

/**
* Reset the structure to detects end of motion.
*/
void resetMotionEndData(MotionEndInfo* endMotion);

/**
 * Detects for a instruction, if motion is finished, or blocked.
 * @param instructionType the instruction for which we want to know if it's finished or not
 * @return binary mask 0x0000 0001 if stopped, 0x0000 0010 if stopped with blocking
 */
unsigned int detectsEndOfMotion(enum InstructionType instructionType, MotionEndInfo* endMotion);

/**
 * Necessary to call isEndOfMotion, or isRobotBlocked.
 */
void updateEndMotionData(enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter, int time);

/**
 * Detects if the robot has end his motion and if it can continue to next instruction.
 */
bool isEndOfMotion(enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter);

/**
 * Detects if the robot is blocked, and if it must be stopped to avoid problems with motors.
 */
bool isRobotBlocked(enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter);

#endif
