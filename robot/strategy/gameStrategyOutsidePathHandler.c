#include "gameStrategyOutsidePathHandler.h"

#include <stdlib.h>

#include "../../common/2d/2d.h"

#include "../../common/error/error.h"

#include "../../common/log/logger.h"

#include "../../navigation/locationList.h"
#include "../../navigation/pathList.h"

#include "../../navigation/navigation.h"

void gameStrategyCreateOutsideTemporaryPaths(GameStrategyContext* gameStrategyContext) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "gameStrategyCreateOutsideTemporaryPaths");
    }
    Navigation* navigation = gameStrategyContext->navigation;
    LocationList* locationList = navigation->locationList;
    float startAngleRadian = gameStrategyContext->robotAngleRadian;
    Point* robotPosition = gameStrategyContext->robotPosition;

    PathData* currentPath = gameStrategyContext->currentPath;
    if (currentPath == NULL) {
        writeError(PATH_NULL);
        return;
    }
    Location* locationToExclude = currentPath->location2;

    Location* robotLocation = addTemporaryLocation(locationList, robotPosition->x, robotPosition->y);
    addTemporaryPathListFromLocation(navigation, robotLocation, locationToExclude, startAngleRadian);
}

void gameStrategyClearOusideTemporaryPathsAndLocations(GameStrategyContext* gameStrategyContext) {
    if (isLoggerTraceEnabled()) {
        appendStringLN(getTraceOutputStreamLogger(), "gameStrategyClearOusideTemporaryPathsAndLocations");
    }
    Navigation* navigation = gameStrategyContext->navigation;
    LocationList* locationList = navigation->locationList;
    PathList* pathList = navigation->paths;
    pathListClearTemporaryPaths(pathList);
    locationListClearTemporaryLocations(locationList);
}