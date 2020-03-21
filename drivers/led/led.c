#include "led.h"

#include <stdlib.h>

#include "../../common/error/error.h"

void initLedArray(LedArray* ledArray,
        LedArrayInitFunction* ledInitFunction,
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
    ledArray->ledArrayWriteValue = ledWriteValue;
    ledArray->object = object;

    // Initialization
    ledInitFunction(ledArray);
}