#include "pidTypeDebug.h"

#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

unsigned int appendPidTypeAsString(OutputStream* outputStream, enum PidType pidType) {
    if (pidType == PID_TYPE_NONE) {
        return appendString(outputStream, "NONE");
    } else if (pidType == PID_TYPE_GO_INDEX) {
        return appendString(outputStream, "GO");
    } else if (pidType == PID_TYPE_ROTATE_INDEX) {
        return appendString(outputStream, "ROTATE");
    } else if (pidType == PID_TYPE_FINAL_APPROACH_INDEX) {
        return appendString(outputStream, "FINAL");
    } else if (pidType == PID_TYPE_MAINTAIN_POSITION_INDEX) {
        return appendString(outputStream, "MAINTAIN");
    } else if (pidType == PID_TYPE_ADJUST) {
        return appendString(outputStream, "ADJUST");
    } else {
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
