#ifndef MOTION_INSTRUCTION_DEBUG_H
#define MOTION_INSTRUCTION_DEBUG_H

#include "motionInstruction.h"

#include "../../common/io/outputStream.h"

/**
* Print a simulation of trajectory to an outputStream.
 *
*/
void printMotionInstructionTableTrajectory(OutputStream* outputStream, MotionInstruction* instruction);

#endif

