#include <stdlib.h>

#include "gameTargetAction.h"
#include "gameTargetActionItemList.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void clearTargetAction(GameTargetAction* targetAction) {
    targetAction->startLocation = NULL;
    targetAction->endLocation = NULL;
    targetAction->timeToAchieve = 0.0f;
    targetAction->status = ACTION_STATUS_TODO;
    targetAction->type = ACTION_TYPE_UNDEFINED;
    if (targetAction->actionItemList != NULL) {
        clearTargetActionItemList(targetAction->actionItemList);
    }
}

void initGameTargetAction(GameTargetAction* targetAction,
        Location* startLocation,
        Location* endLocation,
        enum ActionType actionType,
        float timeToAchieve,
        unsigned int priority,
        GameTargetActionItemList* actionItemList) {
    targetAction->startLocation = startLocation;
    targetAction->endLocation = endLocation;
    targetAction->status = ACTION_STATUS_TODO;
    targetAction->type = actionType;
    targetAction->timeToAchieve = timeToAchieve;
    targetAction->priority = priority;
    targetAction->actionItemList = actionItemList;
}

bool targetActionNeedsMove(GameTargetAction* targetAction) {
    if (targetAction == NULL) {
        return false;
    }
    return targetAction->startLocation != targetAction->endLocation;
}

void doGameTargetAction(GameTargetAction* targetAction, int* context) {
    GameTargetActionItemList* itemList = targetAction->actionItemList;
    unsigned int actionItemSize = itemList->size;
    unsigned char i;
    for (i = 0; i < actionItemSize; i++) {
        GameTargetActionItem* actionItem = getGameTargetActionItem(itemList, i);
        // Launch the action Item
        doGameTargetActionItem(actionItem, context);
    }
}