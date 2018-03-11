#ifndef PID_COMPUTATION_INSTRUCTION_VALUES_DEBUG_H
#define PID_COMPUTATION_INSTRUCTION_VALUES_DEBUG_H

#include "pidMotion.h"

#include "../../common/io/outputStream.h"

/**
 * Print the list of debug data as table with all variables.
 */
void printPidDataDebugTable(OutputStream* outputStream, PidMotion* pidMotion);

#endif
