#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"

#define	BIT_LIST_NAVIGATION_ARRAY_LENGTH	(MAX_PATH / BITS_COUNT_IN_UNSIGNED_INT) + 1

/**
 * Initialize the navigation system.
 */
void initNavigation();

/**
 * Returns the navigation (singleton) location List.
 */
LocationList* getNavigationLocationList();

/**
 * Returns the navigation (singleton) path list.
 */
PathList* getNavigationPathList();


/**
 * Add the location to the navigation graph.
 */
void addNavigationLocation(Location* location, char* name, int x, int y);

/**
 * Add the path to the navigation graph.
 */
void addNavigationPath(PathDataFunction* pathDataFunction);

/**
 * Computes the path.
 * @param outLocationList the out parameter which is filled
 * @param start startPoint
 * @param end endPoint
 */
int computeBestPath(LocationList* outLocationList, 
					Location* start,
					Location* end);

void printNavigationContext();

#endif
