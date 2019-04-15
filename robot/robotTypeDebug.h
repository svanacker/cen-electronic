#ifndef ROBOT_TYPE_DEBUG_H
#define ROBOT_TYPE_DEBUG_H

#include "../robot/robotType.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

unsigned int printRobotType(OutputStream* outputStream, enum RobotType robotType);

unsigned int addRobotTypeTableData(OutputStream* outputStream, enum RobotType robotType, int columnSize);


#endif
