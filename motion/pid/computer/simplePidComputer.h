#ifndef SIMPLE_PID_COMPUTER_H
#define SIMPLE_PID_COMPUTER_H

#include "../pidMotion.h"
#include "../pidComputationValues.h"

/**
 * Simple implementation of motion (go, back, rotation)
 * @see also bSplinePidCompute
 */
void simpleMotionUCompute(
        //PidComputationValues* computationValues,
        PidMotion* pidMotion,
        PidMotionDefinition* motionDefinition);

#endif

