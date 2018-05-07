#ifndef CLIENT_TRAJECTORY_H
#define CLIENT_TRAJECTORY_H

#include <stdbool.h>

/**
 * Calls the Remote Trajectory Device to update the remote position (for example : MotorBoard)
 * @param x the target position in x
 * @param y the target position in y
 * @param radian the target position in deciDegree
 */
bool clientTrajectorySetAbsolutePosition(float x, float y, float radian);

/**
 * Update the Robot Position of current Device (Ex : MainBoard) from the Remote Device (for example : MotorBoard)
 * Typically, the MotorBoard moves, and we need to know the real position.
 */
bool clientTrajectoryUpdateRobotPosition(void);

bool clientTrajectoryAdjustAngleToClosest(void);

bool clientTrajectoryAdjustXPosition(float x);

bool clientTrajectoryAdjustYPosition(float y);

// NOTIFICATION

bool clientTrajectoryNotifySetEnabled(bool enabled);

bool clientTrajectoryNotifySetThreshold(float notifyDistanceThreshold, float notifyAngleRadianThreshold);

#endif
