#include "locationListComputer.h"

#include "../common/2d/2d.h"

#include <stdlib.h>

Location* getNearestLocation(LocationList* locationList, float x, float y) {
    Location* result = NULL;
    int i;
    int size = locationList->size;
    float min = MAX_COST;

    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        // We can have hole because of "remove"
        if (location == NULL) {
            continue;
        }
        float distance = distanceBetweenPoints2(location->x, location->y, x, y);
        if (distance < min) {
            min = distance;
            result = location;
        }
    }
    return result;
}


/**
 * Returns the cost associated to location.
 */
float getTmpCost(Location* location) {
    if (location->tmpCost == NO_COMPUTED_COST) {
        return MAX_COST;
    }
    return location->tmpCost;
}

/**
 * @private
 * Search the nearest node in terms of cost
 */
Location* extractMinCostLocation(LocationList* locationList) {
    // Search the nearest node in terms of cost
    Location* result = NULL;
    float minCost = MAX_COST;
    int size = locationList->size;
    int locationIndex;
    // Loop every Location
    for (locationIndex = 0; locationIndex < size; locationIndex++) {
        Location* location = getLocation(locationList, locationIndex);
        // we only manage only unhandled location point
        if (location->tmpHandled) {
            continue;
        }

        // get the cost
        float cost = getTmpCost(location);
        if (cost <= minCost) {
            minCost = cost;
            result = location;
        }
    }
    // mark location as handled
    result->tmpHandled = true;
    return result;
}