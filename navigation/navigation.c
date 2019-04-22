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

void initNavigation(Navigation* navigation, LocationList* locationList, PathList* pathList, OutgoingPathList* tmpOutgoingPaths, BitList* availablePaths) {
    navigation->locationList = locationList;
    navigation->paths = pathList;
    navigation->tmpOutgoingPaths = tmpOutgoingPaths;
    navigation->availablePaths = availablePaths;
    
    // Init
    clearLocationList(navigation->locationList);
    clearPathList(navigation->paths);
    clearOutgoingPathList(navigation->tmpOutgoingPaths);
    clearBitList(navigation->availablePaths, true);
}

LocationList* getNavigationLocationList(Navigation* navigation) {
    return navigation->locationList;
}

PathList* getNavigationPathList(Navigation* navigation) {
    return navigation->paths;
}

Location* addNavigationLocation(Navigation* navigation, char* name, float x, float y) {
    LocationList* locationList = navigation->locationList;
    Location* result = addNamedLocation(locationList, name, x, y);
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
    initPathData(pathData, location1, location2, cost, controlPointDistance1, controlPointDistance2, angle1, angle2, accelerationFactor, speedFactor);
    return pathData;
}


void setPathAvailability(Navigation* navigation, int index, bool value) {
    setBit(navigation->availablePaths, index, value);
}

void resetAllPathsAsAvailable(Navigation* navigation) {
    clearBitList(navigation->availablePaths, true);
}

bool getPathAvailability(Navigation* navigation, int index) {
    bool result = getBit(navigation->availablePaths, index);
    return result;
}
