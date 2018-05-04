#include "gameTargetListDebug.h"

#include "gameTarget.h"
#include "gameTargetList.h"
#include "gameTargetActionListDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define TARGET_LIST_INDEX_COLUMN_LENGTH              8
#define TARGET_LIST_NAME_COLUMN_LENGTH              12
#define TARGET_LIST_POINT_X_COLUMN_LENGTH           12
#define TARGET_LIST_POINT_Y_COLUMN_LENGTH           12
#define TARGET_LIST_POTENTIAL_GAIN_COLUMN_LENGTH    10
#define TARGET_LIST_STATUS_COLUMN_LENGTH            10
#define TARGET_LIST_LAST_COLUMN_LENGTH              10

/**
 * @private
 */
unsigned int appendGameTargetStatusAsString(OutputStream* outputStream, enum GameTargetStatus gameTargetStatus) {
    switch (gameTargetStatus) {
        case TARGET_AVAILABLE: return appendString(outputStream, "AVAILABLE");
        case TARGET_HANDLED: return appendString(outputStream, "HANDLED");
        case TARGET_INUSE: return appendString(outputStream, "IN USE");
    }
    appendString(outputStream, "?");

    return 1;
}

/**
 * @private
 */
unsigned int addGameTargetStatusTableData(OutputStream* outputStream, enum GameTargetStatus gameTargetStatus, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendGameTargetStatusAsString(outputStream, gameTargetStatus);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

/**
 * @private
 */
void printGameTargetListHeader(OutputStream* outputStream) {
    println(outputStream);
    // Table Header
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "index", TARGET_LIST_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "name", TARGET_LIST_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "x (mm)", TARGET_LIST_POINT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "y (mm)", TARGET_LIST_POINT_Y_COLUMN_LENGTH);
    appendStringHeader(outputStream, "potentialGain", TARGET_LIST_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "status", TARGET_LIST_STATUS_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TARGET_LIST_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private
 */
void printGameTargetLine(OutputStream* outputStream, GameTarget* target, bool includeItems) {
    appendStringTableData(outputStream, target->name, TARGET_LIST_NAME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, target->potentialGain, TARGET_LIST_POTENTIAL_GAIN_COLUMN_LENGTH);
    addGameTargetStatusTableData(outputStream, target->status, TARGET_LIST_STATUS_COLUMN_LENGTH);
    /*
    if (includeItems) {
        printGameTargetActionList(outputStream, &(target->actionList));
    }
    */
}

void printGameTargetListTable(GameTargetList* gameTargetList, OutputStream* outputStream) {
    int i;
    
    int size = gameTargetList->size;
    println(outputStream);
    appendStringAndDec(outputStream, "targetHandledCount:", gameTargetList->targetHandledCount);
    println(outputStream);
    printGameTargetListHeader(outputStream);
    for (i = 0; i < size; i++) {
        GameTarget* target = gameTargetList->targets[i];
        printGameTargetLine(outputStream, target, true);
    }
    appendTableHeaderSeparatorLine(outputStream);
}
