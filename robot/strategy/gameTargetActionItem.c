#include <stdlib.h>

#include "gameTargetActionItem.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void clearGameTargetActionItem(GameTargetActionItem* targetActionItem) {
    targetActionItem->name = NULL;
    targetActionItem->actionItemFunction = NULL;
}

void printGameTargetActionItem(OutputStream* outputStream, GameTargetActionItem* targetActionItem) {
    appendString(outputStream, "\t\t\tactionItem:");
    appendKeyAndName(outputStream, "name=", targetActionItem->name);
    println(outputStream);
}
