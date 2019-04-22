#include <stdlib.h>

#include "gameTargetActionItem.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void clearGameTargetActionItem(GameTargetActionItem* targetActionItem) {
    targetActionItem->name = NULL;
    targetActionItem->actionItemFunction = NULL;
}
