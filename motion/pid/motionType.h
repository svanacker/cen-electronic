#ifndef MOTION_TYPE_H
#define MOTION_TYPE_H

// MOTION

typedef unsigned char MotionType;

/** No position to reach. */
#define NO_POSITION_TO_REACH 0

/** No position to reach, but a position to maintain. */
#define POSITION_TO_MAINTAIN 1

/** The trajectory is in progress. */
#define POSITION_IN_PROGRESS 2

/** The robot reach the position. */
#define POSITION_REACHED 3

/** The robot is directly blocked to move. */
#define POSITION_BLOCKED_WHEELS 4

/** The robot will hurt something (detection by RobotDetector). */
#define POSITION_OBSTACLE 5

#endif
