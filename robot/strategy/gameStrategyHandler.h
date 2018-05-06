#ifndef GAME_STRATEGY_HANDLER
#define GAME_STRATEGY_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

/** Use flag to know if we trace Handler strategy. */
#define DEBUG_STRATEGY_HANDLER

/** Use flag to know if we trace Opponent Robot management. */
#define DEBUG_OPPONENT_ROBOT

/** Minimum angle to add a rotation in degrees. */
#define ANGLE_ROTATION_MIN 5.0f

/** Distance of the opponent to a path to make it unavailable in mm. */
#define DISTANCE_OPPONENT_TO_PATH 200.0f

/** Distance of a detected obstacle in mm. */
#define DISTANCE_OBSTACLE 250.0f

/**
 * Define the time in second for which, if there is no collision, we can reset All path to available. 
 * This time must be > to the notification Collision time, to avoid that it reset it.
*/
#define RESET_OBSTACLE_COLLISION_TIME_SECOND        5

// Init

void initStrategyHandler(GameStrategyContext* gmeStrategyContext);

/**
 * Choose the rigth strategy.
 */
void setStrategy(GameStrategyContext* gmeStrategyContext, int strategyIndex);

/**
 * Returns the strategy context used by the handler.
 */
GameStrategyContext* getStrategyContext(GameStrategyContext* gmeStrategyContext);

/**
 * Do the next step in the strategy. Returns false if nothing was done.
 */
bool nextStep(GameStrategyContext* gmeStrategyContext);

// OBSTACLE

void computePoint(Point* ref, Point* cp, float distance, float angle);

/**
 * Update all paths / opponent Robot Position to mark them as unavailable if the robot is on
 * this path !
 */
void updatePathsAvailability(GameStrategyContext* gmeStrategyContext);

/**
 * Handle a collision detection.
 */
void handleCollision(GameStrategyContext* gmeStrategyContext);

// MOTION

void rotateAbsolute(GameStrategyContext* gameStrategyContext, float angle);

/**
 * Ask to follow a path.
 */
void motionFollowPath(GameStrategyContext* gmeStrategyContext, PathData* pathData, bool reversed);

/**
 * Ask the robot to go to a location but without path (useful for actionItem).
 */
void motionGoLocation(Location* location, 
                    float angle,
                    float controlPointDistance1, float controlPointDistance2,
                    float accelerationFactor, float speedFactor);

/**
 * Update the Motor Board Robot Position (needed at start).
 */
bool updateMotorBoardRobotPosition(GameStrategyContext* gameStrategyContext);

#endif

