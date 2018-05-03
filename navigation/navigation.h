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
void initNavigation(Navigation* navigation, LocationList* locationList, PathList* pathList, BitList* outgoingPaths, BitList* availablePaths);

/**
 * Returns the navigation location List field.
 */
LocationList* getNavigationLocationList(Navigation* navigation);

/**
 * Returns the navigation path List field
 */
PathList* getNavigationPathList(Navigation* navigation);

/**
 * Add the location to the navigation graph.
 */
Location* addNavigationLocation(Navigation* navigation, char* name, float x, float y);

/**
 * Add the path to the navigation graph.
 */
PathData* addNavigationPath(Navigation* navigation,
    Location* location1,
    Location* location2,
    float cost,
    float controlPointDistance1,
    float controlPointDistance2,
    float angle1,
    float angle2,
    float accelerationFactor,
    float speedFactor);

/**
 * Computes the path.
 * @param start startPoint the start point will have a linked pointer on the next point to reach recursively to the end point
 * @param end endPoint
 * @return the cost to reach the best Path
 */
float computeBestPath(Navigation* navigation, 
                             Location* start,
                             Location* end);


// PATH AVAILABILITY

/** 
 * Sets the availability of the path at the specified index.
 * @param index the index of the path
 * @param value the availability of the path
 */
void setPathAvailability(Navigation* navigation, int index, bool value);

bool getPathAvailability(Navigation* navigation, int index);

/**
 * Reset the status of availability of all paths to Available.
 */
void resetAllPathsAsAvailable(Navigation* navigation);

#endif
