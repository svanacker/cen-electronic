#include "gameTargetListDebug.h"

#include "gameTarget.h"
#include "gameTargetList.h"
#include "gameTargetActionListDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define TARGET_LIST_INDEX_COLUMN_LENGTH              6
#define TARGET_LIST_NAME_COLUMN_LENGTH              25
#define TARGET_LIST_POINT_X_COLUMN_LENGTH           8
#define TARGET_LIST_POINT_Y_COLUMN_LENGTH           8
#define TARGET_LIST_POTENTIAL_GAIN_COLUMN_LENGTH    10
#define TARGET_LIST_STATUS_COLUMN_LENGTH            10
#define TARGET_LIST_LAST_COLUMN_LENGTH              10

/**
 * @private
 */
void printGameTargetListHeader(OutputStream* outputStream) {
    println(outputStream);
    // Table Header
    appendTableHeaderSeparatorLine(outputStream);
    // Ligne 1
    appendStringHeader(outputStream, "index", TARGET_LIST_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "name", TARGET_LIST_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "x", TARGET_LIST_POINT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "y", TARGET_LIST_POINT_Y_COLUMN_LENGTH);
    appendStringHeader(outputStream, "potential", TARGET_LIST_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "status", TARGET_LIST_STATUS_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TARGET_LIST_LAST_COLUMN_LENGTH);
    // Ligne 2
    appendStringHeader(outputStream, "", TARGET_LIST_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TARGET_LIST_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TARGET_LIST_POINT_X_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(mm)", TARGET_LIST_POINT_Y_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Gain", TARGET_LIST_POTENTIAL_GAIN_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", TARGET_LIST_STATUS_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TARGET_LIST_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private
 */
void printGameTargetLine(OutputStream* outputStream, unsigned int index, GameTarget* target, bool includeItems) {
    appendDecTableData(outputStream, index, TARGET_LIST_INDEX_COLUMN_LENGTH);
    appendStringTableData(outputStream, target->name, TARGET_LIST_NAME_COLUMN_LENGTH);
    appendDecfTableData(outputStream, target->location->x, TARGET_LIST_POINT_X_COLUMN_LENGTH);
    appendDecfTableData(outputStream, target->location->y, TARGET_LIST_POINT_Y_COLUMN_LENGTH);
    appendDecfTableData(outputStream, target->potentialGain, TARGET_LIST_POTENTIAL_GAIN_COLUMN_LENGTH);
    addGameTargetStatusTableData(outputStream, target->status, TARGET_LIST_STATUS_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, TARGET_LIST_LAST_COLUMN_LENGTH);
    /*
    if (includeItems) {
        printGameTargetActionList(outputStream, &(target->actionList));
    }
    */
}

void printGameTargetListTable(GameTargetList* gameTargetList, OutputStream* outputStream) {
    unsigned int i;
    
    unsigned int size = gameTargetList->size;
    println(outputStream);
    appendStringAndDec(outputStream, "targetHandledCount:", gameTargetList->targetHandledCount);
    println(outputStream);
    printGameTargetListHeader(outputStream);
    for (i = 0; i < size; i++) {
        GameTarget* target = gameTargetList->targets[i];
        printGameTargetLine(outputStream, i, target, true);
    }
    appendTableHeaderSeparatorLine(outputStream);
}
