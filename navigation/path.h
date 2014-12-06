#ifndef PATH_H
#define PATH_H

#include <stdbool.h>

#include "location.h"

/**
 * Function which gives fill all informations in a intermediate structure.
 * All call must be done by getXXX(Path* path) which fill the data and then read it in common.
 * This trick enabled us to save memory and to use instead of program memory.
 * This trick is only possible on read data. So tmpOutgoing is a standard struc path member.
 */

/** Define the function which will be called to fill PathData. */
typedef void PathDataFunction();

typedef struct PathData {
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

int getAngle1Path(PathDataFunction* pathDataFunction);

int getAngle2Path(PathDataFunction* pathDataFunction);

void fillPathData(Location* location1,
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
void fillAsymmetricPathData(Location* location1,
                         Location* location2, 
                         int cost,
                         int controlPointDistance1,
                         int controlPointDistance2,
                         int angle1,
                         int angle2,
                         unsigned char accelerationFactor,
                         unsigned char speedFactor);

/**
 * Return the unique structure which must be filled before.
 * Be careful to call path->pathDataFunction before any call ! If you don't, data will be random
 * (the last call) and does not corresponds to your current Path.
 */
PathData* getTmpPathData();


/**
 * Return if the path contains the location passed in parameter
 */
bool pathContainsLocation(PathDataFunction* path, Location* location);

/**
 * Returns the opposite location on the path.
 * @param path (this) the path for which we want to find the opposite location
 * @param location the location for which we want to search the opposite
 */
Location* getOtherEnd(PathDataFunction* pathDataFunction, Location* location);

/**
 * Print debugguable path.
 */
void printPath(OutputStream* outputStream, PathDataFunction* path);

#endif
