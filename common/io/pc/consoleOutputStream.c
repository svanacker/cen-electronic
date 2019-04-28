#include <stdlib.h>
#include <stdio.h>

#include "consoleOutputStream.h"
#include "../../../common/io/outputStream.h"

// CONSOLE OUTPUT STREAM
// Useful when we want to redirect information to console on PC

void openConsoleOutputStream(OutputStream* outputStream, int param1) {

}

void closeConsoleOutputStream(OutputStream* outputStream) {

}

void writeCharConsoleOutputStream(OutputStream* outputStream, unsigned char c) {
    putchar(c);
}

void flushConsoleOutputStream(OutputStream* outputStream) {

}

void initConsoleOutputStream(OutputStream* outputStream) {
    initOutputStream(outputStream, openConsoleOutputStream, closeConsoleOutputStream, writeCharConsoleOutputStream, flushConsoleOutputStream, NULL);
}
