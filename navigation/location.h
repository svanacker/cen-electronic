#ifndef LOCATION_H
#define LOCATION_H

#include <stdlib.h>

#include "../common/commons.h"
#include "../common/io/outputStream.h"

/**
 * Encapsulates the location.
 */
typedef struct Location {
	char* name;
	int x;
	int y;
} Location;

/**
 * Equals function on Location. The equals is based on the
 * name of the location !
 */
BOOL locationEquals(Location* location1, Location* location2);

/**
 * Print the location on the outputStream.
 */
void printLocation(Location* location, OutputStream* outputStream);

#endif
