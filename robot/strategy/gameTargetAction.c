#include <stdlib.h>

#include "gameTargetAction.h"
#include "gameTargetActionItemList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void clearTargetAction(GameTargetAction* targetAction) {
    targetAction->startLocation = NULL;
    targetAction->endLocation = NULL;
    targetAction->timeToAchieve = 0.0f;
    targetAction->pathData = NULL;
    if (targetAction->actionItemList != NULL) {
        clearTargetActionItemList(targetAction->actionItemList);
    }
}

void initGameTargetAction(GameTargetAction* targetAction,
    Location* startLocation,
    Location* endLocation,
    float timeToAchieve,
    GameTargetActionItemList* actionItemList,
    PathData* pathData) {
    targetAction->startLocation = startLocation;
    targetAction->endLocation = endLocation;
    targetAction->timeToAchieve = timeToAchieve;
    targetAction->actionItemList = actionItemList;
    targetAction->pathData = pathData;
}

bool doGameTargetAction(GameTargetAction* targetAction, int* context) {
    GameTargetActionItemList* itemList = targetAction->actionItemList;
    unsigned int actionItemSize = itemList->size;
    unsigned char i;
    for (i = 0; i < actionItemSize; i++) {
        GameTargetActionItem* actionItem = getGameTargetActionItem(itemList, i);
        // Launch the action Item
        if (!doGameTargetActionItem(actionItem, context)) {
            // If there is a problem, we do not do further action
            return false;
        }
    }
    return true;
}