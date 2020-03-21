#include "ledPc.h"

#include "../led.h"

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
 * PC Implementation Write the color (RGB) value of the specified led.
 * @param ledIndex the index of the led
 */
void ledArrayWriteValuePc(LedArray* ledArray, unsigned int ledIndex, unsigned int R, unsigned int G, unsigned int B) {
    appendStringAndDecLN(getInfoOutputStreamLogger(), "R=", R);
    appendStringAndDecLN(getInfoOutputStreamLogger(), "G=", G);
    appendStringAndDecLN(getInfoOutputStreamLogger(), "B=", B);
}

void initLedArrayPc(LedArray* ledArray) {
    initLedArray(ledArray, &ledArrayInitPc, &ledArrayWriteValuePc, NULL);
}
