#include "robotDebug.h"

#include "../robot/config/robotConfig.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

void printRobotType(OutputStream* outputStream, enum RobotType robotType) {
	if (robotType == ROBOT_TYPE_BIG) {
		appendString(outputStream, "BIG");
	}
	else if (robotType == ROBOT_TYPE_SMALL) {
		appendString(outputStream, "SMALL");
	}
    else {
        appendString(outputStream, "???");
	}
}