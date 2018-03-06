#ifndef MOTION_INSTRUCTION_DEBUG_H
#define MOTION_INSTRUCTION_DEBUG_H

#include "motionInstruction.h"
#include "instructionType.h"

#include "../../common/io/outputStream.h"

/**
* Print a simulation of trajectory to an outputStream.
* @param outputStream where we print the table
* @param instruction the motion instruction for which we would like to have each position / normal Speed ...
* @param pidInterval, must be >= 1.0f. It enables to avoid to see too much lines, but a line only each xx pidTime
*/
void printMotionInstructionTableTrajectory(OutputStream* outputStream, enum InstructionType instructionType, MotionInstruction* instruction, float pidInterval);

#endif

