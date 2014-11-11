#ifndef GAME_TARGET_ACTION_ITEM_H
#define GAME_TARGET_ACTION_ITEM_H

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../navigation/path.h"


/**
 * Define the function which must be called.
 */
typedef void GameTargetActionFunction();

/**
 * Encapsulates the target action item.
 */
typedef struct GameTargetActionItem {
    char* name;
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

