#ifndef SIMPLE_PID_COMPUTER_H
#define SIMPLE_PID_COMPUTER_H

#include "../motionInstruction.h"
#include "../pidMotionDefinition.h"


/**
 * Simple implementation of motion (go, back, rotation)
 * @see also bSplinePidCompute
 */
void simpleMotionUCompute(PidMotionDefinition* motionDefinition);

#endif

