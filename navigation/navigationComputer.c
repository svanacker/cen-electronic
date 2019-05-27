#include "navigationComputer.h"
#include "locationListComputer.h"
#include "outgoingPathList.h"


void updateOutgoingPaths(Navigation* navigation, Location* location) {
    clearOutgoingPathList(navigation->tmpOutgoingPaths);
    int i;
    int pathSize = getPathCount(navigation->paths);
    for (i = 0; i < pathSize; i++) {
        PathData* pathData = getPath(navigation->paths, i);
        // Check the path which start at location
        if (pathData->location1 == location) {
            addOutgoingPath(navigation->tmpOutgoingPaths, pathData);
        }
    }
}

/**
 * Change the cost associated to the location.
 */
void setTmpCost(Location* location, float cost) {
    location->computedCost = cost;
}


float computeBestPath(Navigation* navigation, Location* start, Location* end) {
    LocationList* locationList = navigation->locationList;

    // https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    // "Assign to every node a tentative distance value: set it to zero for our initial node and to infinity for all other nodes. 
    // Set the initial node as current."
    clearLocationTmpInfo(locationList);
    Location* location1;
    start->computedCost = 0.0f;

    unsigned int locationSize = locationList->size;
    unsigned int i = 0;

    unsigned int locationNotHandledCount = locationSize;

    // https://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra
    // "tant que Q n'est pas un ensemble vide"
    while (locationNotHandledCount > 0) {
        locationNotHandledCount = 0;
        // Loop on every location
        for (i = 0; i < locationSize; i++) {
            // We only manage location which are not already handled (simulate the creation of a new list)
            Location* tmpLocation = getLocation(locationList, i);
            if (tmpLocation->computedHandled) {
                continue;
            }
            locationNotHandledCount++;

            // search the nearest node of the nodeList
            location1 = extractMinCostLocation(locationList);
            location1->computedHandled = true;

            // List of path out going starting from the node (location)
            updateOutgoingPaths(navigation, location1);

            unsigned int j;

            // loop on all outgoingPath of the location
            OutgoingPathList* tmpOutgoingPaths = navigation->tmpOutgoingPaths;
            unsigned int tmpOutgoingPathSize = tmpOutgoingPaths->size;
            for (j = 0; j < tmpOutgoingPathSize; j++) {
                OutgoingPathData* outgoingPathData = getOutgoingPath(navigation->tmpOutgoingPaths, j);
                PathData* pathData = outgoingPathData->pathData;
                Location* location2 = pathData->location2;
                float costLocation1 = getComputedCost(location1);
                float costLocation2 = getComputedCost(location2);

                float cost1 = costLocation1 + pathData->cost + pathData->obstacleCost;

                if (costLocation2 > cost1) {
                    // Set the node absolute cost
                    setTmpCost(location2, cost1);
                    // We could only know the predecessor
                    location2->computedPreviousLocation = location1;
                }
            }
        }
    }
    // Compute the success from the predecessor
    if (end != NULL) {
        Location* tmpLocation = end;
        while (tmpLocation->computedPreviousLocation != NULL) {
            // Reverse the link
            tmpLocation->computedPreviousLocation->computedNextLocation = tmpLocation;
            tmpLocation = tmpLocation->computedPreviousLocation;
        }

        // return best cost
        return getComputedCost(end);
    }
    return 0.0f;
}