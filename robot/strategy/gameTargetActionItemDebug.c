#include "gameTargetActionItemDebug.h"
#include "gameTargetActionItem.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// ActionItemStatus

unsigned int appendActionItemStatusAsString(OutputStream* outputStream, enum ActionItemStatus actionItemStatus) {
    if (actionItemStatus == ACTION_ITEM_STATUS_FREE) {
        return appendString(outputStream, "FREE");
    }
    else if (actionItemStatus == ACTION_ITEM_STATUS_DONE) {
        return appendString(outputStream, "DONE");
    }
    else {
        return appendString(outputStream, "???");
    }
}

unsigned int appendActionItemStatusTableData(OutputStream* outputStream, enum ActionItemStatus actionItemStatus, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendActionItemStatusAsString(outputStream, actionItemStatus);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}


// ActionItemPhasis

unsigned int appendActionItemPhasisAsString(OutputStream* outputStream, enum ActionItemPhasis actionItemPhasis) {
    if (actionItemPhasis == ACTION_ITEM_PHASIS_START_LOCATION) {
        return appendString(outputStream, "START");
    }
    else if (actionItemPhasis == ACTION_ITEM_PHASIS_END_LOCATION) {
        return appendString(outputStream, "END");
    }
    else {
        return appendString(outputStream, "???");
    }
}

unsigned int appendActionItemPhasisTableData(OutputStream* outputStream, enum ActionItemPhasis actionItemPhasis, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendActionItemPhasisAsString(outputStream, actionItemPhasis);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}
