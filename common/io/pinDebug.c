#include "pin.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

#define PIN_DEBUG_PIN_INDEX_HEX_COLUMN_LENGTH				                  10
#define PIN_DEBUG_PIN_NAME_COLUMN_LENGTH				                      10
#define PIN_DEBUG_PIN_INPUT_COLUMN_LENGTH				                      20
#define PIN_DEBUG_PIN_VALUE_COLUMN_LENGTH				                      10
#define PIN_DEBUG_LAST_COLUMN_LENGTH				                          30


void printAllPinValues(PinList* pinList, OutputStream* outputStream) {
    println(outputStream);
    appendTableHeaderSeparatorLine(outputStream);

    // First Line
    appendStringHeader(outputStream, "Pin Idx", PIN_DEBUG_PIN_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Pin Name", PIN_DEBUG_PIN_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Input (1) / ", PIN_DEBUG_PIN_INPUT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Pin Value", PIN_DEBUG_PIN_VALUE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, PIN_DEBUG_LAST_COLUMN_LENGTH);

    // Second Line
    appendStringHeader(outputStream, "(Hex)", PIN_DEBUG_PIN_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PIN_DEBUG_PIN_NAME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Output (0)", PIN_DEBUG_PIN_INPUT_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PIN_DEBUG_PIN_VALUE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, PIN_DEBUG_LAST_COLUMN_LENGTH);


    appendTableHeaderSeparatorLine(outputStream);

    int pinIndex = 0;
    int pinCount = 0;
    for (pinIndex = PIN_MIN_INDEX; pinIndex <= PIN_MAX_INDEX; pinIndex++) {
        bool pinValid = isPinValid(pinList, pinIndex);
        if (!pinValid) {
            continue;
        }
        char* pinName = getPinName(pinList, pinIndex);
        bool pinValue = getPinValue(pinList, pinIndex);
        bool pinInput = isPinInput(pinList, pinIndex);
        appendHex2TableData(outputStream, pinIndex, PIN_DEBUG_PIN_INDEX_HEX_COLUMN_LENGTH);
        appendStringTableData(outputStream, pinName, PIN_DEBUG_PIN_NAME_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, pinInput, PIN_DEBUG_PIN_INPUT_COLUMN_LENGTH);
        appendBoolAsStringTableData(outputStream, pinValue, PIN_DEBUG_PIN_VALUE_COLUMN_LENGTH);
        appendEndOfTableColumn(outputStream, PIN_DEBUG_LAST_COLUMN_LENGTH);
        if (pinCount % 4 == 3) {
            appendTableHeaderSeparatorLine(outputStream);
        }
        pinCount++;
    }
}