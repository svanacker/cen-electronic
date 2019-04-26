#ifndef GAME_STRATEGY_MOTION_HANDLER
#define GAME_STRATEGY_MOTION_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

// POSITION MANAGEMENT

/**
 * Update the Motor Board Robot Position (needed at start).
 */
bool updateMotorBoardRobotPosition(GameStrategyContext* gameStrategyContext);


/**
* Compute the nearest location in the path finding from the current position of the robot
* The location is the lowest only in terms of "Time of Flight", and not in terms of complexity to reach it
*/
Location* getNearestLocationFromGameStrategyContext(GameStrategyContext* gameStrategyContext);

/**
 * Clears the current path and actions.
 * Useful when we want to cancel a target or go out from a target.
 */
void clearCurrentTarget(GameStrategyContext* gameStrategyContext);

// MOTION

/**
 * Ask to follow a path.
 */
void motionFollowPath(GameStrategyContext* gmeStrategyContext, PathData* pathData);

/**
* Ask to do a small rotation to ensure that the robot will restart the next move with the right angle
* @param pathData the next pathData that the robot has to do
* @return true if the robot has really moved, false else
*/
bool motionRotateToFollowPath(GameStrategyContext* gmeStrategyContext, PathData* pathData);

#endif

