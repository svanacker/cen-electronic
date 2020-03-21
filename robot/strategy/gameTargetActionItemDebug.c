#include "gameTargetActionItemDebug.h"
#include "gameTargetActionItem.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// ActionItemStatus

unsigned int appendActionItemStatusAsString(OutputStream* outputStream, enum ActionItemStatus actionItemStatus) {
    if (actionItemStatus == ACTION_ITEM_STATUS_TODO) {
        return appendString(outputStream, "TODO");
    } else if (actionItemStatus == ACTION_ITEM_STATUS_DONE) {
        return appendString(outputStream, "DONE");
    } else if (actionItemStatus == ACTION_ITEM_STATUS_DISABLED) {
        return appendString(outputStream, "DISABLED");
    } else if (actionItemStatus == ACTION_ITEM_STATUS_ERROR) {
        return appendString(outputStream, "ERROR");
    } else {
        return appendString(outputStream, "???");
    }
}

unsigned int appendActionItemStatusTableData(OutputStream* outputStream, enum ActionItemStatus actionItemStatus, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendActionItemStatusAsString(outputStream, actionItemStatus);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}
