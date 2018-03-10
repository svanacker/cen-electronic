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

#define LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH     12
#define LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH 12
#define LOCATION_LIST_LOCATION_X_COLUMN_LENGTH        10
#define LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH        10
#define LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH   10
#define LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH   10
#define LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH     37

/**
* Private.
*/
void printLocationListHeader(OutputStream* outputStream) {
	println(outputStream);
	// Table Header
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "name", LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "name (hex)", LOCATION_LIST_LOCATION_NAME_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "x (mm)", LOCATION_LIST_LOCATION_X_COLUMN_LENGTH);
	appendStringHeader(outputStream, "y (mm)", LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH);
	appendStringHeader(outputStream, "xHex (mm)", LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH);
	appendStringHeader(outputStream, "xHex (mm)", LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printLocationTable(OutputStream* outputStream, Location* location) {
	appendFixedCharArrayTableData(outputStream, &(location->name), LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
	appendHexFixedCharArrayTableData(outputStream, &(location->name), LOCATION_LIST_LOCATION_NAME_COLUMN_LENGTH);
	appendDecfTableData(outputStream, location->x, LOCATION_LIST_LOCATION_X_COLUMN_LENGTH);
	appendDecfTableData(outputStream, location->y, LOCATION_LIST_LOCATION_Y_COLUMN_LENGTH);
	appendHexFloat4TableData(outputStream, location->x, POSITION_DIGIT_MM_PRECISION, LOCATION_LIST_LOCATION_X_HEXA_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, location->y, POSITION_DIGIT_MM_PRECISION, LOCATION_LIST_LOCATION_Y_HEXA_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, LOCATION_LIST_LOCATION_LAST_COLUMN_LENGTH);
}

void printLocationListTable(OutputStream* outputStream, LocationList* locationList) {
	int i;
	int size = locationList->size;
	printLocationListHeader(outputStream);
	for (i = 0; i < size; i++) {
		Location* location = getLocation(locationList, i);
		printLocationTable(outputStream, location);
	}
	appendTableHeaderSeparatorLine(outputStream);
}

// Tests Data

void addLocationListTestsData(LocationList* locationList) {
	addNamedLocation(locationList, "STAR", 10, 20);
	addNamedLocation(locationList, "OBJ1", 200, 300);
	addNamedLocation(locationList, "OBJ2", 400, 700);
	addNamedLocation(locationList, "END", 1500, 2000);
}

void printLocationLinkedPath(OutputStream* outputStream, Location* startPoint) {
    Location* currentLocation = startPoint;

    while (startPoint != NULL) {
        printLocation(outputStream, currentLocation);
        startPoint = currentLocation->resultNextLocation;
    }
}
