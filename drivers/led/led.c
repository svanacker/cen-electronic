#include "led.h"

#include <stdlib.h>

#include "../../common/error/error.h"

void initLedArray(LedArray* ledArray,
        LedArrayInitFunction* ledInitFunction,
        LedArrayReadValueFunction* ledReadValue,
        LedArrayWriteValueFunction* ledWriteValue,
        int* object) {
    if (ledArray == NULL) {
        writeError(LED_ARRAY_NULL);
        return;
    }
    if (ledInitFunction == NULL) {
        writeError(LED_ARRAY_INIT_FUNCTION_NULL);
        return;
    }
    ledArray->ledArrayInit = ledInitFunction;
    ledArray->ledArrayReadValue = ledReadValue;
    ledArray->ledArrayWriteValue = ledWriteValue;
    ledArray->object = object;

    // Initialization
    ledInitFunction(ledArray);
}

void setLedColor(LedArray* ledArray, unsigned int ledIndex, Color color) {
    if (ledArray == NULL) {
        writeError(LED_ARRAY_NULL);
        return;
    }
    if (ledArray->ledArrayWriteValue == NULL) {
        writeError(LED_ARRAY_WRITE_VALUE_NULL);
        return;
    }
    ledArray->ledArrayWriteValue(ledArray, ledIndex, color.R, color.G, color.B);
}