#ifndef GAME_STRATEGY_ITEM_H
#define GAME_STRATEGY_ITEM_H

#include "gameStrategy.h"
#include "gameTarget.h"

#include "factor/gainFactor.h"

#include "../../common/io/outputStream.h"

/**
 * Encapsulates the strategy item.
 */
typedef struct GameStrategyItem {
	/** The target to reach. */
	GameTarget* gameTarget;
	/** The gain associated to the function. */
	// getGainFunction* gainFunction;
} GameStrategyItem;

/**
 * Print the detail of each strategy.
 */
void printGameStrategyItem(OutputStream* outputStream, GameStrategyItem* strategyItem);

#endif

