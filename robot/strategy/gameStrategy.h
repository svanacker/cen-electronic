#ifndef GAME_STRATEGY_H
#define GAME_STRATEGY_H

#include "gameStrategy.h"
#include "gameStrategyItem.h"

#include "../../common/io/outputStream.h"

#define MAX_STRATEGY_ITEM 		7

/**
 * Encapsulates the strategy.
 */
typedef struct GameStrategy {
	/** Name of the strategy. */
	char* name;
	/** Elements of strategy. */
	GameStrategyItem* items[MAX_STRATEGY_ITEM];
    /** the size of the list. */
    unsigned char size;
} GameStrategy;

/**
 * Add a strategy item to the list.
 * @param strategyItem the strategy item to add to the list
 */
void addGameStrategyItem(GameStrategy* gameStrategy, GameStrategyItem* strategyItem);

/**
 * Get the strategy at index.
 */
GameStrategyItem* getStrategyItem(GameStrategy* gameStrategy, int index);

/**
 * Get the count of strategies items.
 */
int getStrategyItemCount(GameStrategy* gameStrategy);

/**
 * Print the detail of each strategy.
 */
void printGameStrategy(OutputStream* outputStream, GameStrategy* strategy);

#endif

