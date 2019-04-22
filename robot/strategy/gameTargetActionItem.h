#ifndef GAME_TARGET_ACTION_ITEM_H
#define GAME_TARGET_ACTION_ITEM_H

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../navigation/path.h"

/**
* Define the function which must be called.
*/
typedef bool GameTargetActionFunction(int* context);

/**
 * Define when the action must be done (before the move or when reaching 
 * the target).
 */
enum ActionItemPhasis {
    // This action must be done before reaching the target
    ACTION_ITEM_PHASIS_START_LOCATION = 1,
    // The action must be done when the target is reached
    ACTION_ITEM_PHASIS_END_LOCATION = 2,
};

/**
 * Encapsulates the target action item.
 */
typedef struct GameTargetActionItem {
    /** Name of the action Item */
    char* name;
    /** The time To Achieve this action in seconds. */
    // float timeToAchieve;
    /** The phasis for which the action must be done. */
    enum ActionItemPhasis phasis;
    /** Function which will be called. */
    GameTargetActionFunction* actionItemFunction;
} GameTargetActionItem;

/**
 * Clear the game target action item.
 */
void clearGameTargetActionItem(GameTargetActionItem* targetActionItem);

/**
 * Print the detail of the target action item.
 */
void printGameTargetActionItem(OutputStream* outputStream, GameTargetActionItem* targetActionItem);


#endif

