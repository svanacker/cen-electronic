#ifndef GAME_STRATEGY_ITEM_LIST_H
#define GAME_STRATEGY_ITEM_LIST_H

#include "gameStrategyItem.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/** The max limit of strategy item count. */
#define MAX_STRATEGY_ITEM 		7

/**
 * Tre struct defining a list of strategies.
 */
typedef struct GameStrategyItemList {
    /** An array of pointer on strategy item. */
    GameStrategyItem* items[MAX_STRATEGY_ITEM];
    /** the size of the list. */
    unsigned char size;
} GameStrategyItemList;


/**
 * Add a strategy item to the list.
 * @param strategyItem the strategy item to add to the list
 */
void addGameStrategyItem(GameStrategyItemList* gameStrategyItemList, GameStrategyItem* strategyItem);

/**
 * Get the strategy at index.
 */
GameStrategyItem* getStrategyItem(GameStrategyItemList* gameStrategyItemList, int index);

/**
 * Get the count of strategies.
 */
int getStrategyItemCount(GameStrategyItemList* gameStrategyItemList);

/**
 * Print the game strategy list, and for each the detail of strategy game
 */
void printGameStrategyItemList(OutputStream* outputStream, GameStrategyItemList* gameStrategyItemList);

#endif

