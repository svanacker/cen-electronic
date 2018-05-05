#include "endMatchDebug.h"

#include <stdbool.h>

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
    appendBoolTableData(outputStream, endMatch->doNotEnd, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendStringTableData(outputStream, "N/A", END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);
    appendTableHeaderSeparatorLine(outputStream);

    // VALUES
    // Current Time In Second
    appendStringTableData(outputStream, "Current Time In Second", END_MATCH_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, endMatch->currentTimeInSecond, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, endMatch->currentTimeInSecond, END_MATCH_VALUE_HEX_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);

    // End of Match Notified
    appendStringTableData(outputStream, "End of Match Notified", END_MATCH_KEY_COLUMN_LENGTH);
    appendBoolTableData(outputStream, endMatch->endOfMatchNotified, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendStringTableData(outputStream, "N/A", END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);

    // Match Duration In Second
    appendStringTableData(outputStream, "Match Duration In Second", END_MATCH_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, endMatch->matchDurationInSecond, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendHex2TableData(outputStream, endMatch->matchDurationInSecond, END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);

    // Is Match Finished
    appendStringTableData(outputStream, "Is Match Finished", END_MATCH_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, isMatchFinished(endMatch), END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendStringTableData(outputStream, "N/A", END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);

    // Score to show
    appendStringTableData(outputStream, "Score to Show", END_MATCH_KEY_COLUMN_LENGTH);
    appendDecTableData(outputStream, endMatch->scoreToShow, END_MATCH_VALUE_DEC_COLUMN_LENGTH);
    appendHex4TableData(outputStream, endMatch->scoreToShow, END_MATCH_VALUE_HEX_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, END_MATCH_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}