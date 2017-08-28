#ifndef INSTRUCTION_TYPE_H
#define INSTRUCTION_TYPE_H

#include "../../common/io/outputStream.h"

// -> PID TO CONTROL

// Number of PID to control
#define INSTRUCTION_COUNT 2

/**
 * The index of theta & alpha instruction
 * @see alphaTheta.h
 */
enum InstructionType {
    // Theta => Length of the average of the wheels (left + right) / 2
    THETA = 0,
    // Alpha => Angle (difference between the left and right wheels) / 2
    ALPHA = 1
};

/**
 * Append the instruction Type As String.
 * @param outputStream the outputStream where we will write
 * @param instructionType the instructionType for which we want a String representation
 * @return the number of chars written
 */
unsigned int appendInstructionTypeAsString(OutputStream* outputStream, enum InstructionType instructionType);

#endif
