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
			 Path* path, 
			 PathDataFunction* pathDataFunction) {
	path->pathDataFunction = pathDataFunction;
	addFilledPath(pathList, path);
}

void addFilledPath(PathList* pathList, Path* path) {
    unsigned char size = pathList->size;

	if (size < MAX_PATH) {
	    pathList->paths[size] = path;
	    pathList->size++;
	}
	else {
		writeError(TOO_MUCH_PATHS);
    }
}

Path* getPath(PathList* pathList, int index) {
    return pathList->paths[index];
}

Path* getPathOfLocations(PathList* pathList, Location* location1, Location* location2) {
	int i;
	int size = pathList->size;
	for (i = 0; i < size; i++) {
		Path* path = pathList->paths[i];
		path->pathDataFunction();
		Location* pathLocation1 = getTmpPathData()->location1;
		Location* pathLocation2 = getTmpPathData()->location2;
		// same order
		if (locationEquals(pathLocation1, location1) && locationEquals(pathLocation2, location2)) {
			return path;
		}
		// inverse order
		if (locationEquals(pathLocation1, location2) && locationEquals(pathLocation2, location1)) {
			return path;
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
		Path* path = pathList->paths[i];
		printPath(outputStream, path);
	}
}
