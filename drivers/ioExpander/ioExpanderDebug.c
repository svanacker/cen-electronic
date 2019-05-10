#include "ioExpanderDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "ioExpanderList.h"

#define IO_EXPANDER_IO_COUNT                      8

#define IO_EXPANDER_INDEX_COLUMN_LENGTH		      15
#define IO_EXPANDER_COUNT_COLUMN_LENGTH           10
#define IO_EXPANDER_VALUE_COLUMN_LENGTH           5
#define IO_EXPANDER_LAST_COLUMN		              0

/**
* Private.
*/
void printIOExpanderDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);

    // First line
    appendStringHeader(outputStream, "IO Expander", IO_EXPANDER_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Count", IO_EXPANDER_COUNT_COLUMN_LENGTH);

    int ioIndex;
    for (ioIndex = IO_EXPANDER_IO_COUNT - 1; ioIndex >= 0; ioIndex--) {
        appendStringHeader(outputStream, "IO ", IO_EXPANDER_VALUE_COLUMN_LENGTH);
    }
    appendEndOfTableColumn(outputStream, IO_EXPANDER_LAST_COLUMN);

    // Second line
    appendStringHeader(outputStream, "Index", IO_EXPANDER_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", IO_EXPANDER_COUNT_COLUMN_LENGTH);
    for (ioIndex = IO_EXPANDER_IO_COUNT - 1; ioIndex >= 0; ioIndex--) {
        appendStringAndDecHeader(outputStream, "", ioIndex, IO_EXPANDER_VALUE_COLUMN_LENGTH);
    }
    appendEndOfTableColumn(outputStream, IO_EXPANDER_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}


void printIOExpanderStatesTable(OutputStream* outputStream, IOExpanderList* ioExpanderList) {
    printIOExpanderDebugTableHeader(outputStream);
    int ioIndex;

    unsigned int ioExpanderIndex;
    for (ioExpanderIndex = 0; ioExpanderIndex < ioExpanderList->size; ioExpanderIndex++) {
        appendDecTableData(outputStream, ioExpanderIndex, IO_EXPANDER_INDEX_COLUMN_LENGTH);
        IOExpander* ioExpander = getIOExpanderByIndex(ioExpanderList, ioExpanderIndex);

        appendDecTableData(outputStream, ioExpander->count, IO_EXPANDER_COUNT_COLUMN_LENGTH);

        for (ioIndex = ioExpander->count - 1; ioIndex >= 0; ioIndex--) {
            bool value = ioExpander->ioExpanderReadSingleValue(ioExpander, ioIndex);

            appendBoolTableData(outputStream, value, IO_EXPANDER_VALUE_COLUMN_LENGTH);
        }
        appendEndOfTableColumn(outputStream, IO_EXPANDER_LAST_COLUMN);
        appendTableHeaderSeparatorLine(outputStream);
    }
}
