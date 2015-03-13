#ifndef PID_MOTION_DEFINITION_H
#define PID_MOTION_DEFINITION_H

#include "motionInstruction.h"
#include "../extended/bspline.h"

/**
 * Define the function used to compute Errors.
 */
typedef void ComputeUFunction();

/**
 * Definition of motion. There can be more than one PidMotionDefinition, but only one active
 * at a time.
 */
typedef struct PidMotionDefinition {
    // Alpha / Theta
    MotionInstruction inst[INSTRUCTION_COUNT];
    // When using BSPline
    BSplineCurve curve;
    /** The method which will compute the errors (by using coders or absolute positions) .*/
    ComputeUFunction* computeU;
} PidMotionDefinition;

#endif