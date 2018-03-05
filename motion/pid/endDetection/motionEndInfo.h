#ifndef MOTION_END_INFO_H
#define MOTION_END_INFO_H

#include <stdbool.h>

#include "../../../common/commons.h"

/**
 * Unit which handle to detect if we are at the end of a motion
 * The motion could be ended for 2 reasons :
 * - The integral of speed is very low compared to what it should be
 */


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
#define MAX_HISTORY_COUNT 10

/**
* Defines the structure about motion blocking detection to be able to detect blocking or end of motion.
* We analyze the motion during a constant time maxTime.
* To avoid Range analysis by block, we consider the compute of value like a Stack. When we add a value, we subtract
* the first value to always have a sliding range
*/
typedef struct MotionEndInfo {
    /** How many measure we have done */
	unsigned int integralTime;
	/** The integral of the absolute value of each delta position for a period of time. */
	float absSpeedIntegralHistory[MAX_HISTORY_COUNT];
	// the compute of related array (sum of each previous element between )
	float absSpeedIntegral;
	/** The integral of the value (in volt) determined by the pid computer */
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
