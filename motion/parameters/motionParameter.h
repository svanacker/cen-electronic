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
MotionParameter* getMotionParameters(enum MotionParameterType motionParameterType);

/**
 * Print a table with the list of motion Parameter.
 */
void printMotionParameterList(OutputStream* outputStream);

#endif
