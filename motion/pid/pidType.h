#ifndef PID_TYPE_H
#define PID_TYPE_H

// -> TYPES OF PID

typedef unsigned char PidType;

// different types of PID_TYPE
#define PID_TYPE_COUNT 5

/** The mask used to indicate that we want to use value of PID to go forward and backward. */
#define PID_TYPE_GO_INDEX 0

/** The mask used to indicate that we want to use value of PID to rotate. */
#define PID_TYPE_ROTATE_INDEX 1

/** The mask used to indicate that we want to use value of PID to maintain very strongly the position. */
#define PID_TYPE_MAINTAIN_POSITION_INDEX 2

/** The mask used to indicate that we want to adjust the robot to the border of board. */
#define PID_TYPE_ADJUST_DIRECTION 3

/** The pid for final approach. */
#define PID_TYPE_FINAL_APPROACH_INDEX 4

#endif
