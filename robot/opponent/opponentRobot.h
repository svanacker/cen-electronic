#ifndef OPPONENT_ROBOT_H
#define OPPONENT_ROBOT_H

#include "../../common/2d/2d.h"

/**
 * Returns the last Opponent Robot position.
 */
Point* getLastOpponentRobotPosition();

/**
 * Init the management of Opponent Robot by initializing a timer which will request 
 * every 500 ms the position of the opponent Robot.
 */
void initOpponentRobot();

/**
 * Update the opponent Robot if necessary (if timer has trickered it).
 */
void updateOpponentRobotIfNecessary();

#endif
