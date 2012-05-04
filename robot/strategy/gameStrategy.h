#ifndef GAME_STRATEGY_H
#define GAME_STRATEGY_H

#include "gameStrategy.h"
// #include "gameStrategyItemList.h"

#include "../../common/io/outputStream.h"

/**
 * Encapsulates the strategy.
 */
typedef struct GameStrategy {
	/** Name of the strategy. */
	char* name;
	/** The list of small strategies which can be defined. */
	// GameStrategyItemList* items;
} GameStrategy;

/**
 * Print the detail of each strategy.
 */
void printGameStrategy(OutputStream* outputStream, GameStrategy* strategy);

#endif

