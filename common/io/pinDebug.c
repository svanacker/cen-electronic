#include "pin.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define PIN_DEBUG_PIN_NAME_COLUMN_LENGTH				                      10
#define PIN_DEBUG_PIN_VALUE_COLUMN_LENGTH				                      10
#define PIN_DEBUG_LAST_COLUMN_LENGTH				                          50


void printAllPinValues(PinList* pinList, OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);

    appendStringHeader(outputStream, "Pin Name", PIN_DEBUG_PIN_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Pin Value", PIN_DEBUG_PIN_VALUE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, PIN_DEBUG_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);

    int i = 0;
    for (i = PIN_MIN_INDEX; i <= PIN_MAX_INDEX; i++) {
        char* pinName = getPinName(pinList, i);
        bool pinValue = getPinValue(pinList, i);
        appendStringTableData(outputStream, pinName, PIN_DEBUG_PIN_NAME_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, pinValue, PIN_DEBUG_PIN_VALUE_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, PIN_DEBUG_LAST_COLUMN_LENGTH);
        if (i % 4 == 3) {
            appendTableHeaderSeparatorLine(outputStream);
        }
    }
}