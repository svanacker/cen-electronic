#include "gameTargetActionList.h"
#include "gameTargetAction.h"
#include "gameTargetActionItemList.h"

#include <stdlib.h>

#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../navigation/path.h"

// BASIC LIST MANAGEMENT

void clearTargetActionList(GameTargetActionList* targetActionList) {
    int i;
    int size = targetActionList->size;
    for (i = 0; i < size; i++) {
        GameTargetAction* targetAction = targetActionList->actions[i];
        clearTargetAction(targetAction);
    }
    targetActionList->size = 0;
}

GameTargetAction* getGameTargetAction(GameTargetActionList* targetActionList, int index) {
    return targetActionList->actions[index];
}

int getGameTargetActionCount(GameTargetActionList* targetActionList) {
    return targetActionList->size;
}

// ADD ACTION CONVENIENT METHODS

/*
void addTargetMoveAction(GameTargetActionList* targetActionList,
    GameTargetAction* targetAction,
    Location* startLocation,
    Location* endLocation,
    float timeToAchieve) {
    unsigned char size = targetActionList->size;
    if (size < MAX_TARGET_ACTION) {
        initGameTargetAction(targetAction, startLocation, endLocation, ACTION_TYPE_MOVE, ACTION_PRIORITY_ timeToAchieve, NULL);
        targetActionList->actions[size] = targetAction;
        targetActionList->size++;
    }
    else {
        writeError(TOO_MUCH_TARGET_ACTION);
    }
}
 */

void addTargetPrepareAction(GameTargetActionList* targetActionList,
        GameTargetAction* targetAction,
        Location* location,
        float timeToAchieve,
        GameTargetActionItemList* actionItemList) {
    unsigned char size = targetActionList->size;
    if (size < MAX_TARGET_ACTION) {
        initGameTargetAction(targetAction, location, location, ACTION_TYPE_PREPARE, timeToAchieve, ACTION_PRIORITY_PREPARE_STANDARD, actionItemList);
        targetActionList->actions[size] = targetAction;
        targetActionList->size++;
    } else {
        writeError(TOO_MUCH_TARGET_ACTION);
    }
}

void addTargetTakeAction(GameTargetActionList* targetActionList,
        GameTargetAction* targetAction,
        Location* location,
        float timeToAchieve,
        GameTargetActionItemList* actionItemList) {
    unsigned char size = targetActionList->size;
    if (size < MAX_TARGET_ACTION) {
        initGameTargetAction(targetAction, location, location, ACTION_TYPE_TAKE, timeToAchieve, ACTION_PRIORITY_TAKE_STANDARD, actionItemList);
        targetActionList->actions[size] = targetAction;
        targetActionList->size++;
    } else {
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
        initGameTargetAction(targetAction, location, location, ACTION_TYPE_DROP, timeToAchieve, ACTION_PRIORITY_DROP_STANDARD, actionItemList);
        targetActionList->actions[size] = targetAction;
        targetActionList->size++;
    } else {
        writeError(TOO_MUCH_TARGET_ACTION);
    }
}

// FINDER

GameTargetAction* getNextGameTargetActionTodoByLocation(GameTargetActionList* targetActionList, Location* location) {
    int i;
    int size = targetActionList->size;
    for (i = 0; i < size; i++) {
        GameTargetAction* targetAction = targetActionList->actions[i];
        if (targetAction->status != ACTION_STATUS_TODO && targetAction->status != ACTION_STATUS_DOING) {
            continue;
        }
        // If the start Location is not defined (for Preparation for example, we could do it where we want !)
        if (targetAction->startLocation == NULL) {
            return targetAction;
        }
        // We try to do the action at the right location
        if (targetAction->startLocation == location) {
            return targetAction;
        }
    }
    return NULL;
}

GameTargetAction* getNextGameTargetActionTodoByPriority(GameTargetActionList* targetActionList) {
    int i;
    int size = targetActionList->size;
    GameTargetAction* result = NULL;
    for (i = 0; i < size; i++) {
        GameTargetAction* targetAction = targetActionList->actions[i];
        if (targetAction->status != ACTION_STATUS_TODO && targetAction->status != ACTION_STATUS_DOING) {
            continue;
        }
        // We try to do the action with the highest priority !
        if (result == NULL || targetAction->priority > result->priority) {
            result = targetAction;
        }
    }
    return result;
}
