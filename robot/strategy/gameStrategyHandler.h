#ifndef GAME_STRATEGY_HANDLER
#define GAME_STRATEGY_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

/** If set, simulates the move of the robot. */
#ifdef MPLAB_SIMULATION
	#define SIMULATE_ROBOT
#endif

/** Use flag to know if we trace Handler strategy. */
#define DEBUG_STRATEGY_HANDLER

/** Use flag to know if we trace Opponent Robot management. */
#define DEBUG_OPPONENT_ROBOT

/** Minimum angle to add a rotation in deci degrees. */
#define ANGLE_ROTATION_MIN 50

/** Distance of the opponent to a path to make it unavailable in mm. */
#define DISTANCE_OPPONENT_TO_PATH 200

/** Distance of a detected obstacle in mm. */
#define DISTANCE_OBSTACLE 250

/**
 * Define the time in second for which, if there is no collision, we can reset All path to available. 
 * This time must be > to the notification Collision time, to avoid that it reset it.
*/
#define RESET_OBSTACLE_COLLISION_TIME_SECOND		5

// Init

void initStrategyHandler();

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
bool nextStep();

// OBSTACLE

/**
 * Update all paths / opponent Robot Position to mark them as unavailable if the robot is on
 * this path !
 */
void updatePathsAvailability();

/**
 * Handle a collision detection.
 */
void handleCollision();

// MOTION

void rotateAbsolute(int angle);

/**
 * Ask to follow a path.
 */
void motionFollowPath(PathDataFunction* pathDataFunction, bool reversed);

/**
 * Ask the robot to go to a location but without path (useful for actionItem).
 */
void motionGoLocation(Location* location, 
					int angle,
					int controlPointDistance1, int controlPointDistance2,
					int accelerationFactor, int speedFactor );


#endif

