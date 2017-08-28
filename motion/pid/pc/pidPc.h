#ifndef PID_PC_H
#define PID_PC_H

#include "../../../motion/pid/pidMotion.h"

/**
 * Simulate if we are in a PC mode the move of the robot.
 */
void simulateCurrentPositionReachIfNeeded(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif

