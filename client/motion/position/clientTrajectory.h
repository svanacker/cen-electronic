#ifndef CLIENT_TRAJECTORY_H
#define CLIENT_TRAJECTORY_H

#include "../../../robot/robot.h"

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
bool clientTrajectoryUpdateRobotPosition(RobotPosition* robotPosition);

/**
 * This procedure updates the orientation of the robot for each Quadran of PI/2.
 * Ex, if the robot is 37° oriented, it does nothing, if the robot is oriented of 270.2° and if the threshold to adjust 
 * is greater than 0.2°, it will change the orientation to 270°
 * The adjustment could then raise a notification because of this change
 */
bool clientTrajectoryAdjustAngleToClosest(void);

/**
 * When that we are sure of our position, but that we would like to compensate a drift along X axis, we could use
 * this. 
 * Be careful that if the drift is too important, the position will not be change (to avoid that if we are blocked by a big object,
 * we must not update the robot position to a false position
 * The adjustment could then raise a notification because of this change
 */
bool clientTrajectoryAdjustXPosition(float x);

/**
 * When that we are sure of our position, but that we would like to compensate a drift along Y axis, we could use
 * this.
 * Be careful that if the drift is too important, the position will not be change (to avoid that if we are blocked by a big object,
 * we must not update the robot position to a false position
 * The adjustment could then raise a notification because of this change
 */
bool clientTrajectoryAdjustYPosition(float y);

// NOTIFICATION

/**
 * Set or disable the notification when the robot trajectory change.
 * @return true if the operation was successfull, false else
 */
bool clientTrajectoryNotifySetEnabled(bool enabled);

/**
 * Change the threshold for which the notification must be thrown by the motor Board.
 * @param notifyDistanceThreshold when robot distance change for more than notifyDistanceThreshold since latest notification, it throws a notification
 * @param notifyAngleRadianThreshold when robot angle change for more than notifyAngleRadianThreshold since latest notification, it throws a notification
 * @return true if the operation was successfull, false else
 */
bool clientTrajectoryNotifySetThreshold(float notifyDistanceThreshold, float notifyAngleRadianThreshold);

#endif
