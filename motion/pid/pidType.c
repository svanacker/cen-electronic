#include "pidType.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

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

void appendPidTypeAsString(enum PidType pidType, OutputStream* outputStream) {
    if (pidType == PID_TYPE_GO_INDEX) {
        appendString(outputStream, "GO");
    }
    else if (pidType == PID_TYPE_ROTATE_INDEX) {
        appendString(outputStream, "ROTATE");
    }
    else if (pidType == PID_TYPE_MAINTAIN_POSITION_INDEX) {
        appendString(outputStream, "MAINTAIN");
    }
    else if (pidType == PID_TYPE_ADJUST_DIRECTION) {
        appendString(outputStream, "ADJUST_DIR");
    }
    else if (pidType == PID_TYPE_FINAL_APPROACH_INDEX) {
        appendString(outputStream, "FINAL_APPROACH");
    }
    else {
        append(outputStream, '?');
    }
}