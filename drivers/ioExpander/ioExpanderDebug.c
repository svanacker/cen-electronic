#include "ioExpanderDebug.h"

#include <stdlib.h>

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/i2cDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "../../drivers/ioExpander/ioExpanderPcf8574.h"
#include "../../drivers/ioExpander/ioExpanderList.h"

#define IO_EXPANDER_IO_COUNT                      8

#define IO_EXPANDER_INDEX_COLUMN_LENGTH		      13
#define IO_EXPANDER_COUNT_COLUMN_LENGTH           6
#define IO_EXPANDER_BUS_COLUMN_LENGTH             15
#define IO_EXPANDER_ADDRESS_COLUMN_LENGTH         8
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
    appendStringHeader(outputStream, "Bus", IO_EXPANDER_BUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Address", IO_EXPANDER_ADDRESS_COLUMN_LENGTH);

    int ioIndex;
    for (ioIndex = IO_EXPANDER_IO_COUNT - 1; ioIndex >= 0; ioIndex--) {
        appendStringHeader(outputStream, "IO ", IO_EXPANDER_VALUE_COLUMN_LENGTH);
    }
    appendEndOfTableColumn(outputStream, IO_EXPANDER_LAST_COLUMN);

    // Second line
    appendStringHeader(outputStream, "Index", IO_EXPANDER_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", IO_EXPANDER_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", IO_EXPANDER_BUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Hex)", IO_EXPANDER_ADDRESS_COLUMN_LENGTH);
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
        IOExpander* ioExpander = getIOExpanderByIndex(ioExpanderList, ioExpanderIndex);
        appendDecTableData(outputStream, ioExpanderIndex, IO_EXPANDER_INDEX_COLUMN_LENGTH);
        appendDecTableData(outputStream, ioExpander->count, IO_EXPANDER_COUNT_COLUMN_LENGTH);
        
        I2cBusConnection* i2cBusConnection = NULL;
#ifndef PC_COMPILER
        i2cBusConnection = getIOExpanderBusConnection(ioExpander);
#endif
        if (i2cBusConnection == NULL) {
            appendStringTableData(outputStream, "-", IO_EXPANDER_BUS_COLUMN_LENGTH);
            appendStringTableData(outputStream, "-", IO_EXPANDER_ADDRESS_COLUMN_LENGTH);
        }
        else {
            I2cBus* i2cBus = i2cBusConnection->i2cBus;
            const char* i2cPortAsString = getI2cPortAsString(i2cBus->port);
            appendStringTableData(outputStream, i2cPortAsString, IO_EXPANDER_BUS_COLUMN_LENGTH);
            appendHex2TableData(outputStream, i2cBusConnection->i2cAddress, IO_EXPANDER_ADDRESS_COLUMN_LENGTH);
        }

        for (ioIndex = ioExpander->count - 1; ioIndex >= 0; ioIndex--) {
            bool value = ioExpander->ioExpanderReadSingleValue(ioExpander, ioIndex);

            appendBoolTableData(outputStream, value, IO_EXPANDER_VALUE_COLUMN_LENGTH);
        }
        appendEndOfTableColumn(outputStream, IO_EXPANDER_LAST_COLUMN);
        appendTableHeaderSeparatorLine(outputStream);
    }
}
