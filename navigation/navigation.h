#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"

#define    BIT_LIST_NAVIGATION_ARRAY_LENGTH    (MAX_PATH / BITS_COUNT_IN_UNSIGNED_INT) + 1

#define COST_UNAVAILABLE_PATH 2000

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
Location* addNavigationLocation(char* name, int x, int y);

/**
 * Add the path to the navigation graph.
 */
void addNavigationPath(PathData* pathData,
    Location* location1,
    Location* location2,
    int cost,
    int controlPointDistance1,
    int controlPointDistance2,
    int angle1,
    int angle2,
    unsigned char accelerationFactor,
    unsigned char speedFactor);

/**
 * Computes the path.
 * @param start startPoint the start point will have a linked pointer on the next point to reach recursively to the end point
 * @param end endPoint
 * @return the cost to reach the best Path
 */
int computeBestPath(Location* start,
                    Location* end);

void printNavigationContext(OutputStream* outputStream);

// PATH AVAILABILITY

/** 
 * Sets the availability of the path at the specified index.
 * @param index the index of the path
 * @param value the availability of the path
 */
void setPathAvailability(int index, bool value);

bool getPathAvailability(int index);

/**
 * Reset the status of availability of all paths to Available.
 */
void resetAllPathsAsAvailable();

#endif
