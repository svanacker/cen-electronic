#include "fileOutputStream.h"

#include "../../../common/io/outputStream.h"

#include <stdlib.h>

// FILE OUTPUT STREAM

void openFileOutputStream(OutputStream* outputStream, int param1) {
    // TODO
}

void closeFileOutputStream(OutputStream* outputStream) {

}

void writeCharFileOutputStream(OutputStream* outputStream, unsigned char c) {
    
}

void flushFileOutputStream(OutputStream* outputStream) {

}

void initFileOutputStream(OutputStream* outputStream, char* fileName) {
    initOutputStream(outputStream, openFileOutputStream, closeFileOutputStream, writeCharFileOutputStream, 
        flushFileOutputStream, (int*) fileName);
}
