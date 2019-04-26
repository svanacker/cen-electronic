#include "pathListDebug.h"
#include <stdlib.h>

#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

#include "../common/math/cenMath.h"

#include "../common/error/error.h"

#define PATH_LIST_INDEX_COLUMN_LENGTH                        3
#define PATH_LIST_NAME_1_COLUMN_LENGTH                       5
#define PATH_LIST_NAME_2_COLUMN_LENGTH                       5
#define PATH_LIST_NAME_HEX_1_COLUMN_LENGTH                   9
#define PATH_LIST_NAME_HEX_2_COLUMN_LENGTH                   9
#define PATH_LIST_COST_COLUMN_LENGTH                         7
#define PATH_LIST_OBSTACLE_COST_COLUMN_LENGTH                7
#define PATH_LIST_CP1_COLUMN_LENGTH                          7
#define PATH_LIST_CP2_COLUMN_LENGTH                          7
#define PATH_LIST_ANGLE_1_COLUMN_LENGTH                      6
#define PATH_LIST_ANGLE_2_COLUMN_LENGTH                      6
#define PATH_LIST_ACCELERATION_FACTOR_COLUMN_LENGTH          6
#define PATH_LIST_SPEED_FACTOR_COLUMN_LENGTH                 6
#define PATH_LIST_GO_BACK_COLUMN_LENGTH                      3
#define PATH_LIST_LAST_COLUMN_LENGTH                         0

/**
* Private.
*/
void printPathListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
    // Header Line 1
    appendStringHeader(outputStream, "Idx", PATH_LIST_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "loc.", PATH_LIST_NAME_1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "loc.", PATH_LIST_NAME_2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "loc.", PATH_LIST_NAME_HEX_1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "loc.", PATH_LIST_NAME_HEX_2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "cost", PATH_LIST_COST_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Obst.", PATH_LIST_OBSTACLE_COST_COLUMN_LENGTH);
    appendStringHeader(outputStream, "cp 1", PATH_LIST_CP1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "cp 2", PATH_LIST_CP2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "ang 1", PATH_LIST_ANGLE_1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "ang 2", PATH_LIST_ANGLE_2_COLUMN_LENGTH);

	appendStringHeader(outputStream, "Acc", PATH_LIST_ACCELERATION_FACTOR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Speed", PATH_LIST_SPEED_FACTOR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Ba", PATH_LIST_GO_BACK_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, PATH_LIST_LAST_COLUMN_LENGTH);

    // Header Line 2
    appendStringHeader(outputStream, "", PATH_LIST_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "1", PATH_LIST_NAME_1_COLUMN_LENGTH);
    appendStringHeader(outputStream, "2", PATH_LIST_NAME_2_COLUMN_LENGTH);
    appendStringHeader(outputStream, "1 Hex", PATH_LIST_NAME_HEX_1_COLUMN_LENGTH);
    appendStringHeader(outputStream, "2 Hex", PATH_LIST_NAME_HEX_2_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PATH_LIST_COST_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Cost", PATH_LIST_OBSTACLE_COST_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", PATH_LIST_CP1_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", PATH_LIST_CP2_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(deg)", PATH_LIST_ANGLE_1_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(deg)", PATH_LIST_ANGLE_2_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PATH_LIST_ACCELERATION_FACTOR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PATH_LIST_SPEED_FACTOR_COLUMN_LENGTH);
    appendStringHeader(outputStream, "ck", PATH_LIST_GO_BACK_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, PATH_LIST_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printPathTable(OutputStream* outputStream, PathData* pathData, unsigned int index) {
	appendDecTableData(outputStream, index, PATH_LIST_INDEX_COLUMN_LENGTH);
    Location* location1 = pathData->location1;
    Location* location2 = pathData->location2;

    // Location Name
    if (location1 != NULL) {
        appendFixedCharArrayTableData(outputStream, &(pathData->location1->name), PATH_LIST_NAME_1_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "", PATH_LIST_NAME_1_COLUMN_LENGTH);
    }
    if (location2 != NULL) {
        appendFixedCharArrayTableData(outputStream, &(pathData->location2->name), PATH_LIST_NAME_2_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "", PATH_LIST_NAME_2_COLUMN_LENGTH);
    }

    // Location Name in Hex
    if (location1 != NULL) {
        appendHexFixedCharArrayTableData(outputStream, &(pathData->location1->name), PATH_LIST_NAME_HEX_1_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "", PATH_LIST_NAME_HEX_1_COLUMN_LENGTH);
    }
    if (location2 != NULL) {
        appendHexFixedCharArrayTableData(outputStream, &(pathData->location2->name), PATH_LIST_NAME_HEX_2_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "", PATH_LIST_NAME_HEX_2_COLUMN_LENGTH);
    }
	appendDecfTableData(outputStream, pathData->cost, PATH_LIST_COST_COLUMN_LENGTH);
    appendDecfTableData(outputStream, pathData->obstacleCost, PATH_LIST_OBSTACLE_COST_COLUMN_LENGTH);
    appendDecfTableData(outputStream, pathData->controlPointDistance1, PATH_LIST_CP1_COLUMN_LENGTH);
	appendDecfTableData(outputStream, pathData->controlPointDistance2, PATH_LIST_CP2_COLUMN_LENGTH);
	appendDecfTableData(outputStream, radToDeg(pathData->angleRadian1), PATH_LIST_ANGLE_1_COLUMN_LENGTH);
	appendDecfTableData(outputStream, radToDeg(pathData->angleRadian2), PATH_LIST_ANGLE_2_COLUMN_LENGTH);
	appendDecfTableData(outputStream, pathData-> accelerationFactor, PATH_LIST_ACCELERATION_FACTOR_COLUMN_LENGTH);
	appendDecfTableData(outputStream, pathData->speedFactor, PATH_LIST_SPEED_FACTOR_COLUMN_LENGTH);
	appendBoolTableData(outputStream, pathData->mustGoBackward, PATH_LIST_GO_BACK_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PATH_LIST_LAST_COLUMN_LENGTH);
}

void printPathListTable(OutputStream* outputStream, PathList* pathList) {
	int size = pathList->size;
	printPathListHeader(outputStream);
	int i;
	for (i = 0; i < size; i++) {
		PathData* pathData = getPath(pathList, i);
		printPathTable(outputStream, pathData, i);
        if (i % 5 == 4) {
            appendTableHeaderSeparatorLine(outputStream);
        }
	}
	appendTableHeaderSeparatorLine(outputStream);
}

// TESTS DATA

void addPathListTestsData(PathList* pathList, LocationList* locationList) {
	addFilledPath(pathList, locationList, "STAR", "OBJ1", 10, 20, 30, 15, 25, 2, 2, false);
	addFilledPath(pathList, locationList, "OBJ1", "OBJ2", 15, 10, 15, 10, 20, 3, 2, false);
	addFilledPath(pathList, locationList, "OBJ2", "END", 10, 17, 5, 5, 5, 1, 2, false);
}
