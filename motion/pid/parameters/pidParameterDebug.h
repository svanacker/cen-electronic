#ifndef PID_PARAMETER_DEBUG_H
#define PID_PARAMETER_DEBUG_H

#include <stdbool.h>

#include "../../../common/io/outputStream.h"

#include "pidParameter.h"
#include "../pidMotion.h"

/**
 * Print all parameters as a table.
 * @param outputStream the stream where we debug 
 * @param pidMotion the pointer to the main structure for PID
 */
void printAllPidParametersTable(OutputStream* outputStream, PidMotion* pidMotion);

#endif