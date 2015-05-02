#ifndef STRATEGY_H
#define STRATEGY_H

#include "teamColor.h"

/** We are on the yellow side. */
#define SIDE_YELLOW    1

/** We are on the blue side. */
#define SIDE_GREEN  -1

#define START_POSITION_X_YELLOW 150
#define START_POSITION_Y_YELLOW 150
#define START_POSITION_ANGLE_YELLOW 90

#define START_POSITION_X_GREEN 150
#define START_POSITION_Y_GREEN 150
#define START_POSITION_ANGLE_BLUE 270

/**
* Returns the side of the robot.
* @return SIDE_YELLOW or SIDE_BLUE
*/
enum TeamColor getMatchSide();

/**
* Load the side of the robot.
*/
void loadMatchSide();

#endif
