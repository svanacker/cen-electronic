#include "navigationDebug.h"

#include "navigation.h"
#include "navigationComputer.h"
#include "locationListDebug.h"
#include "pathListDebug.h"

#include "../common/io/outputStream.h"

#include "pathListDebug.h"
#include <stdlib.h>

#include "locationList.h"
#include "location.h"
#include "pathList.h"
#include "path.h"
#include "outgoingPathList.h"
#include "outgoingPath.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"
#include "../common/io/printTableWriter.h"

#include "../common/math/cenMath.h"

#include "../common/error/error.h"

#define NAVIGATION_DEBUG_LOCATION_INDEX_COLUMN_LENGTH                       5
#define NAVIGATION_DEBUG_LOCATION_NAME_COLUMN_LENGTH                        8
#define NAVIGATION_DEBUG_LIST_OF_OUTGOING_PATH                             92
#define NAVIGATION_DEBUG_LIST_OF_LAST_COLUMN_LENGTH                         0

/**
 * Private.
 */
void printNavigationDebugLocationAndOutgoingPathListHeader(OutputStream* outputStream) {
    println(outputStream);
    // Table Header
    appendTableHeaderSeparatorLine(outputStream);
    // Header Line 1
    appendStringHeader(outputStream, "Loc.", NAVIGATION_DEBUG_LOCATION_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Loc.", NAVIGATION_DEBUG_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Outgoing Paths", NAVIGATION_DEBUG_LIST_OF_OUTGOING_PATH);
    appendEndOfTableColumn(outputStream, NAVIGATION_DEBUG_LIST_OF_LAST_COLUMN_LENGTH);

    // Header Line 2
    appendStringHeader(outputStream, "Id", NAVIGATION_DEBUG_LOCATION_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Name", NAVIGATION_DEBUG_LOCATION_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", NAVIGATION_DEBUG_LIST_OF_OUTGOING_PATH);
    appendEndOfTableColumn(outputStream, NAVIGATION_DEBUG_LIST_OF_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}

void printNavigationDebugLocationAndOutgoingPathList(OutputStream* outputStream, Navigation* navigation, Location* location, unsigned int index) {
    appendDecTableData(outputStream, index, NAVIGATION_DEBUG_LOCATION_INDEX_COLUMN_LENGTH);

    appendFixedCharArrayTableData(outputStream, &(location->name), NAVIGATION_DEBUG_LOCATION_NAME_COLUMN_LENGTH);
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    OutgoingPathList* tmpOutgoingPaths = navigation->tmpOutgoingPaths;
    unsigned int pathIndex = 0;
    unsigned int tmpOutgoingPathsSize = tmpOutgoingPaths->size;
    unsigned int charCount = 0;
    for (pathIndex = 0; pathIndex < tmpOutgoingPathsSize; pathIndex++) {
        OutgoingPathData* outgoingPathData = getOutgoingPath(tmpOutgoingPaths, pathIndex);
        if (pathIndex > 0) {
            charCount += appendString(outputStream, ", ");
        }

        PathData* pathData = outgoingPathData->pathData;

        // Location 1
        Location* location1 = pathData->location1;
        if (location1 != NULL) {
            charCount += appendFixedCharArray(outputStream, &(location1->name));
        } else {
            charCount += appendString(outputStream, "NULL");
        }

        charCount += appendString(outputStream, "->");

        // Location 2
        Location* location2 = pathData->location2;
        if (location2 != NULL) {
            charCount += appendFixedCharArray(outputStream, &(location2->name));
        } else {
            charCount += appendString(outputStream, "NULL");
        }
    }
    appendSpaces(outputStream, NAVIGATION_DEBUG_LIST_OF_OUTGOING_PATH - charCount);
    appendEndOfTableColumn(outputStream, NAVIGATION_DEBUG_LIST_OF_LAST_COLUMN_LENGTH);
}

void printNavigationDebugLocationAndOutgoingPathListTable(OutputStream* outputStream, Navigation* navigation) {
    printNavigationDebugLocationAndOutgoingPathListHeader(outputStream);
    int locationIndex;
    LocationList* locationList = navigation->locationList;
    int size = locationList->size;

    for (locationIndex = 0; locationIndex < size; locationIndex++) {
        Location* location = getLocation(locationList, locationIndex);
        updateOutgoingPaths(navigation, location);
        printNavigationDebugLocationAndOutgoingPathList(outputStream, navigation, location, locationIndex);
        if (locationIndex % 5 == 4) {
            appendTableHeaderSeparatorLine(outputStream);
        }
    }
    appendTableHeaderSeparatorLine(outputStream);
}
