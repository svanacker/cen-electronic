#ifndef MOTION_PARAMETER_TYPE_H
#define MOTION_PARAMETER_TYPE_H

#define MOTION_PARAMETERS_COUNT            4

enum MotionParameterType {

    /**
     * The robot goes forward or backward.
     */
    MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD = 0,

    /**
     * The robot do a rotation.
     */
    MOTION_PARAMETER_TYPE_ROTATION = 1,

    /**
     * The robot do a rotation with One Wheel
     */
    MOTION_PARAMETER_TYPE_ROTATION_ONE_WHEEL = 2,

    /**
     * The robot must maintain a position.
     */
    MOTION_PARAMETER_TYPE_MAINTAIN_POSITION = 3
};

#endif
