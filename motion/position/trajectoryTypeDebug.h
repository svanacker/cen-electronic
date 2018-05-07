#ifndef TRAJECTORY_TYPE_DEBUG_H
#define TRAJECTORY_TYPE_DEBUG_H

#include "trajectoryType.h"

#include "../../common/io/outputStream.h"

/**
 * Append the trajectory Type as A String representation.
 * @param outputStream
 * @param trajectoryType
 * @return 
 */
unsigned int appendTrajectoryTypeAsString(OutputStream* outputStream, enum TrajectoryType trajectoryType);

/**
 * For Table Printing
 * @param outputStream
 * @param trajectoryType
 * @param columnSize
 * @return 
 */
unsigned int addTrajectoryTypeTableData(OutputStream* outputStream,  enum TrajectoryType trajectoryType, int columnSize);

#endif
