#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "../common/math/bitList.h"
#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"

struct Navigation;
typedef struct Navigation Navigation;

/**
* Contains all elements used by the system to find the paths. 
*/
struct Navigation {
    // All points
    LocationList* locationList;
    // All Paths
    PathList* paths;
    // Outgoing Paths
    BitList* outgoingPaths;
    // Available Paths
    BitList* availablePaths;
};

#define BIT_LIST_NAVIGATION_ARRAY_LENGTH    (MAX_PATH / BITS_COUNT_IN_UNSIGNED_INT) + 1

#define COST_UNAVAILABLE_PATH 2000

/**
 * Initialize the navigation system.
 */
void initNavigation(LocationList* locationList, PathList* pathList, BitList* outgoingPaths, BitList* availablePaths);

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
PathData* addNavigationPath(
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
unsigned int computeBestPath(Location* start,
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
