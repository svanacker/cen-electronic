#include "led.h"

#include <stdlib.h>

#include "../../common/error/error.h"

void initLedArray(LedArray* ledArray,
        int ledCount,
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
    ledArray->ledCount = ledCount;
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

void setLedColorAsDistance(LedArray* ledArray, unsigned int ledIndex, unsigned int distance) {
    Color color;
    if (distance <= 25) {
        color.R = 255;
        color.G = (distance * 10);
        color.B = 0;
    }
    else if (distance <= 50) {
        color.R = 255 - (distance - 25) * 10;
        color.G = 255;
        color.B = 0;
    }
    else if (distance <= 75) {
        color.R = 0;
        color.G = 255;
        color.B = (distance - 50) * 10;
    }
    else if (distance <= 100) {
        color.R = 0;
        color.G = 255 - (distance - 75) * 10;
        color.B = 255;
    }
    else {
        color.R = 0;
        color.G = 0;
        color.B = 255;
    }
    setLedColor(ledArray, ledIndex, color);
}