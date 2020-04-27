#include "ledPc.h"

#include "../led.h"

#include "../../../common/color/color.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/log/logger.h"

#include <stdbool.h>
#include <stdlib.h>

/**
 * Type of function to initialize the led array.
 */
bool ledArrayInitPc(LedArray* ledArray) {
    // Nothing to do
    return true;
}

/**
 * PC Implementation Read the color (RGB) value of the specified led.
 * @param ledIndex the index of the led
 * @return the current Color
 */
Color ledArrayReadValuePc(LedArray* ledArray, unsigned int ledIndex) {
    // TODO : Implementation
    Color result;
    result.R = 0;
    result.G = 0;
    result.G = 0;
    return result;
}

/**
 * PC Implementation Write the color (RGB) value of the specified led.
 * @param ledIndex the index of the led
 */
void ledArrayWriteValuePc(LedArray* ledArray, unsigned int ledIndex, unsigned int R, unsigned int G, unsigned int B) {
    appendStringAndDecLN(getInfoOutputStreamLogger(), "R=", R);
    appendStringAndDecLN(getInfoOutputStreamLogger(), "G=", G);
    appendStringAndDecLN(getInfoOutputStreamLogger(), "B=", B);
}

void initLedArrayPc(LedArray* ledArray) {
    initLedArray(ledArray, 5, &ledArrayInitPc, &ledArrayReadValuePc , &ledArrayWriteValuePc, NULL);
}
