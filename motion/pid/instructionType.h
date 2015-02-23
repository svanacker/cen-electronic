#ifndef INSTRUCTION_TYPE_H
#define INSTRUCTION_TYPE_H

// -> PID TO CONTROL

// Number of PID to control
#define INSTRUCTION_COUNT 2

enum InstructionType {
    // The index of theta & alpha instruction
    INSTRUCTION_THETA_INDEX = 0,
    INSTRUCTION_ALPHA_INDEX = 1
};

#endif
