#ifndef GAME_STRATEGY_COLLISION_HANDLER
#define GAME_STRATEGY_COLLISION_HANDLER

#include "../../common/2d/2d.h"
#include "gameStrategyContext.h"

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


#endif

