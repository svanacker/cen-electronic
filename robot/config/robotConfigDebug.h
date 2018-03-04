#ifndef ROBOT_CONFIG_DEBUG_H
#define ROBOT_CONFIG_DEBUG_H

#include "robotConfig.h"

#include "../../common/io/outputStream.h"

/**
* Print a table to debug the config.
* @param outputStream where we print the table
*/
void printRobotTableConfig(OutputStream* outputStream, RobotConfig* robotConfig);

#endif
