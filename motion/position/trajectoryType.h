#ifndef TRAJECTORY_TYPE_H
#define TRAJECTORY_TYPE_H

/**
 * Define at a "low level" the kind of move
 */
enum TrajectoryType {
    /** Static position */
    TRAJECTORY_TYPE_NONE = 0,

    /** Forward move */
    TRAJECTORY_TYPE_FORWARD = 1,

    /** Backward move. */
    TRAJECTORY_TYPE_BACKWARD = 2,

    /** Rotation */
    TRAJECTORY_TYPE_ROTATION = 3
};

#endif
