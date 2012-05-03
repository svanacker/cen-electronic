#ifndef GAME_TARGET_ACTION_ITEM_LIST_H
#define GAME_TARGET_ACTION_ITEM_LIST_H

#include "gameTargetActionItem.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

/** The max limit of action item count. */
#define MAX_TARGET_ACTION_ITEM 		5

/**
 * Encapsulates the target action.
 */
typedef struct GameTargetActionItemList {
    /** An array of pointer on target action items. */
    GameTargetActionItem* items[MAX_TARGET_ACTION_ITEM];
    /** the size of the list. */
    unsigned char size;
} GameTargetActionItemList;

/**
 * Print the detail of the all target action items.
 */
void printGameTargetActionItemList(OutputStream* outputStream, GameTargetActionItemList* targetActionItemList);


#endif

