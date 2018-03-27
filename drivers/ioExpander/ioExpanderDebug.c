#include "ioExpanderDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "ioExpander.h"

#define IO_EXPANDER_INDEX_COLUMN_LENGTH		      10
#define IO_EXPANDER_VALUE_COLUMN_LENGTH             10
#define IO_EXPANDER_LAST_COLUMN		              60

/**
* Private.
*/
void printIOExpanderDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Index", IO_EXPANDER_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value", IO_EXPANDER_VALUE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, IO_EXPANDER_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}


void printIOExpanderStatesTable(OutputStream* outputStream, IOExpander* ioExpander) {
    printIOExpanderDebugTableHeader(outputStream);
    unsigned int ioIndex;
    for (ioIndex = 0; ioIndex < ioExpander->count; ioIndex++) {
        bool value = ioExpander->ioExpanderReadValue(ioExpander, ioIndex);

        appendDecTableData(outputStream, ioIndex, IO_EXPANDER_INDEX_COLUMN_LENGTH);
        appendBoolTableData(outputStream, value, IO_EXPANDER_VALUE_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, IO_EXPANDER_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}
