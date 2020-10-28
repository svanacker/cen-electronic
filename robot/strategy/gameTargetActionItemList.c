#include <stdlib.h>

#include "gameTargetActionItemList.h"
#include "gameTargetActionItem.h"

#include "../../common/error/error.h"
#include "../../common/log/logger.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "gameTargetAction.h"

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
        GameTargetActionIsEndedFunction* actionItemIsEndedFunction,
        char* name
        ) {
    unsigned char size = targetActionItemList->size;
    if (size < MAX_TARGET_ACTION_ITEM) {
        targetActionItem->actionItemFunction = actionItemFunction;
        targetActionItem->actionItemIsEndedFunction = actionItemIsEndedFunction;
        targetActionItem->name = name;
        targetActionItem->status = ACTION_ITEM_STATUS_TODO;
        targetActionItem->enabled = true;
        targetActionItemList->items[size] = targetActionItem;
        targetActionItemList->size++;
    } else {
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

enum ActionStatus executeTargetActionItemList(GameTargetActionItemList* actionItemList, int* context) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "executeTargetActionItemList");
    }
    unsigned int doingCount = 0;
    unsigned int actionItemIndex;
    // Loop on all action Items to do
    for (actionItemIndex = 0; actionItemIndex < actionItemList->size; actionItemIndex++) {
        GameTargetActionItem* actionItem = getGameTargetActionItem(actionItemList, actionItemIndex);
        
        // Handling action item which are doing
        if (actionItem->status == ACTION_ITEM_STATUS_DOING) {
            // If the actionItem is not finished
            if (!actionItem->actionItemIsEndedFunction(context)) {
                doingCount++;
                // We must not go to the next action
                break;
            }
            else {
                // the action item is finished
                actionItem->status = ACTION_ITEM_STATUS_DONE;
                continue;
            }
        }

        // Do only action not done and enabled
        if (actionItem->status != ACTION_ITEM_STATUS_TODO || !(actionItem->enabled)) {
            continue;
        }

        // Do the action item, and track if there will be an error
        doGameTargetActionItem(actionItem, context);
        enum ActionItemStatus status = actionItem->status;
        if (status == ACTION_ITEM_STATUS_DISABLED) {
            continue;
        }
        if (status == ACTION_ITEM_STATUS_DOING) {
            doingCount++;
            // Must not go to the next Action Item
            break;
        }
        if (status == ACTION_ITEM_STATUS_ERROR) {
            // If one item is in error, we consider that the whole action is in error
            return ACTION_STATUS_ERROR;
        }
    }
    if (doingCount > 0) {
        return ACTION_STATUS_DOING;    
    }
    return ACTION_STATUS_DONE;
}

void doGameTargetActionItem(GameTargetActionItem* gameTargetActionItem, int* context) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "doGameTargetActionItem");
    }
    if (gameTargetActionItem->actionItemFunction == NULL) {
        writeError(TOO_MUCH_TARGET_ACTION_ITEM_FUNCTION_NULL);
        return;
    }
    if (!gameTargetActionItem->enabled) {
        gameTargetActionItem->status = ACTION_ITEM_STATUS_DISABLED;
    }
    GameTargetActionFunction* doFunction = gameTargetActionItem->actionItemFunction;


    bool succeed = doFunction(context);
    if (succeed) {
        // If there is no isEndedFunction, it means that the action is instantenously done
        if (gameTargetActionItem->actionItemIsEndedFunction == NULL) {
            gameTargetActionItem->status = ACTION_ITEM_STATUS_DONE;
        }
        else {
            // We mark that the action item is doing
            gameTargetActionItem->status = ACTION_ITEM_STATUS_DOING;
        }
    } else {
        gameTargetActionItem->status = ACTION_ITEM_STATUS_ERROR;
    }
    if (isLoggerTraceEnabled()) {
        appendStringAndBoolLN(getTraceOutputStreamLogger(), "doGameTargetActionItem:result=", succeed);
    }
}