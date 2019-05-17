#include <stdlib.h>
#include <string.h>

#include "locationListDebug.h"
#include "locationList.h"
#include "location.h"

#include "../common/2d/2d.h"

#include "../common/error/error.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

#include "../common/string/cenString.h"

// DEBUG AS TABLE

#define LOCATION_LIST_LOCATION_INDEX_COLUMN_LENGTH           4
#define LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH            8 
#define LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH        9
#define LOCATION_LIST_LOCATION_X_COLUMN_LENGTH               8
#define LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH               8
#define LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH          8
#define LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH          8
#define LOCATION_LIST_LOCATION_TMP_COST_COLUMN_LENGTH        8
#define LOCATION_LIST_LOCATION_NEXT_COLUMN_LENGTH            8

#define LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH            0

/**
* Private.
*/
void printLocationListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
    // Line Header 1
	appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Idx", LOCATION_LIST_LOCATION_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "name", LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "name", LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "x", LOCATION_LIST_LOCATION_X_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y", LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH);
	appendStringHeader(outputStream, "x Hex", LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y Hex", LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Tmp", LOCATION_LIST_LOCATION_TMP_COST_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Next", LOCATION_LIST_LOCATION_NEXT_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH);
    // Line Header 2
    appendStringHeader(outputStream, "", LOCATION_LIST_LOCATION_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(hex)", LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", LOCATION_LIST_LOCATION_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Cost", LOCATION_LIST_LOCATION_TMP_COST_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Loc", LOCATION_LIST_LOCATION_NEXT_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);
}

void printLocationTable(OutputStream* outputStream, Location* location, unsigned int locationIndex) {
    appendDecTableData(outputStream, locationIndex, LOCATION_LIST_LOCATION_INDEX_COLUMN_LENGTH);
    if (location != NULL) {
        appendFixedCharArrayTableData(outputStream, &(location->name), LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
        appendHexFixedCharArrayTableData(outputStream, &(location->name), LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "NULL", LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
        appendStringTableData(outputStream, "NULL", LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH);
    }
	appendDecfTableData(outputStream, location->x, LOCATION_LIST_LOCATION_X_COLUMN_LENGTH);
	appendDecfTableData(outputStream, location->y, LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH);
	appendHexFloat4TableData(outputStream, location->x, POSITION_DIGIT_MM_PRECISION, LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, location->y, POSITION_DIGIT_MM_PRECISION, LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH);

    appendDecfTableData(outputStream, location->computedCost, LOCATION_LIST_LOCATION_TMP_COST_COLUMN_LENGTH);

    // Next
    if (location->computedNextLocation != NULL && location->computedNextLocation->name != NULL) {
        appendFixedCharArrayTableData(outputStream, &(location->computedNextLocation->name), LOCATION_LIST_LOCATION_NEXT_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "NULL", LOCATION_LIST_LOCATION_NEXT_COLUMN_LENGTH);
    }
	appendEndOfTableColumn(outputStream, LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH);
}

void printLocationListTable(OutputStream* outputStream, LocationList* locationList) {
	int locationIndex;
	int size = locationList->size;
	printLocationListHeader(outputStream);
	for (locationIndex = 0; locationIndex < size; locationIndex++) {
		Location* location = getLocation(locationList, locationIndex);
		printLocationTable(outputStream, location, locationIndex);
        if (locationIndex % 5 == 4) {
            appendTableHeaderSeparatorLine(outputStream);
        }
	}
	appendTableHeaderSeparatorLine(outputStream);
}

unsigned int appendLocationLinkedPath(OutputStream* outputStream, Location* startPoint) {
    unsigned int result = 0;
    Location* currentLocation = startPoint;

    while (currentLocation != NULL) {
        // Avoid to add an arrow at the first time
        if (result != 0) {
            result += appendString(outputStream, "->");
        }
        // Write the name of the location
        result += appendFixedCharArray(outputStream, &(currentLocation->name));
        currentLocation = currentLocation->computedNextLocation;
    }
    return result;
}

// Tests Data

void addLocationListTestsData(LocationList* locationList) {
	addNamedLocation(locationList, "STAR", "STAR", 10, 20);
	addNamedLocation(locationList, "OBJ1", "OBJ 1", 200, 300);
	addNamedLocation(locationList, "OBJ2", "OBJ 2", 400, 700);
	addNamedLocation(locationList, "END", "END", 1500, 2000);
}
