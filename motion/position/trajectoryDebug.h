#ifndef TRAJECTORY_DEBUG_H
#define TRAJECTORY_DEBUG_H

#include "../../common/io/outputStream.h"

/**
 * Print the position of the robot.
 */
void printDebugPosition(OutputStream* outputStream);

/**
* Print the value used to analyze coders value
*/
void printDebugCoderHistory(OutputStream* outputStream);

#endif
