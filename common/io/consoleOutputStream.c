#include <stdlib.h>
#include <stdio.h>


#include "consoleOutputStream.h"
#include "outputStream.h"

// CONSOLE OUTPUT STREAM
// Useful when we want to redirect information to NULL (like dev/null in Unix)

void openConsoleOutputStream(OutputStream* outputStream, int param1) {

}

void closeConsoleOutputStream(OutputStream* outputStream) {

}

void writeCharConsoleOutputStream(OutputStream* outputStream, char c) {
    putchar(c);
}

void flushConsoleOutputStream(OutputStream* outputStream) {

}

void initConsoleOutputStream(OutputStream* outputStream) {
    initOutputStream(outputStream, openConsoleOutputStream, closeConsoleOutputStream, writeCharConsoleOutputStream, flushConsoleOutputStream, NULL);
}
