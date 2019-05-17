#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "../common/math/bitList.h"
#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"
#include "outgoingPathList.h"
#include "outgoingPath.h"

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
    // Outgoing Paths (tmp variable because associated to a computed Location)
    OutgoingPathList* tmpOutgoingPaths;
};

#define BIT_LIST_NAVIGATION_ARRAY_LENGTH    (MAX_PATH / BITS_COUNT_IN_UNSIGNED_INT) + 1

#define COST_UNAVAILABLE_PATH 2000

/**
 * Initialize the navigation system.
 * @param navigation the wrapper object
 * @param locationList the list of location
 * @param pathList the list of Path with information on how to join them (often via a bSplineCurve)
 * @param tmpOutgoingPaths a temporary object used to compute temporary for a specific Location, the list of outgoing Paths
 */
void initNavigation(Navigation* navigation, LocationList* locationList, PathList* pathList, OutgoingPathList* tmpOutgoingPaths);

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
Location* addNavigationLocation(Navigation* navigation, char* name, char* label, float x, float y);

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

#endif
