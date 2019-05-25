#include "multiplexerDebug.h"

#include <stdlib.h>

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/i2cDebug.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#include "../../../drivers/i2c/multiplexer/multiplexer.h"
#include "../../../drivers/i2c/multiplexer/multiplexerTca9548A.h"
#include "../../../drivers/i2c/multiplexer/multiplexerList.h"

#define MULTIPLEXER_IO_COUNT                                          8

#define MULTIPLEXER_INDEX_COLUMN_LENGTH		                          8
#define MULTIPLEXER_COUNT_COLUMN_LENGTH                               6
#define MULTIPLEXER_USE_CACHE_CHANNEL_MASK_COLUMN_LENGTH              6
#define MULTIPLEXER_BUS_COLUMN_LENGTH                                15
#define MULTIPLEXER_ADDRESS_COLUMN_LENGTH                             8
#define MULTIPLEXER_CHANNEL_ENABLE_COLUMN_LENGTH                      5
#define MULTIPLEXER_LAST_COLUMN		                                  0

/**
* Private.
*/
void printMultiplexerDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);

    // First line
    appendStringHeader(outputStream, "Multip.", MULTIPLEXER_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Count", MULTIPLEXER_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Bus", MULTIPLEXER_BUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Address", MULTIPLEXER_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Use", MULTIPLEXER_USE_CACHE_CHANNEL_MASK_COLUMN_LENGTH);

    int multiplexerIndex;
    for (multiplexerIndex = MULTIPLEXER_IO_COUNT - 1; multiplexerIndex >= 0; multiplexerIndex--) {
        appendStringHeader(outputStream, "CHAN.", MULTIPLEXER_CHANNEL_ENABLE_COLUMN_LENGTH);
    }
    appendEndOfTableColumn(outputStream, MULTIPLEXER_LAST_COLUMN);

    // Second line
    appendStringHeader(outputStream, "Id", MULTIPLEXER_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", MULTIPLEXER_COUNT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", MULTIPLEXER_BUS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "(Hex)", MULTIPLEXER_ADDRESS_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Cache", MULTIPLEXER_USE_CACHE_CHANNEL_MASK_COLUMN_LENGTH);

    for (multiplexerIndex = MULTIPLEXER_IO_COUNT - 1; multiplexerIndex >= 0; multiplexerIndex--) {
        appendStringAndDecHeader(outputStream, "", multiplexerIndex, MULTIPLEXER_CHANNEL_ENABLE_COLUMN_LENGTH);
    }
    appendEndOfTableColumn(outputStream, MULTIPLEXER_LAST_COLUMN);

    appendTableHeaderSeparatorLine(outputStream);
}


void printMultiplexerTable(OutputStream* outputStream, MultiplexerList* multiplexerList) {
    printMultiplexerDebugTableHeader(outputStream);
    unsigned int multiplexerIndex;
    for (multiplexerIndex = 0; multiplexerIndex < multiplexerList->size; multiplexerIndex++) {
        Multiplexer* multiplexer = getMultiplexerByIndex(multiplexerList, multiplexerIndex);
        appendDecTableData(outputStream, multiplexerIndex, MULTIPLEXER_INDEX_COLUMN_LENGTH);
        appendDecTableData(outputStream, multiplexer->channelCount, MULTIPLEXER_COUNT_COLUMN_LENGTH);
        
        I2cBusConnection* i2cBusConnection = NULL;
#ifndef PC_COMPILER
        i2cBusConnection = getMultiplexerI2cBusConnection(multiplexer);
#endif
        if (i2cBusConnection == NULL) {
            appendStringTableData(outputStream, "-", MULTIPLEXER_BUS_COLUMN_LENGTH);
            appendStringTableData(outputStream, "-", MULTIPLEXER_ADDRESS_COLUMN_LENGTH);
        }
        else {
            I2cBus* i2cBus = i2cBusConnection->i2cBus;
            const char* i2cPortAsString = getI2cPortAsString(i2cBus->port);
            appendStringTableData(outputStream, i2cPortAsString, MULTIPLEXER_BUS_COLUMN_LENGTH);
            appendHex2TableData(outputStream, i2cBusConnection->i2cAddress, MULTIPLEXER_ADDRESS_COLUMN_LENGTH);
        }
        
        appendBoolAsStringTableData(outputStream, multiplexer->useChannelMasksCache, MULTIPLEXER_USE_CACHE_CHANNEL_MASK_COLUMN_LENGTH);
        
        // ALL CHANNELS
        signed int channelIndex;
        for (channelIndex = (signed int) multiplexer->channelCount - 1; channelIndex >= 0; channelIndex--) {
            bool value = multiplexer->multiplexerGetChannelEnable(multiplexer, (unsigned int) channelIndex);

            appendBoolTableData(outputStream, value, MULTIPLEXER_CHANNEL_ENABLE_COLUMN_LENGTH);
        }
        appendEndOfTableColumn(outputStream, MULTIPLEXER_LAST_COLUMN);
        appendTableHeaderSeparatorLine(outputStream);
    }
}
