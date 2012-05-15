#ifndef GAME_STRATEGY_HANDLER
#define GAME_STRATEGY_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

/** If set, simulates the move of the robot. */
#define  SIMULATE_ROBOT

/** Use flag to know if we trace Handler strategy. */
#define DEBUG_STRATEGY_HANDLER

/** Use flag to know if we trace Opponent Robot management. */
#define DEBUG_OPPONENT_ROBOT

/** Minimum angle to add a rotation. */
#define ANGLE_ROTATION_MIN 50

/** Distance of the opponent to a path to made it unavailable. */
#define DISTANCE_OPPONENT_TO_PATH 300

/**
 * Choose the rigth strategy.
 */
void setStrategy(int strategyIndex);

/**
 * Returns the strategy context used by the handler.
 */
GameStrategyContext* getStrategyContext();

/**
 * Do the next step in the strategy. Returns FALSE if nothing was done.
 */
BOOL nextStep();

// OBSTACLE

/**
 * Update all paths / opponent Robot Position to mark them as unavailable if the robot is on
 * this path !
 */
void updatePathsAvailability();

// MOTION

/**
 * Ask to follow a path.
 */
void motionFollowPath(PathDataFunction* pathDataFunction);

/**
 * Ask the robot to go to a location but without path (useful for actionItem).
 */
void motionGoLocation(Location* location, 
					int angle,
					int controlPointDistance1, int controlPointDistance2,
					int accelerationFactor, int speedFactor );


#endif

