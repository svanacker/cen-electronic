#ifndef PID_DEBUG_H
#define PID_DEBUG_H

#include "pidMotion.h"

#include "../../common/io/outputStream.h"

/**
 * Print the list of motion instruction as a table with all instructions.
 */
void printMotionInstructionTable(OutputStream* outputStream, PidMotion* pidMotion);

/**
 * Print the list of debug data as table with all variables.
 */
void printPidDataDebugTable(OutputStream* outputStream, PidMotion* pidMotion);

#endif
