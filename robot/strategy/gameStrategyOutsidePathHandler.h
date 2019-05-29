#ifndef GAME_STRATEGY_OUTSIDE_PATH_HANDLER
#define GAME_STRATEGY_OUTSIDE_PATH_HANDLER

#include "gameStrategyHandler.h"

/**
* Creates a new "route" for the robot which is not on a classical Path !
*/
void gameStrategyCreateOutsideTemporaryPaths(GameStrategyContext* gameStrategyContext);

/**
* Do the cleanup when the robot is back to the Track.
*/
void gameStrategyClearOusideTemporaryPathsAndLocations(GameStrategyContext* gameStrategyContext);

#endif

