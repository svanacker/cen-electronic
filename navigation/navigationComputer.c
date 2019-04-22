#include "navigationComputer.h"
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
 * Returns the cost associated to location.
 */
float getTmpCost(Location* location) {
    if (location->tmpCost == NO_COMPUTED_COST) {
        return MAX_COST;
    }
    return location->tmpCost;
}

/**
 * Change the cost associated to the location.
 */
void setTmpCost(Location* location, float cost) {
    location->tmpCost = cost;
}

/**
 * @private
 * Search the nearest node in terms of cost
 */
Location* extractMinCostLocation(Navigation* navigation) {
    // Search the nearest node in terms of cost
    Location* result = NULL;
    float minCost = MAX_COST;
    int size = navigation->locationList->size;
    int locationIndex;
    // Loop every Location
    for (locationIndex = 0; locationIndex < size; locationIndex++) {
        Location* location = getLocation(navigation->locationList, locationIndex);
        // we only manage only unhandled location point
        if (location->tmpHandled) {
            continue;
        }
#ifdef NAVIGATION_DEBUG 
        appendString(getInfoOutputStreamLogger(), "\t");
        printLocation(getInfoOutputStreamLogger(), location);
#endif

        // get the cost
        float cost = getTmpCost(location);
#ifdef NAVIGATION_DEBUG
        appendStringAndDec(getInfoOutputStreamLogger(), "\tcost:", cost);
        println(getInfoOutputStreamLogger());
#endif
        if (cost <= minCost) {
            minCost = cost;
            result = location;
        }
    }
    // mark location as handled
    result->tmpHandled = true;
    return result;
}

float computeBestPath(Navigation* navigation, Location* start, Location* end) {
    float result = 0.0f;

    // not necessary because handledLocationList elements are removed from unhandled to handled.
    // we can not have doublon.
    // unhandledLocationList.set = true;    
    // handledLocationList.set = true;

    clearLocationTmpInfo(navigation->locationList);
    Location* location1;

    start->tmpCost = 0;
#ifdef NAVIGATION_DEBUG
    printLocation(getInfoOutputStreamLogger(), start);
#endif

    unsigned int locationSize = navigation->locationList->size;
    unsigned int i = 0;
    // Loop on every location
    for (i = 0; i < locationSize; i++) {
        // search the nearest node of the nodeList
#ifdef NAVIGATION_DEBUG
        appendStringLN(getInfoOutputStreamLogger(), "extractMinCostLocation");
#endif
        location1 = extractMinCostLocation(navigation);

#ifdef NAVIGATION_DEBUG
        appendString(getInfoOutputStreamLogger(), "bestLocation=");
        printLocation(getInfoOutputStreamLogger(), location1);
#endif

        // List of path going to the node (location)
        updateOutgoingPaths(navigation, location1);

        unsigned int j;

        // loop on all outgoingPath of the location
        OutgoingPathList* tmpOutgoingPaths = navigation->tmpOutgoingPaths;
        unsigned int pathSize = tmpOutgoingPaths->size;
        for (j = 0; j < pathSize; j++) {
            /*
            // Do not use paths that are not available
            bool available = getPathAvailability(navigation, j);
            if (!available) {
                continue;
            }
            */

            OutgoingPathData* outgoingPathData = getOutgoingPath(navigation->tmpOutgoingPaths, j);
            PathData* pathData = outgoingPathData->pathData;
            Location* location2 = getOtherEnd(pathData, location1);
            float costLocation1 = getTmpCost(location1);
            float costLocation2 = getTmpCost(location2);

            // getOtherEnd called the current fonction to fill path information
            // so we can use pathData without problem.
            float cost = costLocation1 + pathData->cost;

            /*
            if (!available) {
                cost += COST_UNAVAILABLE_PATH;
            }
            */

            if (cost < costLocation2) {
                // Set the node absolute cost
                setTmpCost(location2, cost);
                location2->tmpPreviousLocation = location1;
                location1->resultNextLocation = location2;
            }
        }
    }
    // store best cost
    result = getTmpCost(end);
    location1 = end;

    return result;
}