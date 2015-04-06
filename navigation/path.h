#ifndef PATH_H
#define PATH_H

#include <stdbool.h>

#include "location.h"

typedef struct PathData {
    /** name of the path. */
    char* pathName;
    /** first point (with name). */
    Location* location1;
    /** second point (with name). */
    Location* location2;
    /** Cost of the path. */
    unsigned int cost;
    /** Distance of the control point P0-P1 in cm. */     
    signed char controlPointDistance1;
    /** Distance of the control point P1->P3 in cm. */     
    signed char controlPointDistance2;
    /** angle1 (when at P0) in decidegree. */
    int angle1;
    /** angle2 (when at P3) in decidegree. */
    int angle2;
    /** AccelerationFactor factor (min = 1, max = 16). */
    unsigned char accelerationFactor;
    /** Speed factor (min = 1, max = 16). */
    unsigned char speedFactor;
    /** When reversed, the path must be done backward. */
    bool mustGoBackward;
} PathData;

int getAngle1Path(PathData* pathData);

int getAngle2Path(PathData* pathData);

void fillPathData(PathData* pathData,
                        Location* location1,
                         Location* location2, 
                         int cost,
                         int controlPointDistance1,
                         int controlPointDistance2,
                         int angle1,
                         int angle2,
                         unsigned char accelerationFactor,
                         unsigned char speedFactor);

/** 
 * Fills the data of an asymmetric path, a path on which 
 * the robot must move backward when reversed.
 */
void fillAsymmetricPathData(PathData* pathData, 
                        Location* location1,
                         Location* location2, 
                         int cost,
                         int controlPointDistance1,
                         int controlPointDistance2,
                         int angle1,
                         int angle2,
                         unsigned char accelerationFactor,
                         unsigned char speedFactor);

/**
 * Return if the path contains the location passed in parameter
 */
bool pathContainsLocation(PathData* pathData, Location* location);

/**
 * Returns the opposite location on the path.
 * @param path (this) the path for which we want to find the opposite location
 * @param location the location for which we want to search the opposite
 */
Location* getOtherEnd(PathData* pathData, Location* location);

/**
 * Print debugguable path.
 */
void printPath(OutputStream* outputStream, PathData* pathData);

#endif
