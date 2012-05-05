#ifndef GAME_TARGET_ACTION_ITEM_H
#define GAME_TARGET_ACTION_ITEM_H

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

/**
 * Define the function which must be called.
 */
typedef void GameTargetActionFunction(OutputStream* outputStream);

/**
 * Encapsulates the target action item.
 */
typedef struct GameTargetActionItem {
	char* name;
	/** Function which will be called. */
	GameTargetActionFunction* actionItem;
} GameTargetActionItem;

/**
 * Print the detail of the target action item.
 */
void printGameTargetActionItem(OutputStream* outputStream, GameTargetActionItem* targetActionItem);


#endif

