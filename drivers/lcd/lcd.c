/**
 * Common function for driver LCD, which are not specific to a particular device.
 */
#include <stdlib.h>
#include <string.h>

#include "lcd.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"

/**
 *@private
 */
void openOutputStreamLCD(OutputStream* outputStream, int param1) {
    initLCD();
    clearScreen();
}

/**
 *@private
 */
void closeOutputStreamLCD(OutputStream* outputStream) {
    clearScreen();
}

/**
 *@private
 */
void writeLCDStreamChar(OutputStream* outputStream, char c) {
    writeLCDChar(c);
}

/**
 *@private
 */
void flushLCD(OutputStream* outputStream) {
    //
}

void initLCDOutputStream(OutputStream* outputStream) {
    outputStream->openOutputStream = openOutputStreamLCD;
    outputStream->closeOutputStream = closeOutputStreamLCD;
    outputStream->writeChar = writeLCDStreamChar;
    outputStream->flush = flushLCD;
    openOutputStreamLCD(outputStream, 0);
}
