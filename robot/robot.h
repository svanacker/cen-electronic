#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>

#include "../common/commons.h"
#include "../common/io/outputStream.h"

/**
 * Define the Structure which stores RobotPosition.
 */
typedef struct RobotPosition {
    // x in millimeter
    float x;
    // y in millimeter
    float y;
    // angle in decidegree
    float angleDegree;
} RobotPosition;

/** 
 * Defines some information needed by MainBoard about the status of the Robot.
 * Very precise information about the position of the robot is handled by the trajectory handler
 */

// Time in seconds
#define TIME_FOR_OBSTACLE_NEW_NOTIFICATION             4

// MAIN FUNCTIONS

/**
* Returns true if we must stop the robot
*/
bool isRobotMustStop();

/**
* Change the fact that the robot must stop
*/
void setRobotMustStop(bool value);

/**
* Stop the robot and avoid the PIC to restart.
*/
void stopRobot(void);

void stopRobotObstacle(void);

// POSITION

float getRobotPositionX();

float getRobotPositionY();

float getRobotAngle();

void updateRobotPosition(float x, float y, float angle);

void printRobotPosition(OutputStream* outputStream);

bool isRobotPositionChanged();

void resetRobotPositionChanged();

void setRobotPositionChanged();

#endif
