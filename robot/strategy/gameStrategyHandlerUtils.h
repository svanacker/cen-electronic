#ifndef GAME_STRATEGY_UTILS_HANDLER
#define GAME_STRATEGY_UTILS_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

/**
 * Define the time in second for which, if there is no collision, we can reset All path to available.
 * This time must be > to the notification Collision time, to avoid that it reset it.
*/
#define RESET_OBSTACLE_COLLISION_TIME_SECOND        5

Location* getNearestLocationFromGameStrategyContext(GameStrategyContext* gameStrategyContext);

/**
 * Clears the current path and actions.
 * Useful when we want to cancel a target or go out from a target.
 */
void clearCurrentTarget(GameStrategyContext* gameStrategyContext);

// STATUS MANAGEMENT
void markTargetInUse(GameStrategyContext* gameStrategyContext);

void markTargetAsHandled(GameStrategyContext* gameStrategyContext);

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

bool motionRotateToFollowPath(GameStrategyContext* gmeStrategyContext, PathData* pathData, bool reversed);

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

