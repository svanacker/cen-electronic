#ifndef GAME_STRATEGY_H
#define GAME_STRATEGY_H

#include "gameStrategy.h"

#include "../../common/io/outputStream.h"

/**
 * Encapsulates the strategy.
 */
typedef struct GameStrategy {
	char* name;
} GameStrategy;

/**
 * Print the detail of each strategy.
 */
void printGameStrategy(OutputStream* outputStream, GameStrategy* strategy);

#endif

