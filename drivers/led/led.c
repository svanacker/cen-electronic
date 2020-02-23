#include "led.h"

void initLedArray(LedArray* ledArray,
    LedArrayInitFunction* ledInit,
    LedArrayWriteValueFunction* ledWriteValue,
    int* object) {
    ledArray->ledArrayInit = ledInit;
    ledArray->ledArrayWriteValue = ledWriteValue;
    ledArray->object = object;
}