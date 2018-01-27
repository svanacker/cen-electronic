#include <stdlib.h>

#include "navigation.h"
#include "location.h"
#include "locationList.h"
#include "path.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/math/bitList.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

// #define NAVIGATION_DEBUG

/** The object with all information. */
static Navigation navigation;

void initNavigation(LocationList* locationList, PathList* pathList, BitList* outgoingPaths, BitList* availablePaths) {
    navigation.locationList = locationList;
    navigation.paths = pathList;
    navigation.outgoingPaths = outgoingPaths;
    navigation.availablePaths = availablePaths;
    
    // Init
    clearLocationList(navigation.locationList);
    clearPathList(navigation.paths);
    clearBitList(navigation.outgoingPaths, false);
    clearBitList(navigation.availablePaths, true);
}

LocationList* getNavigationLocationList(void) {
    return navigation.locationList;
}

PathList* getNavigationPathList(void) {
    return navigation.paths;
}

Location* addNavigationLocation(char* name, int x, int y) {
    LocationList* locationList = navigation.locationList;
    Location* result = addNamedLocation(locationList, name, x, y);
    return result;
}

PathData* addNavigationPath(
            Location* location1,
            Location* location2,
            int cost,
            int controlPointDistance1,
            int controlPointDistance2,
            int angle1,
            int angle2,
            unsigned char accelerationFactor,
            unsigned char speedFactor) {
    PathData* pathData = addPath(navigation.paths);
    initPathData(pathData, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
    return pathData;
}

void updateOutgoingPaths(Location* location) {
    clearBitList(navigation.outgoingPaths, false);
    int i;
    int pathSize = getPathCount(navigation.paths);
    for (i = 0; i < pathSize; i++) {
        PathData* pathData = getPath(navigation.paths, i);

        // For example : location = "A", check if path contains("A") : "AB" contains "A", but "DE" not
        bool pathContainsLocationBool = pathContainsLocation(pathData, location);

        if (!pathContainsLocationBool) {
            continue;
        }

        // Check if the locationList that we handle contains the other end
        // Ex : path = "AB", location="A" => otherEnd = "B"
        Location* otherEnd = getOtherEnd(pathData, location);

        // Ex : handledLocationList = {EF, GH} and other End = B
        bool handledLocationListContainsLocation = containsLocation(navigation.locationList, otherEnd, true);
        if (!handledLocationListContainsLocation) {
            setBit(navigation.outgoingPaths, i, true);
        }
    }
}

/** 
 * Returns the cost associated to location.
 */
unsigned int getCost(Location* location) {
    if (location->tmpCost == NO_COMPUTED_COST) {
        return MAX_COST;
    }
    return location->tmpCost;
}

/**
 * Change the cost associated to the location.
 */
void setCost(Location* location, unsigned int cost) {
    location->tmpCost = cost;
}

/**
 * @private
 * Search the nearest node in terms of cost
 */
Location* extractMinCostLocation(void) {
    // Search the nearest node in terms of cost
    Location* result = NULL;
    unsigned int minCost = MAX_COST;
    int size = navigation.locationList->size;
    int i;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(navigation.locationList, i);
        // we only manage only unhandled location point
        if (location->tmpHandled) {
            continue;
        }
        #ifdef NAVIGATION_DEBUG 
            appendString(getInfoOutputStreamLogger(), "\t");
            printLocation(getInfoOutputStreamLogger(), location);
        #endif

        // get the cost
        unsigned int cost = getCost(location);
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

unsigned int computeBestPath(Location* start, Location* end) {
    unsigned int result = 0;

    // not necessary because handledLocationList elements are removed from unhandled to handled.
    // we can not have doublon.
    // unhandledLocationList.set = true;    
    // handledLocationList.set = true;

    clearLocationTmpInfo(navigation.locationList);
    Location* location1;

    start->tmpCost = 0;
    #ifdef NAVIGATION_DEBUG
        printLocation(getInfoOutputStreamLogger(), start);
    #endif

    unsigned int size = navigation.locationList->size;
    unsigned int i = 0;
    for (i = 0; i < size; i++) {
        // search the nearest node of the nodeList
        #ifdef NAVIGATION_DEBUG
            appendString(getInfoOutputStreamLogger(), "extractMinCostLocation\n");
        #endif
        location1 = extractMinCostLocation();

        #ifdef NAVIGATION_DEBUG
            appendString(getInfoOutputStreamLogger(), "bestLocation=");
            printLocation(getInfoOutputStreamLogger(), location1);
        #endif

        // List of path going to the node (location)
        updateOutgoingPaths(location1);

        unsigned int i;
        unsigned int size = navigation.paths->size;

        #ifdef NAVIGATION_DEBUG
            printLocationList(getInfoOutputStreamLogger(), "locations=", &locationList);
            printPathList(getInfoOutputStreamLogger(), "allPaths=", &paths);
        #endif

        // loop on all outgoingPath
        for (i = 0; i < size; i++) {
            bool outgoing = getBit(navigation.outgoingPaths, i);
            if (!outgoing) {
                continue;
            }

            // Do not use paths that are not available
            bool available = getPathAvailability(i);
            if (!available) {
                continue;
            }

            PathData* pathData = getPath(navigation.paths, i);
            Location* location2 = getOtherEnd(pathData, location1);
            unsigned int costLocation1 = getCost(location1);
            unsigned int costLocation2 = getCost(location2);
            
            #ifdef NAVIGATION_DEBUG
                appendStringAndDec(getInfoOutputStreamLogger(), "costLocation1:", costLocation1);
                appendStringAndDec(getInfoOutputStreamLogger(), ", costLocation2:", costLocation2);
                println(getInfoOutputStreamLogger());
            #endif

            // getOtherEnd called the current fonction to fill path information
            // so we can use pathData without problem.
            unsigned int cost = costLocation1 + pathData->cost;

            if (!available) {
                cost += COST_UNAVAILABLE_PATH;
            }

            if (cost < costLocation2) {
                // Affectation de la distance absolue du noeud
                setCost(location2, cost);
                location2->tmpPreviousLocation = location1;
                location1->resultNextLocation = location2;
            }
        }        
    }
    // store best cost
    result = getCost(end);
    location1 = end;
    
    return result;
}

void printNavigationContext(OutputStream* outputStream) {
    printLocationListTable(outputStream, navigation.locationList);
    printPathList(outputStream, "paths:", navigation.paths);
}

void setPathAvailability(int index, bool value) {
    setBit(navigation.availablePaths, index, value);
}

void resetAllPathsAsAvailable(void) {
    clearBitList(navigation.availablePaths, true);
}

bool getPathAvailability(int index) {
    bool result = getBit(navigation.availablePaths, index);
    return result;
}
