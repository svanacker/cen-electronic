#ifndef PID_MOTION_DEFINITION_H
#define PID_MOTION_DEFINITION_H

#include "instructionType.h"
#include "motionInstruction.h"
#include "../extended/bspline.h"

// Forward declaration
typedef struct PidMotionDefinition PidMotionDefinition;

/**
 * Define the function used to compute Errors.
 */
typedef void ComputeUFunction(PidMotionDefinition* motionDefinition);


/**
 * Definition of motion. There can be more than one PidMotionDefinition, but only one active
 * at a time.
 */
struct PidMotionDefinition {
    // Alpha / Theta
    MotionInstruction inst[INSTRUCTION_COUNT];
    // When using BSPline
    BSplineCurve curve;
    /** The method which will compute the errors (by using coders or absolute positions) .*/
    ComputeUFunction* computeU;
};

#endif