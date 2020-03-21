#ifndef NAVIGATION_COMPUTER_H
#define NAVIGATION_COMPUTER_H

#include "navigation.h"

/**
 * Update the outgoing paths for a specific Location.
 */
void updateOutgoingPaths(Navigation* navigation, Location* location);

/**
 * Computes the path.
 * @param the context of Navigation
 * @param start startPoint the start point will have a linked pointer on the next point to reach recursively to the end point
 * @param end endPoint
 * @return the cost to reach the best Path
 */
float computeBestPath(Navigation* navigation,
        Location* start,
        Location* end);

#endif
