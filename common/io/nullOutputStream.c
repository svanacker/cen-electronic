#include <stdlib.h>

#include "nullOutputStream.h"
#include "outputStream.h"

// NULL OUTPUT STREAM
// Useful when we want to redirect information to NULL (like dev/null in Unix)

void openNullOutputStream(OutputStream* outputStream, int param1) {

}

void closeNullOutputStream(OutputStream* outputStream) {

}

void writeCharNullOutputStream(OutputStream* outputStream, unsigned char c) {

}

void flushNullOutputStream(OutputStream* outputStream) {

}

void initNullOutputStream(OutputStream* outputStream) {
    initOutputStream(outputStream, openNullOutputStream, closeNullOutputStream, writeCharNullOutputStream, flushNullOutputStream, NULL);
}
