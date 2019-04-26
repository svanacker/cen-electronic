#ifndef PATH_H
#define PATH_H

#include <stdbool.h>

#include "../common/2d/2d.h"
#include "location.h"

/**
 * Contains all Information about a path, which is the minimal information to use a bspline by a robot.
 */
typedef struct PathData {
    /** first point (with name). */
    Location* location1;
    /** second point (with name). */
    Location* location2;
    /** Cost of the path. */
    float cost;
    /** Distance of the control point P0-P1 in mm (can be negative). */     
    float controlPointDistance1;
    /** Distance of the control point P1->P3 in mm. */     
    float controlPointDistance2;
    /** angle1 (when at P0) in degree. */
    float angleRadian1;
    /** angle2 (when at P3) in degree. */
    float angleRadian2;
    /** TODO : Convert into enum AccelerationFactor factor (min = 1, max = 16). */
    float accelerationFactor;
    /** Speed factor (min = 1, max = 16). */
    float speedFactor;
    /** When reversed, the path must be done backward. */
    bool mustGoBackward;
    /** We add an additionnal cost when encouring a robot which decrease time after time to retest after several seconds */
    float obstacleCost;
} PathData;

float getPathStartAngleRadian(PathData* pathData);

float getPathEndAngleRadian(PathData* pathData);

/**
 * Initializes the PathData structure with all informations.
 */
void initPathData(PathData* pathData,
                        Location* location1,
                         Location* location2, 
                         float cost,
                         float controlPointDistance1,
                         float controlPointDistance2,
                         float angleRadian1,
                         float angleRadian2,
                         float accelerationFactor,
                         float speedFactor);

/** 
 * Fills the data of an asymmetric path, a path on which 
 * the robot must move backward when reversed.
 */
void initAsymmetricPathData(PathData* pathData, 
                        Location* location1,
                         Location* location2, 
                         float cost,
                         float controlPointDistance1,
                         float controlPointDistance2,
                         float angle1,
                         float angle2,
                         unsigned char accelerationFactor,
                         unsigned char speedFactor);

/**
 * Return if the path contains the location passed in parameter
 * @param pathData the path for which we try to find if one point contains the location passed in parameter
 */
bool pathContainsLocation(PathData* pathData, Location* location);

/**
 * Ask the robot to move from the location1 (he must be very near, if not we will have some unpredictable result) to location2 with right angle1 / angle2
 */
bool moveAlongPath(PathData* pathData);

// OBSTACLE MANAGEMENT

void updateObstacleCostIfObstacle(PathData* pathData);

void decreaseObstacleCost(PathData* pathData);

/**
 * When we are too far from the locationPoint, we must use this method to
 * create a new BSpline to go back for the PathData
 * @param pathData
 * @param robotPosition
 * @return 
 */
bool restartFromPositionToGoToPath(PathData* pathData, Point* robotPosition);

#endif
