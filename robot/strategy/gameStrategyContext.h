#ifndef GAME_STRATEGY_CONTEXT_H
#define GAME_STRATEGY_CONTEXT_H

#include "gameStrategy.h"

#include "../../navigation/location.h"

/**
 * Encapsulates the context of the strategy.
 */
typedef struct GameStrategyContext {
	/** The choosen gameStrategy. */
	GameStrategy* gameStrategy;
	/** The elapsedMatchTime in seconds .*/
	float elapsedMatchTime;
	/** The currentLocation of the robot. */
	Location* currentLocation;
	// TODO : Opponent Robot.
} GameStrategyContext;

/**
 * Print the context of the game Strategy.
 */
void printGameStrategyContext(OutputStream* outputStream, GameStrategyContext* context);

#endif

