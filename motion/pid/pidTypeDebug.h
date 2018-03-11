#ifndef PID_TYPE_DEBUG_H
#define PID_TYPE_DEBUG_H

#include <stdbool.h>

#include "pidType.h"

#include "../../common/io/outputStream.h"

/**
 * Append the type of the Pid as String into the outputStream.
 */
unsigned int appendPidTypeAsString(OutputStream* outputStream, enum PidType pidType);

/**
 * Append the pid Type in a table column data.
 */
unsigned int addPidTypeTableData(OutputStream* outputStream, enum PidType pidType, int columnSize);

#endif
