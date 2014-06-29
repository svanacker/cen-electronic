#ifndef STRATEGY_H
#define STRATEGY_H

/** We are on the yellow side. */
#define SIDE_YELLOW    1

/** We are on the blue side. */
#define SIDE_BLUE  -1

#define START_POSITION_X_YELLOW 150
#define START_POSITION_Y_YELLOW 150
#define START_POSITION_ANGLE_YELLOW 150

#define START_POSITION_X_BLUE 150
#define START_POSITION_Y_BLUE 150
#define START_POSITION_ANGLE_BLUE 150

/**
* Returns the side of the robot.
* @return SIDE_YELLOW or SIDE_BLUE
*/
signed int getMatchSide();

/**
* Load the side of the robot.
*/
void loadMatchSide();

#endif
