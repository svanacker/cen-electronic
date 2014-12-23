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

/** All locations. */
static LocationList locations;

/** All paths. */
static PathList paths;

static unsigned int bitListValues[BIT_LIST_NAVIGATION_ARRAY_LENGTH];
static BitList outgoingPaths;

static unsigned int availablePathsBitListValues[BIT_LIST_NAVIGATION_ARRAY_LENGTH];
static BitList availablePaths;

void initNavigation(void) {
    clearLocationList(&locations);
    clearPathList(&paths);
    initBitList(&outgoingPaths, (unsigned int(*)[]) &bitListValues, BIT_LIST_NAVIGATION_ARRAY_LENGTH);
    initBitList(&availablePaths, (unsigned int(*)[]) &availablePathsBitListValues, BIT_LIST_NAVIGATION_ARRAY_LENGTH);
    clearBitList(&availablePaths, true);
}

LocationList* getNavigationLocationList(void) {
    return &locations;
}

PathList* getNavigationPathList(void) {
    return &paths;
}

void addNavigationLocation(Location* location, char* name, int x, int y) {
    addLocation(&locations, location, name, x, y);
}

void addNavigationPath(PathDataFunction* pathDataFunction) {
    addPath(&paths, pathDataFunction); 
}

void updateOutgoingPaths(Location* location) {
    clearBitList(&outgoingPaths, false);
    int i;
    int pathSize = getPathCount(&paths);
    for (i = 0; i < pathSize; i++) {
        PathDataFunction* pathDataFunction = getPath(&paths, i);

        // For example : location = "A", check if path contains("A") : "AB" contains "A", but "DE" not
        bool pathContainsLocationBool = pathContainsLocation(pathDataFunction, location);

        if (!pathContainsLocationBool) {
            continue;
        }

        // Check if the locationList that we handle contains the other end
        // Ex : path = "AB", location="A" => otherEnd = "B"
        Location* otherEnd = getOtherEnd(pathDataFunction, location);

        // Ex : handledLocationList = {EF, GH} and other End = B
        bool handledLocationListContainsLocation = containsLocation(&locations, otherEnd, true);
        if (!handledLocationListContainsLocation) {
            setBit(&outgoingPaths, i, true);
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
void setCost(Location* location, int cost) {
    location->tmpCost = cost;
}

/**
 * @private
 * Search the nearest node in terms of cost
 */
Location* extractMinCostLocation(void) {
    // Search the nearest node in terms of cost
    Location* result = NULL;
    int minCost = MAX_COST;
    int size = locations.size;
    int i;
    for (i = 0; i < size; i++) {
        Location* location = locations.locations[i];
        // we only manage only unhandled location point
        if (location->tmpHandled) {
            continue;
        }
        #ifdef NAVIGATION_DEBUG 
            appendString(getOutputStreamLogger(INFO), "\t");
            printLocation(getOutputStreamLogger(INFO), location);
        #endif

        // get the cost
        int cost = getCost(location);
        #ifdef NAVIGATION_DEBUG
            appendStringAndDec(getOutputStreamLogger(INFO), "\tcost:", cost);
            println(getOutputStreamLogger(INFO));
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

int computeBestPath(LocationList* outLocationList, Location* start, Location* end) {
    int result = 0;
    clearLocationList(outLocationList);

    // not necessary because handledLocationList elements are removed from unhandled to handled.
    // we can not have doublon.
    // unhandledLocationList.set = true;    
    // handledLocationList.set = true;

    clearLocationTmpInfo(&locations);
    Location* location1;

    start->tmpCost = 0;
    #ifdef NAVIGATION_DEBUG
        printLocation(getOutputStreamLogger(INFO), start);
    #endif

    int size = locations.size;
    int i = 0;
    for (i = 0; i < size; i++) {
        // search the nearest node of the nodeList
        #ifdef NAVIGATION_DEBUG
            appendString(getOutputStreamLogger(INFO), "extractMinCostLocation\n");
        #endif
        location1 = extractMinCostLocation();

        #ifdef NAVIGATION_DEBUG
            appendString(getOutputStreamLogger(INFO), "bestLocation=");
            printLocation(getOutputStreamLogger(INFO), location1);
        #endif

        // List of path going to the node (location)
        updateOutgoingPaths(location1);

        int i;
        int size = paths.size;

        #ifdef NAVIGATION_DEBUG
            printLocationList(getOutputStreamLogger(INFO), "locations=", &locations);
            printPathList(getOutputStreamLogger(INFO), "allPaths=", &paths);
        #endif

        // loop on all outgoingPath
        for (i = 0; i < size; i++) {
            bool outgoing = getBit(&outgoingPaths, i);            
            if (!outgoing) {
                continue;
            }

            // Do not use paths that are not available
            bool available = getPathAvailability(i);
            if (!available) {
                continue;
            }

            PathDataFunction* pathDataFunction = getPath(&paths, i);
            pathDataFunction();
            Location* location2 = getOtherEnd(pathDataFunction, location1);
            int costLocation1 = getCost(location1);
            int costLocation2 = getCost(location2);
            
            #ifdef NAVIGATION_DEBUG
                appendStringAndDec(getOutputStreamLogger(INFO), "costLocation1:", costLocation1);
                appendStringAndDec(getOutputStreamLogger(INFO), ", costLocation2:", costLocation2);
                println(getOutputStreamLogger(INFO));
            #endif

            // getOtherEnd called the current fonction to fill path information
            // so we can use pathData without problem.
            int cost = costLocation1 + getTmpPathData()->cost;

            if (!available) {
                cost += COST_UNAVAILABLE_PATH;
            }

            if (cost < costLocation2) {
                // Affectation de la distance absolue du noeud
                setCost(location2, cost);
                location2->tmpPreviousLocation = location1;
            }
        }        
    }
    // store best cost
    result = getCost(end);
    location1 = end;
    
    while ((location1 != start) && (location1 != NULL)) {
        addFilledLocation(outLocationList, location1);
        location1 = location1->tmpPreviousLocation;
    }
    addFilledLocation(outLocationList, start);

    reverseLocationList(outLocationList);

    return result;
}

void printNavigationContext(OutputStream* outputStream) {
    printLocationList(outputStream, "locations:", &locations);
    printPathList(outputStream, "paths:", &paths);
}

void setPathAvailability(int index, bool value) {
    setBit(&availablePaths, index, value);
}

void resetAllPathsAsAvailable(void) {
    clearBitList(&availablePaths, true);
}

bool getPathAvailability(int index) {
    return getBit(&availablePaths, index);
}
