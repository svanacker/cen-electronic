#include <stdlib.h>

#include "navigation.h"
#include "location.h"
#include "locationList.h"
#include "locationListDebug.h"
#include "path.h"
#include "pathList.h"
#include "pathListDebug.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/math/bitList.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

// #define NAVIGATION_DEBUG

void initNavigation(Navigation* navigation, LocationList* locationList, PathList* pathList, OutgoingPathList* tmpOutgoingPaths) {
    navigation->locationList = locationList;
    navigation->paths = pathList;
    navigation->tmpOutgoingPaths = tmpOutgoingPaths;

    // Init
    clearLocationList(navigation->locationList);
    clearPathList(navigation->paths);
    clearOutgoingPathList(navigation->tmpOutgoingPaths);
}

LocationList* getNavigationLocationList(Navigation* navigation) {
    return navigation->locationList;
}

PathList* getNavigationPathList(Navigation* navigation) {
    return navigation->paths;
}

Location* addNavigationLocation(Navigation* navigation, char* name, char* label, float x, float y) {
    LocationList* locationList = navigation->locationList;
    Location* result = addNamedLocation(locationList, LOCATION_USAGE_TYPE_PERMANENT, name, label, x, y);
    return result;
}

PathData* addNavigationPath(Navigation* navigation,
        Location* location1,
        Location* location2,
        float cost,
        float controlPointDistance1,
        float controlPointDistance2,
        float angle1,
        float angle2,
        float accelerationFactor,
        float speedFactor) {
    PathData* pathData = addPath(navigation->paths);
    initPathData(pathData, PATH_DATA_USAGE_TYPE_PERMANENT, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
    return pathData;
}

// TEMPORARY PATHS

void addTemporaryPathListFromLocation(Navigation* navigation, Location* fromLocation, Location* excludeLocation, float startAngle) {
    PathList* pathList = navigation->paths;
    LocationList* locationList = navigation->locationList;
    unsigned int locationIndex;
    unsigned int locationListSize = locationList->size;
    for (locationIndex = 0; locationIndex < locationListSize; locationIndex++) {
        Location* location = getLocation(locationList, locationIndex);
        if (location->usageType != LOCATION_USAGE_TYPE_PERMANENT) {
            continue;
        }

        // We don't create a path with the same origin and target !
        if (location == fromLocation) {
            continue;
        }

        // We exclude the location where we would like to go !!
        if (location == excludeLocation) {
            continue;
        }

        startAngle = angleOfVector2(fromLocation->x, fromLocation->y, location->x, location->y);

        // if (location->usage == )
        float distance = distanceBetweenLocations(fromLocation, location);
        // We create a temporary Path, and we go to it slowly
        // TODO : Check for the cp1 & cp2 if we are going backward ???
        PathData* pathData = findPathDataToRecycleIfAny(pathList);
        if (pathData == NULL) {
            pathData = addNavigationPath(navigation, fromLocation, location, distance, 100.0f, 100.0f, startAngle, startAngle, 0.5f, 0.5f);
            // In every case, mark it as temporary
            pathData->usageType = PATH_DATA_USAGE_TYPE_TEMPORARY;
        } else {
            initPathData(pathData, PATH_DATA_USAGE_TYPE_TEMPORARY, fromLocation, location, distance, 100.0f, 100.0f, startAngle, startAngle, 0.5f, 0.5f);
        }
    }
}
