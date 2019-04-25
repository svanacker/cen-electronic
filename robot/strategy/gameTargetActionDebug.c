#include "gameTargetActionDebug.h"
#include "gameTargetAction.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// ActionItemStatus

unsigned int appendActionStatusAsString(OutputStream* outputStream, enum ActionStatus actionStatus) {
    if (actionStatus == ACTION_STATUS_TODO) {
        return appendString(outputStream, "TODO");
    }
    else if (actionStatus == ACTION_STATUS_DONE) {
        return appendString(outputStream, "DONE");
    }
    else if (actionStatus == ACTION_STATUS_ERROR) {
        return appendString(outputStream, "ERROR");
    }
    else {
        return appendString(outputStream, "???");
    }
}

unsigned int appendActionStatusTableData(OutputStream* outputStream, enum ActionStatus actionStatus, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendActionStatusAsString(outputStream, actionStatus);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}
