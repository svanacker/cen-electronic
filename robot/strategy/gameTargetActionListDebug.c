#include "gameTargetActionListDebug.h"
#include "gameTargetAction.h"
#include "gameTargetActionItemList.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../navigation/path.h"

void printGameTargetActionList(OutputStream* outputStream, GameTargetActionList* targetActionList) {
    int i;
    int size = targetActionList->size;
    for (i = 0; i < size; i++) {
        GameTargetAction* targetAction = targetActionList->actions[i];
        printGameTargetAction(outputStream, targetAction, true);
    }
}
