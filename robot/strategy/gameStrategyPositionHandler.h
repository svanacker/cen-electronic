#ifndef GAME_STRATEGY_POSITION_HANDLER
#define GAME_STRATEGY_POSITION_HANDLER

#include "../../navigation/location.h"
#include "../../navigation/path.h"

#include "gameStrategyContext.h"

/**
 * Update the Motor Board Robot Position (needed at start) to synchronize the position of the 2 Boards.
 * Master Data is then owned by the Motor Board, and the Slave information is read by the Main Board from the Motor Board
 */
bool updateRobotPositionFromMainBoardToMotorBoard(GameStrategyContext* gameStrategyContext);

/**
* This method must be frequently called by the main Board to be sure to have the right position.
*/
void updateIfNeededRobotPositionFromMotorBoardToMainBoard(GameStrategyContext* gameStrategyContext);

/**
* Compute the nearest location in the path finding from the current position of the robot
* The location is the lowest only in terms of "Time of Flight", and not in terms of complexity to reach it
*/
Location* getNearestLocationFromGameStrategyContext(GameStrategyContext* gameStrategyContext);

#endif

