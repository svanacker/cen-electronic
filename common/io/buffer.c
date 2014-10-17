#include <stdlib.h>
#include <stddef.h>

#include "buffer.h"

#include "stream.h"
#include "inputStream.h"
#include "outputStream.h"

#include "../../common/error/error.h"
#include "../../common/io/ioUtils.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"

// BUFFER

bool checkBufferNotNull(Buffer* buffer) {
    if (buffer == NULL) {
        writeError(IO_BUFFER_NULL);
        return false;
    }
    return true;
}

// -> OUTPUT STREAM INTERFACE

/**
 * @private
 */
void _openBufferOutputStream(OutputStream* outputStream, int param1) {
    Buffer* buffer = (Buffer*) outputStream->object;

    deepClearBuffer(buffer);
}

/**
 * @private
 */
void _closeBufferOutputStream(OutputStream* outputStream) {
    Buffer* buffer = (Buffer*) outputStream->object;

    deepClearBuffer(buffer);
}

/**
 * Definition of a function which is able to write a character.
 */
void _bufferWriteChar(OutputStream* outputStream, char c) {
    Buffer* buffer = (Buffer*) outputStream->object;

    bufferWriteChar(buffer, c);
}

/**
 * Flush the stream.
 */
void _bufferFlush(OutputStream* outputStream) {
    // DO NOTHING
}

// -> INPUT STREAM INTERFACE

/**
 * @private
 */
void _openBufferInputStream(InputStream* inputStream, int param1) {
    Buffer* buffer = (Buffer*) inputStream->object;

    deepClearBuffer(buffer);
}

/**
 * @private
 */
void _closeBufferInputStream(InputStream* inputStream) {
    Buffer* buffer = (Buffer*) inputStream->object;

    deepClearBuffer(buffer);
}

/**
 * @private
 */
char _bufferReadChar(InputStream* inputStream) {
    Buffer* buffer = (Buffer*) inputStream->object;
    char result = bufferReadChar(buffer);
    return result;
}

/**
 * Definition of a function which is able to return if there is character to read.
 */
bool _bufferAvailableData(InputStream* inputStream) {
    Buffer* buffer = (Buffer*) inputStream->object;
    bool result = !isBufferEmpty(buffer);

    return result;
}


// BUFFER INTERFACE

void initBuffer(Buffer* buffer, char (*array)[], unsigned char length, char* name, char* type) {
    buffer->s = array;
    buffer->length = length;
    deepClearBuffer(buffer);

    // inputStream
    initInputStream(
            &(buffer->inputStream),
            &_openBufferInputStream,
            &_closeBufferInputStream,
            &_bufferReadChar,
            &_bufferAvailableData,
            (int*) buffer);

    // outputStream
    initOutputStream(
            &(buffer->outputStream),
            &_openBufferOutputStream,
            &_closeBufferOutputStream,
            &_bufferWriteChar,
            &_bufferFlush,
            (int*) buffer
            );
    buffer->name = name;
    buffer->type = type;
}

bool isBufferInitialized(Buffer* buffer)
{
    return buffer->length > 0;
}

bool isBufferFull(const Buffer* buffer) {
    return ((buffer->writeIndex + 1) % buffer->length) == buffer->readIndex;

}

bool isBufferEmpty(const Buffer* buffer) {
    return buffer->readIndex == buffer->writeIndex;
}

int getBufferElementsCount(const Buffer* buffer) {
    int result = buffer->writeIndex - buffer->readIndex;
    if (result < 0) {
        result += buffer->length;
    }
    return result;
}

void bufferWriteChar(Buffer* buffer, char c) {
    int isFull = isBufferFull(buffer);
    if (!isFull) {
        char* sPointer = (char*) buffer->s;
        // Shift to the right cell index
        sPointer += buffer->writeIndex;
        *sPointer = c;
        buffer->writeIndex++;
        buffer->writeIndex %= buffer->length;
    } else {
        // We must log the problem
        writeError(IO_BUFFER_FULL);
        // Print Buffer
        printDebugBuffer(getErrorOutputStreamLogger(), buffer);
    }
}

char bufferReadChar(Buffer* buffer) {
    int isEmpty = isBufferEmpty(buffer);
    if (!isEmpty) {
        // char result = buffer->s[buffer->readIndex];
        char* sPointer = (char*) buffer->s;
        // Shift to the right cell index
        sPointer += buffer->readIndex;
        char result = *sPointer;        

        buffer->readIndex++;
        buffer->readIndex %= buffer->length;
        return result;
    } else {
        // We must log the problem
        writeError(IO_BUFFER_EMPTY);
    }
    return 0;
}

char bufferGetCharAtIndex(Buffer* buffer, int charIndex) {
    int size = getBufferElementsCount(buffer);
    if (charIndex < size) {
        char* sPointer = (char*) buffer->s;
        // Shift to the right cell index
        sPointer += ((buffer->readIndex + charIndex) % buffer->length);
        char result = *sPointer;        

        return result;
    } else {
        // We must log the problem
        writeError(IO_BUFFER_NOT_ENOUGH_DATA);
    }
    return 0;
}

void clearBuffer(Buffer* buffer) {
    buffer->writeIndex = 0;
    buffer->readIndex = 0;
}

void deepClearBuffer(Buffer* buffer) {
    int i;
    char* sPointer = (char*) buffer->s;
    for (i = 0; i < buffer->length; i++) {
        // Shift to the right cell index
        *sPointer = 0;
        sPointer++;
    }
    clearBuffer(buffer);
}

InputStream* getInputStream(Buffer* buffer) {
    if (checkBufferNotNull(buffer)) {
        return &(buffer->inputStream);
    }
    return NULL;
}

OutputStream* getOutputStream(Buffer* buffer) {
    if (checkBufferNotNull(buffer)) {
        return &(buffer->outputStream);
    }
    return NULL;
}

void printDebugBuffer(OutputStream* outputStream, Buffer* buffer) {
    if (buffer == NULL) {
        appendString(outputStream, "\nBuffer is NULL !\n");
        return;
    }
    appendString(outputStream, "\nBuf:");

    if (buffer->name != NULL) {
        appendKeyAndName(outputStream, "name=", buffer->name);
    }

    if (buffer->type) {
        appendKeyAndName(outputStream, ",type=", buffer->type);
    }

    appendStringAndDec(outputStream, ",length=", buffer->length);
    appendStringAndDec(outputStream, ",writeIdx=", buffer->writeIndex);
    appendStringAndDec(outputStream, ",readIdx=", buffer->readIndex);

    appendString(outputStream, ",START=");
    int i;
    char* sPointer = (char*) buffer->s;
    for (i = 0; i < buffer->length; i++) {
        // Shift to the right cell index
        append(outputStream, *sPointer);
        sPointer++;
    }
    appendString(outputStream, "END\n");
}
