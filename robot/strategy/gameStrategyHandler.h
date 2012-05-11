#ifndef GAME_STRATEGY_HANDLER
#define GAME_STRATEGY_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

/** If set, simulates the move of the robot. */
#define  SIMULATE_ROBOT

/** Use flag to know if we trace Handler strategy. */
#define DEBUG_STRATEGY_HANDLER

/**
 * Choose the rigth strategy.
 */
void setStrategy(int strategyIndex);

/**
 * Returns the strategy context used by the handler.
 */
GameStrategyContext* getStrategyContext();

/**
 * Do the next step in the strategy
 */
void nextStep();

// MOTION

/**
 * Ask to follow a path.
 */
void motionFollowPath(PathDataFunction* pathDataFunction);

void motionGoLocation(Location* location, 
					int angle,
					int controlPointDistance1, int controlPointDistance2,
					int accelerationFactor, int speedFactor );


#endif

