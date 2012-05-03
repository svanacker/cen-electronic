#ifndef LOCATION_H
#define LOCATION_H

#include <stdlib.h>

#include "../common/commons.h"
#include "../common/io/outputStream.h"

#define MAX_COST 			20000
#define NO_COMPUTED_COST	-1

/**
 * Encapsulates the location.
 */
typedef struct Location {
	/** The name. */
	char* name;
	/** The coordinates in x. */
	int x;
	/** The coordinates in y. */
	int y;
	/** Temporary information needed by path finding algorithm. */
	int tmpCost;
} Location;

/**
 * Equals function on Location. The equals is based on the
 * name of the location !
 */
BOOL locationEquals(Location* location1, Location* location2);

/**
 * Print the location on the outputStream.
 */
void printLocation(OutputStream* outputStream, Location* location);

#endif
