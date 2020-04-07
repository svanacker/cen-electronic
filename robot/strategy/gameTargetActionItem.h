#ifndef GAME_TARGET_ACTION_ITEM_H
#define GAME_TARGET_ACTION_ITEM_H

#include <stdbool.h>

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../navigation/path.h"

/**
 * Define the function which must be called.
 * @return true if the function succeed, false if there is an error.
 */
typedef bool GameTargetActionFunction(int* context);

/**
* Define the callback function which must be called to know if the current action is finished.
*/
typedef bool GameTargetActionIsEndedFunction(int* context);

/**
 * Define if the action Item was done or not.
 */
enum ActionItemStatus {
    // The item action was not done
    ACTION_ITEM_STATUS_TODO = 1,
    // The item action is doing (we wait that the function isEnded is ok)
    ACTION_ITEM_STATUS_DOING = 2,
    // The item action was done
    ACTION_ITEM_STATUS_DONE = 3,
    // The item action is disabled,
    ACTION_ITEM_STATUS_DISABLED = 4,
    // The item action is in error,
    ACTION_ITEM_STATUS_ERROR = 5
};

/**
 * Encapsulates the target action item.
 */
typedef struct GameTargetActionItem {
    /** Name of the action Item */
    char* name;
    /** If the action is enabled or not */
    bool enabled;
    /** The statut if the action item was done or not. */
    enum ActionItemStatus status;
    /** Function which will be called. */
    GameTargetActionFunction* actionItemFunction;
    /** Function which will be called to know if the action is finished. */
    GameTargetActionIsEndedFunction* actionItemIsEndedFunction;
} GameTargetActionItem;

/**
 * Clear the game target action item.
 */
void clearGameTargetActionItem(GameTargetActionItem* targetActionItem);

#endif

