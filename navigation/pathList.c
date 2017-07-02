#include <stdlib.h>

#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

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
						unsigned int cost, 
						int controlPointDistance1, int controlPointDistance2, 
						int angle1, int angle2, 
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
	result->angle1 = angle1;
	result->angle2 = angle2;
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

// DEBUG

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

#define PATH_LIST_NAME_1_COLUMN_LENGTH                       11
#define PATH_LIST_NAME_2_COLUMN_LENGTH                       11
#define PATH_LIST_NAME_HEX_1_COLUMN_LENGTH                   12
#define PATH_LIST_NAME_HEX_2_COLUMN_LENGTH                   12
#define PATH_LIST_COST_COLUMN_LENGTH                         5
#define PATH_LIST_CP1_COLUMN_LENGTH                          5
#define PATH_LIST_CP2_COLUMN_LENGTH                          5
#define PATH_LIST_ANGLE_1_COLUMN_LENGTH                      6
#define PATH_LIST_ANGLE_2_COLUMN_LENGTH                      6
#define PATH_LIST_ACCELERATION_FACTOR_COLUMN_LENGTH          4
#define PATH_LIST_SPEED_FACTOR_COLUMN_LENGTH                 6
#define PATH_LIST_GO_BACK_COLUMN_LENGTH                      5
#define PATH_LIST_LAST_COLUMN_LENGTH                         1

/**
* Private.
*/
void printPathListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "location 1", PATH_LIST_NAME_1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "location 2", PATH_LIST_NAME_2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "loc 1 Hex", PATH_LIST_NAME_HEX_1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "loc 2 Hex", PATH_LIST_NAME_HEX_2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "cost", PATH_LIST_COST_COLUMN_LENGTH);
	appendStringHeader(outputStream, "cp 1", PATH_LIST_CP1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "cp 2", PATH_LIST_CP2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "ang 1", PATH_LIST_ANGLE_1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "ang 2", PATH_LIST_ANGLE_2_COLUMN_LENGTH);

	appendStringHeader(outputStream, "Acc", PATH_LIST_ACCELERATION_FACTOR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Speed", PATH_LIST_SPEED_FACTOR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Back", PATH_LIST_GO_BACK_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, PATH_LIST_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printPathTable(OutputStream* outputStream, PathData* pathData) {
	appendFixedCharArrayTableData(outputStream, &(pathData->location1->name), PATH_LIST_NAME_1_COLUMN_LENGTH);
	appendFixedCharArrayTableData(outputStream, &(pathData->location2->name), PATH_LIST_NAME_2_COLUMN_LENGTH);
	appendHexFixedCharArrayTableData(outputStream, &(pathData->location1->name), PATH_LIST_NAME_HEX_1_COLUMN_LENGTH);
	appendHexFixedCharArrayTableData(outputStream, &(pathData->location2->name), PATH_LIST_NAME_HEX_2_COLUMN_LENGTH);
	appendDecTableData(outputStream, pathData->cost, PATH_LIST_COST_COLUMN_LENGTH);
	appendDecTableData(outputStream, pathData->controlPointDistance1, PATH_LIST_CP1_COLUMN_LENGTH);
	appendDecTableData(outputStream, pathData->controlPointDistance2, PATH_LIST_CP2_COLUMN_LENGTH);
	appendDecTableData(outputStream, pathData->angle1, PATH_LIST_ANGLE_1_COLUMN_LENGTH);
	appendDecTableData(outputStream, pathData->angle2, PATH_LIST_ANGLE_2_COLUMN_LENGTH);
	appendDecTableData(outputStream, pathData-> accelerationFactor, PATH_LIST_ACCELERATION_FACTOR_COLUMN_LENGTH);
	appendDecTableData(outputStream, pathData->speedFactor, PATH_LIST_SPEED_FACTOR_COLUMN_LENGTH);
	appendBoolTableData(outputStream, pathData->mustGoBackward, PATH_LIST_GO_BACK_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PATH_LIST_LAST_COLUMN_LENGTH);
}

void printPathListTable(OutputStream* outputStream, PathList* pathList) {
	int size = pathList->size;
	printPathListHeader(outputStream);
	int i;
	for (i = 0; i < size; i++) {
		PathData* pathData = getPath(pathList, i);
		printPathTable(outputStream, pathData);
	}
	appendTableHeaderSeparatorLine(outputStream);
}

// TESTS DATA

// Tests Data

void addPathListTestsData(PathList* pathList, LocationList* locationList) {
	addFilledPath(pathList, locationList, "STAR", "OBJ1", 10, 20, 30, 15, 25, 2, 2, false);
	addFilledPath(pathList, locationList, "OBJ1", "OBJ2", 15, 10, 15, 10, 20, 3, 2, false);
	addFilledPath(pathList, locationList, "OBJ2", "END", 10, 17, 5, 5, 5, 1, 2, false);
}
