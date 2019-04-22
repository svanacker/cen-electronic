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
 * Define if the action Item was done or not.
 */
enum ActionItemStatus {
    // The item action was not done
    ACTION_ITEM_STATUS_FREE = 1,
    // The item action was done
    ACTION_ITEM_STATUS_DONE = 2,
};

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
    /** The phasis for which the action must be done. */
    enum ActionItemPhasis phasis;
    /** The statut if the action item was done or not. */
    enum ActionItemStatus status;
    /** Function which will be called. */
    GameTargetActionFunction* actionItemFunction;
} GameTargetActionItem;

/**
 * Clear the game target action item.
 */
void clearGameTargetActionItem(GameTargetActionItem* targetActionItem);

#endif

