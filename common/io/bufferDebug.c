#include <stdlib.h>

#include "bufferDebug.h"
#include "buffer.h"
#include "outputStream.h"
#include "printWriter.h"

void printDebugBuffer(OutputStream* outputStream, Buffer* buffer) {
    if (!checkBufferNotNull(buffer)) {
        return;
    }
    if (buffer == NULL) {
        println(outputStream);
        appendStringLN(outputStream, "Buffer is NULL !");
        return;
    }
    println(outputStream);
    appendString(outputStream, "Buffer:");

    if (buffer->name != NULL) {
        appendKeyAndName(outputStream, "name=", buffer->name);
    }

    if (buffer->type) {
        appendKeyAndName(outputStream, ", type=", buffer->type);
    }

    appendStringAndDec(outputStream, ", length=", buffer->length);
    appendStringAndDec(outputStream, ", writeIdx=", buffer->writeIndex);
    appendStringAndDec(outputStream, ", readIdx=", buffer->readIndex);
    appendCRLF(outputStream);
    // FULL DUMP 
    appendString(outputStream, "---START---");
    appendCRLF(outputStream);
    unsigned int i;
    char* sPointer = (char*) buffer->s;
    for (i = 0; i < buffer->length; i++) {
        // Shift to the right cell index
        unsigned char c = *sPointer;
        if (c == 0) {
            // To avoid [00] on Console
            append(outputStream, '#');
        } else {
            append(outputStream, c);
        }
        sPointer++;
        // Multi line management
        if (i % CONSOLE_MAX_WIDTH == CONSOLE_MAX_WIDTH - 1) {
            appendCRLF(outputStream);
        }
    }
    appendCRLF(outputStream);
    appendString(outputStream, "---END---");
    appendCRLF(outputStream);

    // LOGICAL COUNT
    appendString(outputStream, "---FROM READ_INDEX TO WRITE_INDEX ---");
    appendCRLF(outputStream);
    for (i = 0; i < buffer->readIndex; i++) {
        append(outputStream, ' ');
    }
    unsigned elementCount = getBufferElementsCount(buffer);
    for (i = 0; i < elementCount; i++) {
        unsigned char c = bufferGetCharAtIndex(buffer, i);
        append(outputStream, c);
        // Multi line management
        if (i % CONSOLE_MAX_WIDTH == CONSOLE_MAX_WIDTH - 1) {
            appendCRLF(outputStream);
        }
    }
    appendCRLF(outputStream);

}
