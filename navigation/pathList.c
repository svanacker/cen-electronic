#include <stdlib.h>

#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/error/error.h"

void clearPathList(PathList* pathList) {
    pathList->size = 0;
}

void addPath(PathList* pathList,
             PathData* pathData) {
    unsigned char size = pathList->size;

    if (size < MAX_PATH) {
        pathList->paths[size] = pathData;
        pathList->size++;
    }
    else {
        writeError(TOO_MUCH_PATHS);
    }
}

PathData* getPath(PathList* pathList, int index) {
    return pathList->paths[index];
}

PathData* getPathOfLocations(PathList* pathList, Location* location1, Location* location2, bool* reversed) {
    int i;
    int size = pathList->size;
    for (i = 0; i < size; i++) {
        PathData* pathData = pathList->paths[i];
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
    return NULL;
}

int getPathCount(PathList* pathList) {
    return pathList->size;
}

void printPathList(OutputStream* outputStream, char* pathListName, PathList* pathList) {
    int i;
    int size = pathList->size;
    appendKeyAndName(outputStream, "PathList:", pathListName);
    appendStringAndDec(outputStream, ", size=", pathList->size);

    println(outputStream);
    for (i = 0; i < size; i++) {
        PathData* pathData = pathList->paths[i];
        printPath(outputStream, pathData);
    }
}
