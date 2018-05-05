#include "startMatchDebug.h"

#include <stdbool.h>
#include <stdint.h>

#include "startMatch.h"

#include "../../common/io/outputStream.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define START_MATCH_KEY_COLUMN_LENGTH				30
#define START_MATCH_VALUE_DEC_COLUMN_LENGTH         15
//#define START_MATCH_VALUE_HEX_COLUMN_LENGTH       15
#define START_MATCH_LAST_COLUMN_LENGTH		        10

/**
* @private.
*/
void printStartOfMatchTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Key", START_MATCH_KEY_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value (Dec)", START_MATCH_VALUE_DEC_COLUMN_LENGTH);
//    appendStringHeader(outputStream, "Value (Hex)", END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, START_MATCH_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);
}

void printStartMatchTable(OutputStream* outputStream, StartMatch* startMatch) {
    printStartOfMatchTableHeader(outputStream);

    // CONFIG
    appendStringTableData(outputStream, "Wait for Start", START_MATCH_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, startMatch->waitForStart, START_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, START_MATCH_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);

    // Is Match Started
    appendStringTableData(outputStream, "Is Match Started", START_MATCH_KEY_COLUMN_LENGTH);
    if (startMatch->waitForStart) {
        appendBoolAsStringTableData(outputStream, startMatch->isMatchStartedFunction(startMatch), START_MATCH_VALUE_DEC_COLUMN_LENGTH);
    }
    else {
        appendStringTableData(outputStream, "N/A", START_MATCH_VALUE_DEC_COLUMN_LENGTH);
    }
    appendEndOfTableColumn(outputStream, START_MATCH_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}