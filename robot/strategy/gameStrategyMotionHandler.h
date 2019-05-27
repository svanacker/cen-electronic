#ifndef GAME_STRATEGY_MOTION_HANDLER
#define GAME_STRATEGY_MOTION_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

/**
* Initialize the motion part of the GameStrategyContext*.
*/
void initGameStrategyMotionHandler(GameStrategyContext* gameStrategyContext);

/**
 * Ask to follow a path.
 */
bool motionFollowPath(GameStrategyContext* gmeStrategyContext, PathData* pathData);

/**
* Ask to do a small rotation to ensure that the robot will restart the next move with the right angle
* @param pathData the next pathData that the robot has to do
* @return true if the robot has really moved, false else
*/
bool motionRotateToFollowPath(GameStrategyContext* gmeStrategyContext, PathData* pathData);

// COMBINAISON Of Rotate / Follow

bool followComputedNextPath(GameStrategyContext* gameStrategyContext);


#endif

