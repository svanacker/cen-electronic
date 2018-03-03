#ifndef MOTION_END_INFO_H
#define MOTION_END_INFO_H

#include <stdbool.h>

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
* Defines the structure about motion blocking detection to be able to detect blocking or end of motion.
* We analyze the motion during a constant time maxTime.
* To avoid Range analysis by block, we consider the compute of value like a Stack. When we add a value, we subtract
* the first value to always have a sliding range
*/
typedef struct MotionEndInfo {
    /** How many measure we have done */
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

/**
 * Clear the structure to init or reinit it
 * @param endMotion
 */
void resetMotionEndInfo(MotionEndInfo* endMotion);

#endif
