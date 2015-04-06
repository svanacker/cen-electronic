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
    pathList->locations = pathListArray;
    pathList->maxSize = pathListSize;
}

void clearPathList(PathList* pathList, PathData(*pathListArray)[], unsigned int pathListSize) {
    pathList->size = 0;
}

PathData* addPath(PathList* pathList) {
    if (&pathList == NULL || pathList->maxSize == 0) {
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

PathData* getPath(PathList* pathList, int index) {
    if (&pathList == NULL || pathList->maxSize == 0) {
        writeError(PATH_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= pathList->maxSize) {
        writeError(PATH_LIST_INDEX_OUT_OF_BOUNDS);
        return NULL;
    }
    PathData* result = (PathData*)pathList->locations;
    // we don't need use sizeof because our pointer is a PathData* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

PathData* getPathOfLocations(PathList* pathList, Location* location1, Location* location2, bool* reversed) {
    unsigned int i;
    unsigned int size = pathList->size;
    for (i = 0; i < size; i++) {
        PathData* pathData = getPath(pathList, i);
        Location* pathLocation1 = pathData->location1;
        Location* pathLocation2 = pathData->location2;
        // same order
        if (locationEquals(pathLocation1, location1) && locationEquals(pathLocation2, location2)) {
            *reversed = false;
            return pathData;
        }
        // inverse order
        if (locationEquals(pathLocation1, location2) && locationEquals(pathLocation2, location1)) {
            *reversed = true;
            return pathData;
        }
    }
    *reversed = false;
    return NULL;
}

unsigned int getPathCount(PathList* pathList) {
    return pathList->size;
}

void printPathList(OutputStream* outputStream, char* pathListName, PathList* pathList) {
    unsigned int i;
    unsigned int size = pathList->size;
    appendKeyAndName(outputStream, "PathList:", pathListName);
    appendStringAndDec(outputStream, ", size=", pathList->size);

    println(outputStream);
    for (i = 0; i < size; i++) {
        PathData* pathData = getPath(pathList, i);
        printPath(outputStream, pathData);
    }
}
