#ifndef STRATEGY_H
#define STRATEGY_H

#include "teamColor.h"

#include "../../robot/config/robotConfig.h"

/**
* Returns the side of the robot.
* @return SIDE_YELLOW or SIDE_BLUE
*/
enum TeamColor getMatchSide();

/**
* Load the side of the robot.
*/
void loadMatchSideAndUpdateRobotPosition(RobotConfig* robotConfig);

#endif
