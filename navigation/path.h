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
	int controlPointDistance1;
	/** Distance of the control point P1->P3. */ 	
	int controlPointDistance2;
	/** angle1 (when at P0) in decidegree. */
	int angle1;
	/** angle2 (when at P3) in decidegree. */
	int angle2;
	/** Cost of the path. */
	int cost;
	/** Speed factor (max = FF, min = 1). */
	int speedFactor;
} Path;

#endif
