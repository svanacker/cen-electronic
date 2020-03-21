#include <stdlib.h>

#include "streamLink.h"

void initStreamLink(StreamLink* streamLink,
        const char* streamName,
        Buffer* inputBuffer,
        unsigned char (*inputBufferArrayPointer)[],
        unsigned int inputBufferLength,
        Buffer* outputBuffer,
        unsigned char (*outputBufferArrayPointer)[],
        unsigned int outputBufferLength,
        OutputStream* outputStream,
        int param) {
    streamLink->inputBuffer = inputBuffer;
    streamLink->outputBuffer = outputBuffer;
    streamLink->outputStream = outputStream;
    if (inputBuffer != NULL) {
        initBuffer(inputBuffer, inputBufferArrayPointer, inputBufferLength, streamName, IN_AS_STRING);
    }
    if (outputBuffer != NULL) {
        initBuffer(outputBuffer, outputBufferArrayPointer, outputBufferLength, streamName, OUT_AS_STRING);
    }
    if (outputStream != NULL) {
        outputStream->openOutputStream(outputStream, param);
    }
}
