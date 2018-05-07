#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../device/device.h"

#define TRAJECTORY_THRESHOLD_NOTIFY_DEFAULT_VALUE               true
// 5 cm of threshold
#define TRAJECTORY_THRESHOLD_DISTANCE_MM_DEFAULT_VALUE         50.0f
// About 10 degree
#define TRAJECTORY_THRESHOLD_ANGLE_RADIAN_DEFAULT_VALUE    0.174533f

/**
 * Structure to store all informations linked to the follow of trajectory.
 */
typedef struct {
    /** The current position with angle and initial Orientation */
    Position position;
    // Last left coder value
    float lastLeft;
    // Last right coder value
    float lastRight;
    // Last angle
    float lastAngle;
    // NOTIFY CHANGE SYSTEM
    /** If we activate the notification on trajectory change */
    bool notifyChange;
    /** The last notified current Position with angle and initial Orientation*/
    Position lastNotificationPosition;
    /** The threshold in terms of distance (mm) to notify the new position */
    float thresholdDistance;
    /** The threshold in terms of angle (radian) to notify the new position */
    float thresholdAngleRadian;
} TrajectoryInfo;

/**
 * Returns all data about the follow of the trajectory.
 */
TrajectoryInfo* getTrajectory(void);

/**
 * Initializes the trajectory computer and sets the current
 * position to (0, 0) with an orientation angle of 0.
 */
void initializeTrajectory(void);

/**
 * Clears the current trajectory informations and sets the
 * current position to (0, 0) with the orientation 0.
 */
void clearTrajectory(void);

// POSITION

/**
 * Returns the current absolute position.
 * @return the structure representing the current position
 */
Position* getPosition(void);

/**
 * Sets the absolute position.
 * @param x the x coordinate in true length
 * @param y the y coordinate in true length
 * @param orientation the orientation angle
 */
void setPosition(float x, float y, float orientation);

/**
 * Adjust the X Position, with a threshold to avoid that if we are blocked, we increase the error instead
 * to decrease them.
 */
bool adjustXPosition(float x, float thresholdDistance);

/**
 * Adjust the Y Position,  with a threshold to avoid that if we are blocked, we increase the error instead
 * to decrease them.
 * @param y
 */
bool adjustYPosition(float y, float thresholdDistance);

/**
 * Adjust the angle with a threshold to avoid that if we are blocked, we increase the error instead
 * to decrease them.
 * We do not provide the angle but we consider that we use always a value close to
 * 0 / 90 / 180 / 270 degree
 */
bool adjustAngle(float thresholdAngle);

/**
 * Update the information for the trajectory.
 * Please note that the trajectory can differed from the reality
 * because of threshold
 */
void updateTrajectory(void);

/**
 * Update the information for the trajectory, but does not
 * use Threshold.
 */
void updateTrajectoryWithNoThreshold(void);

/**
 * Update the information for the trajectory and store to avoid
 * lost of information, and clear Coders.
 */
void updateTrajectoryAndClearCoders(void);

// NOTIFICATION & TRAJECTORY_TYPE

enum TrajectoryType computeTrajectoryType(float distanceSinceLastNotification, float angleRadianSinceLastNotification);

float getDistanceBetweenLastNotificationAndCurrentRobotPosition(void);

float getAbsoluteAngleRadianBetweenLastNotificationAndCurrentRobotPosition(void);

void clearLastNotificationData(void);

#endif
