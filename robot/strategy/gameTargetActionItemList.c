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
                     char* name,
//                      float timeToAchieve,
                     enum ActionItemPhasis phasis
) {
    unsigned char size = targetActionItemList->size;
    if (size < MAX_TARGET_ACTION_ITEM) {
        targetActionItem->actionItemFunction = actionItemFunction;
        targetActionItem->name = name;
//      targetActionItem->timeToAchieve = timeToAchieve;
        targetActionItem->phasis = phasis;
        targetActionItem->status = ACTION_ITEM_STATUS_TODO;
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

int getGameTargetActionItemCount(GameTargetActionItemList* targetActionItemList) {
    return targetActionItemList->size;
}

// ITERATOR

bool targetActionItemListHasNext(GameTargetActionItemList* targetActionItemList) {
    return (targetActionItemList->iteratorIndex < targetActionItemList->size);
}

GameTargetActionItem* targetActionItemListNext(GameTargetActionItemList* targetActionItemList) {
    if (targetActionItemList->iteratorIndex < targetActionItemList->size) {
        GameTargetActionItem* result = targetActionItemList->items[targetActionItemList->iteratorIndex];
        targetActionItemList->iteratorIndex++;
        return result;
    }
    return NULL;
}

void targetActionItemListResetIterator(GameTargetActionItemList* targetActionItemList) {
    targetActionItemList->iteratorIndex = 0;
}

// DOING

bool doGameTargetActionItem(GameTargetActionItem* gameTargetActionItem, int* context) {
    if (gameTargetActionItem->actionItemFunction == NULL) {
        writeError(TOO_MUCH_TARGET_ACTION_ITEM_FUNCTION_NULL);
        return false;
    }
    GameTargetActionFunction* doFunction = gameTargetActionItem->actionItemFunction;
    return doFunction(context);
}