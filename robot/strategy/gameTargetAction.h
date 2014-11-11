#ifndef GAME_TARGET_ACTION_H
#define GAME_TARGET_ACTION_H

// #include "gameTarget.h"
#include "gameTargetActionItemList.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../navigation/location.h"

/**
 * Encapsulates the target action.
 */
typedef struct GameTargetAction {
    // Returns the first point which is needed to do the target Action
    Location* startLocation;
    // Returns the location of the target Action.
    Location* endLocation;
    // Time to achieve (in millisecond)
    int timeToAchieve;
    // Reference to GameTargetActionListItem, can be NULL
    GameTargetActionItemList* actionItemList;
    /** Path (can be NULL) used to check if the target Action Item is available. */
    PathDataFunction* pathDataFunction;
} GameTargetAction;

/**
 * Clear the targetAction and the items if any.
 */
void clearTargetAction(GameTargetAction* targetAction);

/**
 * Print the detail of the target action.
 */
void printGameTargetAction(OutputStream* outputStream, GameTargetAction* targetAction, bool includeItems);


#endif

