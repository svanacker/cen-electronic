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
			 Location* location1,
			 Location* location2, 
			 int cost,
			 int controlPointDistance1,
			 int controlPointDistance2,
			 int angle1,
			 int angle2,
			 int speedFactor) {
	path->location1 = location1;
	path->location2 = location2;
	path->controlPointDistance1 = controlPointDistance1;
	path->controlPointDistance2 = controlPointDistance2;
	path->angle1 = angle1;
	path->angle2 = angle2;
	path->cost = cost;
	path->speedFactor = speedFactor;
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
