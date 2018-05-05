#include "endMatchDebug.h"

#include <stdbool.h>
#include <stdint.h>

#include "../../common/io/outputStream.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define END_MATCH_KEY_COLUMN_LENGTH				30
#define END_MATCH_VALUE_DEC_COLUMN_LENGTH       15
#define END_MATCH_VALUE_HEX_COLUMN_LENGTH       15
#define END_MATCH_LAST_COLUMN_LENGTH		    10

/**
* @private.
*/
void printEndOfMatchTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Key", END_MATCH_KEY_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value (Dec)", END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value (Hex)", END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);
}

void printEndOfMatchTable(OutputStream* outputStream, EndMatch* endMatch) {
    printEndOfMatchTableHeader(outputStream);

    // CONFIG
    // Do not end
    appendStringTableData(outputStream, "Do not end", END_MATCH_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, endMatch->doNotEnd, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendStringTableData(outputStream, "N/A", END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);

    // VALUES

    // Remaining Time
    appendStringTableData(outputStream, "Remaining Time", END_MATCH_KEY_COLUMN_LENGTH);
    unsigned int remainingTime = matchEndGetRemainingTime(endMatch);
    if (remainingTime == INT32_MAX) {
        appendStringTableData(outputStream, "+INFINITY", END_MATCH_VALUE_DEC_COLUMN_LENGTH);
        appendStringTableData(outputStream, "+INFINITY", END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    }
    else {
        appendDecTableData(outputStream, remainingTime, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
        appendHex2TableData(outputStream, remainingTime, END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    }
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);

    // Match Duration In Second
    appendStringTableData(outputStream, "Match Duration In Second", END_MATCH_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, endMatch->matchDurationInSecond, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, endMatch->matchDurationInSecond, END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);

    // Current Time In Second
    appendStringTableData(outputStream, "Current Time In Second", END_MATCH_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, endMatch->currentTimeInSecond, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, endMatch->currentTimeInSecond, END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);

    // Is Match Finished
    appendStringTableData(outputStream, "Is Match Finished", END_MATCH_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, isMatchFinished(endMatch), END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendStringTableData(outputStream, "N/A", END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);

    // Score to show
    appendStringTableData(outputStream, "Score to Show", END_MATCH_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, endMatch->scoreToShow, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendHex4TableData(outputStream, endMatch->scoreToShow, END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);

    // End of Match Notified
    appendStringTableData(outputStream, "End of Match Notified", END_MATCH_KEY_COLUMN_LENGTH);
    appendBoolAsStringTableData(outputStream, endMatch->endOfMatchNotified, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendStringTableData(outputStream, "N/A", END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);


    appendTableHeaderSeparatorLine(outputStream);
}