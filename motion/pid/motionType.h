#ifndef MOTION_TYPE_H
#define MOTION_TYPE_H

// MOTION

enum MotionType {
    /** No position to reach. */
    NO_POSITION_TO_REACH = 0,
    
    /** No position to reach, but a position to maintain. */
    POSITION_TO_MAINTAIN = 1,
    
    /** The trajectory is in progress. */
    POSITION_IN_PROGRESS = 2,
    
    /** The robot reach the position. */
    POSITION_REACHED = 3,
    
    /** The robot is directly blocked to move. */
    POSITION_BLOCKED_WHEELS = 4,
    
    /** The robot will hurt something (detection by RobotDetector). */
    POSITION_OBSTACLE = 5
};

#endif
