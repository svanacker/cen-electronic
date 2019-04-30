#ifndef GAME_TARGET_ACTION_LIST_H
#define GAME_TARGET_ACTION_LIST_H

#include <stdbool.h>

#include "gameTargetAction.h"
#include "gameTargetActionItemList.h"

#include "../../navigation/locationList.h"
#include "../../navigation/path.h"

/** The max limit of target action count. */
#define MAX_TARGET_ACTION         5

/**
 * Tre struct defining a list of strategies.
 */
typedef struct GameTargetActionList {
    /** An array of pointer on actions. */
    GameTargetAction* actions[MAX_TARGET_ACTION];
    /** the size of the list. */
    unsigned int size;
} GameTargetActionList;

/**
 * Clear the target Action and the corresponding items.
 */
void clearTargetActionList(GameTargetActionList* targetActionList);

/**
 * Add an action to the target.
 * @param targetAction the target to add to the list
 */
void addTargetMoveAction(GameTargetActionList* targetActionList,
    GameTargetAction* targetAction,
    Location* startLocation,
    Location* endLocation,
    float timeToAchieve);

void addTargetPrepareAction(GameTargetActionList* targetActionList,
    GameTargetAction* targetAction,
    Location* location,
    float timeToAchieve,
    GameTargetActionItemList* actionItemList);

void addTargetHandlingAction(GameTargetActionList* targetActionList,
    GameTargetAction* targetAction,
    Location* location,
    float timeToAchieve,
    GameTargetActionItemList* actionItemList);

void addTargetDropAction(GameTargetActionList* targetActionList,
    GameTargetAction* targetAction,
    Location* location,
    float timeToAchieve,
    GameTargetActionItemList* actionItemList);


/**
 * Get the target action at index.
 */
GameTargetAction* getGameTargetAction(GameTargetActionList* list, int index);

/**
 * Returns the first location (start) location to reach.
 */
bool isAnyActionStartedOrDone(GameTargetActionList* list);

/**
 * Return the next Game Target Action to do if any.
 */
GameTargetAction* getNextGameTargetActionTodo(GameTargetActionList* targetActionList, Location* location);

/**
 * Get the count of target action.
 */
int getGameTargetActionCount(GameTargetActionList* list);

#endif
