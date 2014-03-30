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
			 PathDataFunction* pathDataFunction) {
    unsigned char size = pathList->size;

	if (size < MAX_PATH) {
	    pathList->paths[size] = pathDataFunction;
	    pathList->size++;
	}
	else {
		writeError(TOO_MUCH_PATHS);
    }
}

PathDataFunction* getPath(PathList* pathList, int index) {
    return pathList->paths[index];
}

PathDataFunction* getPathOfLocations(PathList* pathList, Location* location1, Location* location2, bool* reversed) {
	int i;
	int size = pathList->size;
	for (i = 0; i < size; i++) {
		PathDataFunction* pathDataFunction = pathList->paths[i];
		pathDataFunction();
		Location* pathLocation1 = getTmpPathData()->location1;
		Location* pathLocation2 = getTmpPathData()->location2;
		// same order
		if (locationEquals(pathLocation1, location1) && locationEquals(pathLocation2, location2)) {
			*reversed = FALSE;
			return pathDataFunction;
		}
		// inverse order
		if (locationEquals(pathLocation1, location2) && locationEquals(pathLocation2, location1)) {
			*reversed = TRUE;
			return pathDataFunction;
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
		PathDataFunction* pathDataFunction = pathList->paths[i];
		printPath(outputStream, pathDataFunction);
	}
}
