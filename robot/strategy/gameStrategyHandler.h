#ifndef GAME_STRATEGY_HANDLER
#define GAME_STRATEGY_HANDLER

#include "gameStrategyContext.h"

/** If set, simulates the move of the robot. */
#define  SIMULATE_ROBOT

/** Use flag to know if we trace Handler strategy. */
#define DEBUG_STRATEGY_HANDLER

/**
 * Returns the strategy context used by the handler.
 */
GameStrategyContext* getStrategyContext();

void nextStep();


#endif

