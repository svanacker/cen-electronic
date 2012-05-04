#ifndef PATH_H
#define PATH_H

#include "location.h"

/**
 * Encapsulates a path between 2 points.
 */
typedef struct Path {
	/** first point (with name). */
	Location* location1;
	/** second point (with name). */
	Location* location2;
	/** Distance of the control point P0-P1. */ 	
	unsigned char controlPointDistance1;
	/** Distance of the control point P1->P3. */ 	
	unsigned char controlPointDistance2;
	/** angle1 (when at P0) in decidegree. */
	int angle1;
	/** angle2 (when at P3) in decidegree. */
	int angle2;
	/** Cost of the path. */
	unsigned char cost;
	/** Speed factor (max = FF, min = 1). */
	unsigned char speedFactor;
} Path;

/**
 * Return if the path contains the location passed in parameter
 */
BOOL pathContainsLocation(Path* path, Location* location);

/**
 * Returns the opposite location on the path.
 * @param path (this) the path for which we want to find the opposite location
 * @param location the location for which we want to search the opposite
 */
Location* getOtherEnd(Path* path, Location* location);

/**
 * Print debugguable path.
 */
void printPath(OutputStream* outputStream, Path* path);

#endif
