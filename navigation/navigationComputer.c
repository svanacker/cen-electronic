#include "navigationComputer.h"
#include "locationListComputer.h"
#include "outgoingPathList.h"


void updateOutgoingPaths(Navigation* navigation, Location* location) {
    clearOutgoingPathList(navigation->tmpOutgoingPaths);
    int i;
    int pathSize = getPathCount(navigation->paths);
    for (i = 0; i < pathSize; i++) {
        PathData* pathData = getPath(navigation->paths, i);

        // For example : location = "A", check if path contains("A") : "AB" contains "A", but "DE" not
        bool pathContainsLocationBool = pathContainsLocation(pathData, location);

        if (!pathContainsLocationBool) {
            continue;
        }

        // Check if the locationList that we handle contains the other end
        // Ex : path = "AB", location="A" => otherEnd = "B"
        Location* otherEnd = getOtherEnd(pathData, location);

        // Ex : handledLocationList = {EF, GH} and other End = B
        bool handledLocationListContainsLocation = containsLocation(navigation->locationList, otherEnd, true);
        if (!handledLocationListContainsLocation) {
            addOutgoingPath(navigation->tmpOutgoingPaths, pathData);
        }
    }
}

/**
 * Change the cost associated to the location.
 */
void setTmpCost(Location* location, float cost) {
    location->tmpCost = cost;
}


float computeBestPath(Navigation* navigation, Location* start, Location* end) {
    LocationList* locationList = navigation->locationList;
    float result = 0.0f;

    clearLocationTmpInfo(locationList);
    Location* location1;
    start->tmpCost = 0;

    unsigned int locationSize = locationList->size;
    unsigned int i = 0;
    // Loop on every location
    for (i = 0; i < locationSize; i++) {
        // search the nearest node of the nodeList
        location1 = extractMinCostLocation(locationList);

        // List of path going to the node (location)
        updateOutgoingPaths(navigation, location1);

        unsigned int j;

        // loop on all outgoingPath of the location
        OutgoingPathList* tmpOutgoingPaths = navigation->tmpOutgoingPaths;
        unsigned int tmpOutgoingPathSize = tmpOutgoingPaths->size;
        for (j = 0; j < tmpOutgoingPathSize; j++) {
            // Do not use paths that are not available
            bool available = getPathAvailability(navigation, j);
            if (!available) {
                continue;
            }

            OutgoingPathData* outgoingPathData = getOutgoingPath(navigation->tmpOutgoingPaths, j);
            PathData* pathData = outgoingPathData->pathData;
            Location* location2 = getOtherEnd(pathData, location1);
            float costLocation1 = getTmpCost(location1);
            float costLocation2 = getTmpCost(location2);

            // getOtherEnd called the current fonction to fill path information
            // so we can use pathData without problem.
            float cost = costLocation1 + pathData->cost;

            if (!available) {
                cost += COST_UNAVAILABLE_PATH;
            }

            if (cost < costLocation2) {
                // Set the node absolute cost
                setTmpCost(location2, cost);
                location1->resultNextLocation = location2;
            }
            else {
                location1->resultNextLocation = NULL;
            }
        }
    }
    // store best cost
    result = getTmpCost(end);
    location1 = end;

    cutLocationLinkedList(start, end);

    return result;
}