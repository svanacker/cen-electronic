#ifndef MOTION_PARAMETER_H
#define MOTION_PARAMETER_H

#include "motionParameterType.h"

// We don't store any digit, because, the unit is mm / sec
#define MOTION_PARAMETERS_SPEED_DIGIT            0

// We store 1 digit because the unit is mm / sec^2
#define MOTION_PARAMETERS_ACCELERATION_DIGIT     0

/**
 * Structure defining default Motion Parameters.
 */
typedef struct {
    /** The default acceleration. */
    float a;
    /** The default speed. */
    float speed;
} MotionParameter;

/**
 * Returns Parameters for Motion.
 */
MotionParameter* getMotionParameters(enum MotionParameterType motionParameterType);

#endif
