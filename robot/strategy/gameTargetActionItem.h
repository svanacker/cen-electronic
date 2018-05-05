#ifndef GAME_TARGET_ACTION_ITEM_H
#define GAME_TARGET_ACTION_ITEM_H

// forward declaration
struct GameTargetActionItem;
typedef struct GameTargetActionItem GameTargetActionItem;

// #include "gameStrategyContext.h"

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
struct GameTargetActionItem {
    /** Name of the action Item */
    char* name;
    /** Function which will be called. */
    GameTargetActionFunction* actionItemFunction;
};

/**
 * Clear the game target action item.
 */
void clearGameTargetActionItem(GameTargetActionItem* targetActionItem);

/**
 * Print the detail of the target action item.
 */
void printGameTargetActionItem(OutputStream* outputStream, GameTargetActionItem* targetActionItem);


#endif

