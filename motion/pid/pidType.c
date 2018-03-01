#include "pidType.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../motion/parameters/motionParameterType.h"

enum PidType getPidType(enum MotionParameterType motionParameterType) {
    if (motionParameterType == MOTION_PARAMETER_TYPE_FORWARD_OR_BACKWARD) {
        return PID_TYPE_GO_INDEX;
    } else if (motionParameterType == MOTION_PARAMETER_TYPE_ROTATION) {
        return PID_TYPE_ROTATE_INDEX;
    } else if (motionParameterType == MOTION_PARAMETER_TYPE_MAINTAIN_POSITION) {
        return PID_TYPE_MAINTAIN_POSITION_INDEX;
    }
    // Default value, must not enter here
    return PID_TYPE_GO_INDEX;
}

unsigned int appendPidTypeAsString(OutputStream* outputStream, enum PidType pidType) {
    if (pidType == PID_TYPE_UNDEFINED) {
        return appendString(outputStream, "UNDEFINED");
    }
    else if (pidType == PID_TYPE_GO_INDEX) {
        return appendString(outputStream, "GO");
    }
    else if (pidType == PID_TYPE_ROTATE_INDEX) {
		return appendString(outputStream, "ROTATE");
    }
    else if (pidType == PID_TYPE_MAINTAIN_POSITION_INDEX) {
		return appendString(outputStream, "MAINTAIN");
    }
    else if (pidType == PID_TYPE_ADJUST_DIRECTION) {
		return appendString(outputStream, "ADJUST_DIR");
    }
    else if (pidType == PID_TYPE_FINAL_APPROACH_INDEX) {
		return appendString(outputStream, "FINAL");
    }
    else {
        append(outputStream, '?');
		return 1;
    }
	return 0;
}

unsigned int addPidTypeTableData(OutputStream* outputStream, enum PidType pidType, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendPidTypeAsString(outputStream, pidType);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}