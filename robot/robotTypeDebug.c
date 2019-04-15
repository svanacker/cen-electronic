#include "robotTypeDebug.h"

#include "../robot/robotType.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

unsigned int printRobotType(OutputStream* outputStream, enum RobotType robotType) {
	if (robotType == ROBOT_TYPE_BIG) {
		return appendString(outputStream, "BIG");
	}
	else if (robotType == ROBOT_TYPE_SMALL) {
		return appendString(outputStream, "SMALL");
	}
    else if (robotType == ROBOT_TYPE_UNKNOWN) {
        return appendString(outputStream, "UNKNOWN");
	}
    else {
        return appendString(outputStream, "???");
	}
}

unsigned int addRobotTypeTableData(OutputStream* outputStream, enum RobotType robotType, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = printRobotType(outputStream, robotType);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}
