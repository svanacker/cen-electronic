#ifndef MOTION_PARAMETER_H
#define MOTION_PARAMETER_H

#include "motionParameterType.h"

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
MotionParameter* getDefaultMotionParameters(enum MotionParameterType motionParameterType);

#endif
