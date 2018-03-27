#include "relayDebug.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#include "relay.h"

#define RELAY_INDEX_COLUMN_LENGTH		      10
#define RELAY_VALUE_COLUMN_LENGTH             10
#define RELAY_LAST_COLUMN		              60

/**
* Private.
*/
void printRelayDebugTableHeader(OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Index", RELAY_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value", RELAY_VALUE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, RELAY_LAST_COLUMN);
    appendTableHeaderSeparatorLine(outputStream);
}


void printRelayStatesTable(OutputStream* outputStream, Relay* relay) {
    printRelayDebugTableHeader(outputStream);
    unsigned int relayIndex;
    for (relayIndex = 0; relayIndex < relay->count; relayIndex++) {
        bool value = relay->relayReadValue(relay, relayIndex);

            // Strategy Index
        appendDecTableData(outputStream, relayIndex, RELAY_INDEX_COLUMN_LENGTH);
        appendBoolTableData(outputStream, value, RELAY_VALUE_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, RELAY_LAST_COLUMN);
    }

    appendTableHeaderSeparatorLine(outputStream);
}
