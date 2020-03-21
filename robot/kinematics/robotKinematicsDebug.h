#ifndef ROBOT_KINEMATICS_DEBUG_H
#define ROBOT_KINEMATICS_DEBUG_H

#include "robotKinematics.h"
#include "../../common/io/outputStream.h"

/**
 * Output a table with all values.
 */
void printRobotKinematicsTable(OutputStream* outputStream, RobotKinematics* robotKinematics);

#endif
