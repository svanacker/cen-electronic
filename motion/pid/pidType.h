#ifndef PID_TYPE_H
#define PID_TYPE_H

#include "../../common/io/outputStream.h"

#include "../../motion/parameters/motionParameterType.h"

// -> TYPES OF PID

// different types of PID_TYPE
#define PID_TYPE_COUNT 5

enum PidType {
    /** The mask used to indicate that we want to use value of PID to go forward and backward. */
    PID_TYPE_GO_INDEX = 0,
    
    /** The mask used to indicate that we want to use value of PID to rotate. */
    PID_TYPE_ROTATE_INDEX = 1,
    
    /** The mask used to indicate that we want to use value of PID to maintain very strongly the position. */
    PID_TYPE_MAINTAIN_POSITION_INDEX = 2,
    
    /** The mask used to indicate that we want to adjust the robot to the border of board. */
    PID_TYPE_ADJUST_DIRECTION = 3,
    
    /** The pid for final approach. */
    PID_TYPE_FINAL_APPROACH_INDEX = 4
};

/**
 * Determines the type of pid which must be applied depending of the motionType.
 */
enum PidType getPidType(enum MotionParameterType motionParameterType);

/**
 * Append the type of the Pid as String into the outputStream.
 */
void appendPidTypeAsString(enum PidType pidType, OutputStream* outputStream);


#endif
