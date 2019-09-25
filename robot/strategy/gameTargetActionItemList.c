#include <stdlib.h>

#include "gameTargetActionItemList.h"
#include "gameTargetActionItem.h"

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

// LIST MANAGEMENT

void clearTargetActionItemList(GameTargetActionItemList* targetActionItemList) {
    int i;
    int size = targetActionItemList->size;
    for (i = 0; i < size; i++) {
        GameTargetActionItem* targetActionItem = targetActionItemList->items[i];
        clearGameTargetActionItem(targetActionItem);
    }    
    targetActionItemList->size = 0;
}


void addTargetActionItem(GameTargetActionItemList* targetActionItemList,
                     GameTargetActionItem* targetActionItem,
                     GameTargetActionFunction* actionItemFunction,
                     char* name
//                      float timeToAchieve,
) {
    unsigned char size = targetActionItemList->size;
    if (size < MAX_TARGET_ACTION_ITEM) {
        targetActionItem->actionItemFunction = actionItemFunction;
        targetActionItem->name = name;
//      targetActionItem->timeToAchieve = timeToAchieve;
        targetActionItem->status = ACTION_ITEM_STATUS_TODO;
        targetActionItem->enabled = true;
        targetActionItemList->items[size] = targetActionItem;
        targetActionItemList->size++;
    }
    else {
        writeError(TOO_MUCH_TARGET_ACTION_ITEM);
    }
}

GameTargetActionItem* getGameTargetActionItem(GameTargetActionItemList* targetActionItemList, int index) {
    return targetActionItemList->items[index];
}

unsigned int getGameTargetActionItemTodoCount(GameTargetActionItemList* targetActionItemList) {
    unsigned int result = 0;
    int i;
    int size = targetActionItemList->size;
    for (i = 0; i < size; i++) {
        GameTargetActionItem* targetActionItem = targetActionItemList->items[i];
        if (targetActionItem->enabled && targetActionItem->status == ACTION_ITEM_STATUS_TODO) {
            result++;
        }
    }
    return result;
}

int getGameTargetActionItemCount(GameTargetActionItemList* targetActionItemList) {
    return targetActionItemList->size;
}

// ACTIONS

bool executeTargetActionItemList(GameTargetActionItemList* actionItemList, int* context) {
    bool result = true;
    unsigned int actionItemIndex;
    // Loop on all action Items to do
    for (actionItemIndex = 0; actionItemIndex < actionItemList->size; actionItemIndex++) {
        GameTargetActionItem* actionItem = getGameTargetActionItem(actionItemList, actionItemIndex);
        // Do only action not done and enabled
        if (actionItem->status != ACTION_ITEM_STATUS_TODO || !(actionItem->enabled)) {
            continue;
        }

        // Do the action item, and track if there will be an error
        if (!doGameTargetActionItem(actionItem, context)) {
            result = false;
        }
    }
    return result;
}

bool doGameTargetActionItem(GameTargetActionItem* gameTargetActionItem, int* context) {
    if (gameTargetActionItem->actionItemFunction == NULL) {
        writeError(TOO_MUCH_TARGET_ACTION_ITEM_FUNCTION_NULL);
        return false;
    }
    if (!gameTargetActionItem->enabled) {
        gameTargetActionItem->status = ACTION_ITEM_STATUS_DISABLED;

        return true;
    }
    GameTargetActionFunction* doFunction = gameTargetActionItem->actionItemFunction;


    bool succeed = doFunction(context);
    if (succeed) {
        gameTargetActionItem->status = ACTION_ITEM_STATUS_DONE;
    }
    else {
        gameTargetActionItem->status = ACTION_ITEM_STATUS_ERROR;
    }
    return succeed;
}