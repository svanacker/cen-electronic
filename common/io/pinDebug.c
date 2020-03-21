#include "pin.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

void printAllPinValues(PinList* pinList, OutputStream* outputStream) {
    int i = 0;
    for (i = PIN_MIN_INDEX; i <= PIN_MAX_INDEX; i++) {
        bool value = pinList->getPinValueFunction(pinList, i);
        appendString(outputStream, "Pin ");
        appendHex2(outputStream, i);
        append(outputStream, '=');
        appendBool(outputStream, value);
        println(outputStream);
    }
}