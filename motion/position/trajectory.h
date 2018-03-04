#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "../../device/device.h"
#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

/**
 * Structure to store all informations linked to the follow of trajectory.
 */
typedef struct {
    Position position;
    // Last left coder value
    float lastLeft;
    // Last right coder value
    float lastRight;
    // Last angle
    float lastAngle;
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

#endif
