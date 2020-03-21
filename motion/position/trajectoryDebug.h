#ifndef TRAJECTORY_DEBUG_H
#define TRAJECTORY_DEBUG_H

#include "trajectory.h"

#include "../../common/io/outputStream.h"

/**
 * Print the position of the robot.
 */
void printDebugPosition(OutputStream* outputStream);

/**
 * Print the value used to analyze coders value
 */
void printDebugCoderHistory(OutputStream* outputStream);

/**
 * Append the trajectory Type as A String representation.
 * @param outputStream
 * @param trajectoryType
 * @return 
 */
unsigned int appendTrajectoryTypeAsString(OutputStream* outputStream, enum TrajectoryType trajectoryType);

#endif
