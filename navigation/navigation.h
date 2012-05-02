#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"

/**
 * Add the location to the navigation graph.
 */
void addNavigationLocation(Location* location, char* name, int x, int y);

/**
 * Computes the path.
 * @param outLocationList the out parameter which is filled
 * @param start startPoint
 * @param end endPoint
 */
int computeBestPath(LocationList* outLocationList, Location* start, Location* end);

#endif
