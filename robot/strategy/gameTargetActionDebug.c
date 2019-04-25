#include "gameTargetActionDebug.h"
#include "gameTargetAction.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// ActionType

unsigned int appendActionTypeAsString(OutputStream* outputStream, enum ActionType actionType) {
    if (actionType == ACTION_TYPE_UNDEFINED) {
        return appendString(outputStream, "UNDEFINED");
    }
    else if (actionType == ACTION_TYPE_MOVE) {
        return appendString(outputStream, "MOVE");
    }
    else if (actionType == ACTION_TYPE_PREPARE) {
        return appendString(outputStream, "PREP");
    }
    else if (actionType == ACTION_TYPE_HANDLE) {
        return appendString(outputStream, "HANDLE");
    }
    else if (actionType == ACTION_TYPE_DROP) {
        return appendString(outputStream, "DROP");
    }
    else {
        return appendString(outputStream, "???");
    }
}

unsigned int appendActionTypeTableData(OutputStream* outputStream, enum ActionType actionType, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendActionTypeAsString(outputStream, actionType);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}


// ActionStatus

unsigned int appendActionStatusAsString(OutputStream* outputStream, enum ActionStatus actionStatus) {
    if (actionStatus == ACTION_STATUS_UNDEFINED) {
        return appendString(outputStream, "UNDEFINED");
    }
    else if (actionStatus == ACTION_STATUS_TODO) {
        return appendString(outputStream, "TODO");
    }
    else if (actionStatus == ACTION_STATUS_DOING) {
        return appendString(outputStream, "DOING");
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
