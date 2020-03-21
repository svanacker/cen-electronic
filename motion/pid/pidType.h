#ifndef PID_TYPE_H
#define PID_TYPE_H

#include <stdbool.h>

#include "../../motion/parameters/motionParameterType.h"
#include "../../motion/pid/instructionType.h"

// -> TYPES OF PID

// different types of PID_TYPE
#define PID_TYPE_COUNT 6

enum PidType {
    /** The type of pid when we don't know */
    PID_TYPE_NONE = 0,

    /** The mask used to indicate that we want to use value of PID to go forward and backward. */
    PID_TYPE_GO_INDEX = 1,

    /** The mask used to indicate that we want to use value of PID to rotate. */
    PID_TYPE_ROTATE_INDEX = 2,

    /** The pid for final approach. (Strong PID with more Integral ?) */
    PID_TYPE_FINAL_APPROACH_INDEX = 3,

    /** The mask used to indicate that we want to use value of PID to maintain very strongly the position (Very Strong PID). */
    PID_TYPE_MAINTAIN_POSITION_INDEX = 4,

    /** The mask used to indicate that we want to adjust the robot to the border of board (=> low PID). */
    PID_TYPE_ADJUST = 5
};

bool checkPidTypeIndexInRange(unsigned int pidTypeIndex);

/**
 * Returns how many pid type exists
 */
unsigned int getPidTypeCount(void);

/**
 * Convert the pidType enum to an index (useful for array).
 */
unsigned int pidTypeEnumToIndex(enum PidType pidType);

/**
 * Convert an numerical value (enum index) into pidType.
 */
enum PidType pidTypeValueOf(unsigned int pidTypeIndex);

/**
 * Determines the type of pid which must be applied depending of the motionType.
 */
enum PidType getPidType(enum MotionParameterType motionParameterType, enum InstructionType enumInstructionType);

#endif
