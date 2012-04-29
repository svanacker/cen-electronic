#include "stream.h"
#include "outputStream.h"

#include "../../common/commons.h"

// NULL OUTPUT STREAM
// Useful when we want to redirect information to NULL (like dev/null in Unix)

void openNullOutputStream(OutputStream* outputStream, int param1) {

}

void closeNullOutputStream(OutputStream* outputStream) {

}

void writeCharNullOutputStream(OutputStream* outputStream, char c) {
    
}

void flushNullOutputStream(OutputStream* outputStream) {

}

void initNullOutputStream(OutputStream* outputStream) {
    outputStream->openOutputStream = openNullOutputStream;
    outputStream->closeOutputStream = closeNullOutputStream;
    outputStream->writeChar = writeCharNullOutputStream;
    outputStream->flush = flushNullOutputStream;
}
