#ifndef TRAJECTORY_DRIVER_H
#define TRAJECTORY_DRIVER_H

#include <stdbool.h>

/**
 * Calls the Remote Trajectory Device to update the remote position (for example : MotorBoard)
 * @param x the target position in x
 * @param y the target position in y
 * @param deciDegree the target position in deciDegree
 */
bool trajectoryDriverSetAbsolutePosition(float x, float y, float deciDegree);

/**
 * Update the Robot Position of current Device (Ex : MainBoard) from the Remote Device (for example : MotorBoard)
 * Typically, the MotorBoard moves, and we need to know the real position.
 */
bool trajectoryDriverUpdateRobotPosition();

#endif
