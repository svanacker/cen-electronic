#include "gameTargetActionList.h"
#include "gameTargetAction.h"
#include "gameTargetActionItemList.h"

#include <stdlib.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../navigation/path.h"

void clearTargetActionList(GameTargetActionList* targetActionList) {
    int i;
    int size = targetActionList->size;
    for (i = 0; i < size; i++) {
        GameTargetAction* targetAction = targetActionList->actions[i];
        clearTargetAction(targetAction);
    }
    targetActionList->size = 0;
}

// Add Action to the list

void addTargetMoveAction(GameTargetActionList* targetActionList,
    GameTargetAction* targetAction,
    Location* startLocation,
    Location* endLocation,
    float timeToAchieve) {
    unsigned char size = targetActionList->size;
    if (size < MAX_TARGET_ACTION) {
        initGameTargetAction(targetAction, startLocation, endLocation, ACTION_TYPE_MOVE, timeToAchieve, NULL);
        targetActionList->actions[size] = targetAction;
        targetActionList->size++;
    }
    else {
        writeError(TOO_MUCH_TARGET_ACTION);
    }
}

void addTargetPrepareAction(GameTargetActionList* targetActionList,
                     GameTargetAction* targetAction,
                     Location* location,
                     float timeToAchieve,
                     GameTargetActionItemList* actionItemList) {
    unsigned char size = targetActionList->size;
    if (size < MAX_TARGET_ACTION) {
        initGameTargetAction(targetAction, location, location, ACTION_TYPE_PREPARE, timeToAchieve, actionItemList);
        targetActionList->actions[size] = targetAction;
        targetActionList->size++;
    }
    else {
        writeError(TOO_MUCH_TARGET_ACTION);
    }
}

void addTargetHandlingAction(GameTargetActionList* targetActionList,
    GameTargetAction* targetAction,
    Location* location,
    float timeToAchieve,
    GameTargetActionItemList* actionItemList) {
    unsigned char size = targetActionList->size;
    if (size < MAX_TARGET_ACTION) {
        initGameTargetAction(targetAction, location, location, ACTION_TYPE_HANDLE, timeToAchieve, actionItemList);
        targetActionList->actions[size] = targetAction;
        targetActionList->size++;
    }
    else {
        writeError(TOO_MUCH_TARGET_ACTION);
    }
}

void addTargetDropAction(GameTargetActionList* targetActionList,
    GameTargetAction* targetAction,
    Location* location,
    float timeToAchieve,
    GameTargetActionItemList* actionItemList) {
    unsigned char size = targetActionList->size;
    if (size < MAX_TARGET_ACTION) {
        initGameTargetAction(targetAction, location, location, ACTION_TYPE_DROP, timeToAchieve, actionItemList);
        targetActionList->actions[size] = targetAction;
        targetActionList->size++;
    }
    else {
        writeError(TOO_MUCH_TARGET_ACTION);
    }
}

/**
 * Returns the first location (start) location to reach.
 */
bool isAnyActionStartedOrDone(GameTargetActionList* list) {
    int i;
    int size = list->size;
    for (i = 0; i < size; i++) {
        GameTargetAction* targetAction = list->actions[i];
        if (targetAction->status == ACTION_STATUS_DOING || targetAction->status == ACTION_STATUS_DONE) {
            return true;
        }
    }
    return false;
}

GameTargetAction* getNextGameTargetActionTodo(GameTargetActionList* targetActionList, Location* location) {
    int i;
    int size = targetActionList->size;
    for (i = 0; i < size; i++) {
        GameTargetAction* targetAction = targetActionList->actions[i];
        if (targetAction->status == ACTION_STATUS_TODO && targetAction->startLocation == location) {
            return targetAction;
        }
    }
    return NULL;
}

GameTargetAction* getGameTargetAction(GameTargetActionList* targetActionList, int index) {
    return targetActionList->actions[index];
}

int getGameTargetActionCount(GameTargetActionList* targetActionList) {
    return targetActionList->size;
}
