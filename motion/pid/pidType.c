#include "pidType.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

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