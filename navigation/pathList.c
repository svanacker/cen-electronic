#include <stdlib.h>

#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/error/error.h"

void initPathList(PathList* pathList, PathData(*pathListArray)[], unsigned int pathListSize) {
    if (pathList == NULL) {
        writeError(PATH_LIST_NULL);
        return;
    }
    pathList->paths = pathListArray;
    pathList->maxSize = pathListSize;
}

void clearPathList(PathList* pathList) {
    pathList->size = 0;
}

PathData* addPath(PathList* pathList) {
    if (pathList == NULL || pathList->maxSize == 0) {
        writeError(PATH_LIST_NOT_INITIALIZED);
        return NULL;
    }

    unsigned int size = pathList->size;
    if (size < pathList->maxSize) {
        PathData* pathData = getPath(pathList, size);
        pathList->size++;
        return pathData;
    }
    else {
        writeError(TOO_MUCH_PATHS);
        return NULL;
    }
}

PathData* addFilledPath(PathList* pathList,
						LocationList* locationList,
					    char* locationName1, char* locationName2, 
						float cost, 
						float controlPointDistance1, 
                        float controlPointDistance2, 
						float angleRadian1, 
                        float angleRadian2,
						unsigned char accelerationFactor, unsigned char speedFactor,
						bool mustGoBackward) {
	PathData* result = addPath(pathList);

	Location* location1 = findLocationByStringName(locationList, locationName1);
	result->location1 = location1;

	Location* location2 = findLocationByStringName(locationList, locationName2);
	result->location2 = location2;

	result->cost = cost;
	result->controlPointDistance1 = controlPointDistance1;
	result->controlPointDistance2 = controlPointDistance2;
	result->angleRadian1 = angleRadian1;
	result->angleRadian2 = angleRadian2;
	result->accelerationFactor = accelerationFactor;
	result->speedFactor = speedFactor;
	result->mustGoBackward = mustGoBackward;

	return result;
}

PathData* getPath(PathList* pathList, unsigned int index) {
    if (pathList == NULL || pathList->maxSize == 0) {
        writeError(PATH_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= pathList->maxSize) {
        writeError(PATH_LIST_INDEX_OUT_OF_BOUNDS);
        return NULL;
    }
    PathData* result = (PathData*)pathList->paths;
    // we don't need use sizeof because our pointer is a PathData* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

PathData* getPathOfLocations(PathList* pathList, Location* location1, Location* location2) {
    unsigned int i;
    unsigned int size = pathList->size;
    for (i = 0; i < size; i++) {
        PathData* pathData = getPath(pathList, i);
        Location* pathLocation1 = pathData->location1;
        Location* pathLocation2 = pathData->location2;
        // The path must be on the same order than the 2 locations
        if (locationEquals(pathLocation1, location1) && locationEquals(pathLocation2, location2)) {
            return pathData;
        }
    }
    return NULL;
}

unsigned int getPathCount(PathList* pathList) {
    return pathList->size;
}

// OBSTACLE MANAGEMENT

void pathListDecreaseObstacleCost(PathList* pathList) {
    unsigned int i;
    unsigned int size = pathList->size;
    for (i = 0; i < size; i++) {
        PathData* pathData = getPath(pathList, i);
        decreaseObstacleCost(pathData);
    }
}
