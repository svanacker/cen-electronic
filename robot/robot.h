#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>

#include "../common/commons.h"
#include "../common/io/outputStream.h"

// Time in seconds
#define TIME_FOR_OBSTACLE_NEW_NOTIFICATION             4

// MAIN FUNCTIONS

/**
* Returns true if we must stop the robot
*/
unsigned int isRobotMustStop();

/**
* Change the fact that the robot must stop
*/
void setRobotMustStop(unsigned int value);

/**
* Stop the robot and avoid the PIC to restart.
*/
void stopRobot(void);

void stopRobotObstacle(void);

// POSITION

int getRobotPositionX();

int getRobotPositionY();

int getRobotAngle();

void updateRobotPosition(int x, int y, int angle);

void printRobotPosition(OutputStream* outputStream);

bool isRobotPositionChanged();

void resetRobotPositionChanged();

void setRobotPositionChanged();

#endif
