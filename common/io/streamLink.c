#include <stdlib.h>

#include "../../common/commons.h"

#include "streamLink.h"

void initStreamLink(StreamLink* streamLink,
        char* streamName,
        Buffer* inputBuffer,
		char (*inputBufferArrayPointer)[],
		unsigned char inputBufferLength,
        Buffer* outputBuffer,
		char (*outputBufferArrayPointer)[],
		unsigned char outputBufferLength,
        OutputStream* outputStream) {
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
        outputStream->openOutputStream(outputStream, 0);
    }
}
