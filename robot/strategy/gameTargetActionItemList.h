#ifndef GAME_TARGET_ACTION_ITEM_LIST_H
#define GAME_TARGET_ACTION_ITEM_LIST_H


#include "gameTargetActionItem.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../navigation/path.h"

/** The max limit of action item count. */
#define MAX_TARGET_ACTION_ITEM         5

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
 * Clear the target action item list, and all items.
 */
void clearTargetActionItemList(GameTargetActionItemList* targetActionItemList);

/**
 * Add an action item to the target.
 * @param targetActionItem the target item to add to the list
 */
void addTargetActionItem(GameTargetActionItemList* targetActionItemList,
                     GameTargetActionItem* targetActionItem,
                     GameTargetActionFunction* function,
                     char* name
//                    float timeToAchieve,
);

/**
 * Get the target action item at index.
 */
GameTargetActionItem* getGameTargetActionItem(GameTargetActionItemList* targetActionItemList, int index);

/**
 * Get the count of target action item.
 */
int getGameTargetActionItemCount(GameTargetActionItemList* list);

// DO ACTIONS

bool executeTargetActionItemList(GameTargetActionItemList* actionItemList, int* context);

/**
 * Call the real method by passing a context and the object to do
 */
bool doGameTargetActionItem(GameTargetActionItem* gameTargetActionItem, int* gameStrategyContext);


#endif

