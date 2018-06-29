#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "buffer.h"

#include "inputStream.h"
#include "outputStream.h"

#include "../../common/error/error.h"
#include "../../common/io/ioUtils.h"

#include "../../common/log/logHandler.h"
#include "../../common/log/logger.h"

// BUFFER

/**
 * Private Functions.
 * @returns true if there is a problem, false else
 */
bool checkBufferNotNull(const Buffer* buffer) {
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
 * @private
 * Definition of a function which is able to write a character.
 */
void _bufferWriteChar(OutputStream* outputStream, char c) {
    Buffer* buffer = (Buffer*) outputStream->object;

    bufferWriteChar(buffer, c);
}

/**
 * @private
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
 * @private
 * Definition of a function which is able to return if there is character to read.
 */
bool _bufferAvailableData(InputStream* inputStream) {
    Buffer* buffer = (Buffer*) inputStream->object;
    bool result = !isBufferEmpty(buffer);

    return result;
}


// BUFFER INTERFACE

void initBuffer(Buffer* buffer, char (*s)[], unsigned int length, const char* name, const char* type) {
    if (!checkBufferNotNull(buffer)) {
        return;    
    }
    buffer->s = s;
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

bool isBufferInitialized(Buffer* buffer) {
    if (!checkBufferNotNull(buffer)) {
        return false;
    }
    return buffer->length > 0;
}

bool isBufferFull(const Buffer* buffer) {
    if (!checkBufferNotNull(buffer)) {
        return false;
    }
    return ((buffer->writeIndex + 1) % buffer->length) == buffer->readIndex;
}

bool isBufferEmpty(const Buffer* buffer) {
    return buffer->readIndex == buffer->writeIndex;
}

bool isBufferEqualsToString(const Buffer* buffer, char* s) {
    int i = 0;
    char c  = *s;
    while (c != '\0') {
        if (getBufferElementsCount(buffer) <= i) {
            return false;
        }
        char cBuffer = bufferGetCharAtIndex(buffer, i);
        if (cBuffer != c) {
            return false;
        }
        s++;
        c = *s;
        i++;
    }
    if (getBufferElementsCount(buffer) != i) {
        return false;
    }
    return true;
}

int getBufferElementsCount(const Buffer* buffer) {
    int result = buffer->writeIndex - buffer->readIndex;
    if (result < 0) {
        result += buffer->length;
    }
    return result;
}

int getBufferCapacity(const Buffer* buffer) {
    return buffer->length - 1;
}

void bufferWriteChar(Buffer* buffer, char c) {
	bool isFull = isBufferFull(buffer);
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
    bool isEmpty = isBufferEmpty(buffer);
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
        return 0;
    }
}

char bufferGetCharAtIndex(const Buffer* buffer, int charIndex) {
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

bool bufferWriteCharAtIndex(const Buffer* buffer, int charIndex, char c) {
    int size = getBufferElementsCount(buffer);
    if (charIndex < size) {
        char* sPointer = (char*) buffer->s;
        // Shift to the right cell index
        sPointer += ((buffer->readIndex + charIndex) % buffer->length);
        *sPointer = c;

        return true;
    } else {
        // We must log the problem
        writeError(IO_BUFFER_ILLEGAL_INDEX_ACCESS);
        return false;
    }
}

void bufferClearLastChars(Buffer* buffer, unsigned char charToRemoveCount) {
    if (!checkBufferNotNull(buffer)) {
        return;
    }
    int size = getBufferElementsCount(buffer);
    if (charToRemoveCount <= size) {
        buffer->readIndex += charToRemoveCount;
        buffer->readIndex %= buffer->length;
    } else {
        writeError(IO_BUFFER_NOT_ENOUGH_DATA);
    }
}

void clearBuffer(Buffer* buffer) {
    if (!checkBufferNotNull(buffer)) {
        return;
    }
    buffer->writeIndex = 0;
    buffer->readIndex = 0;
}

void deepClearBuffer(Buffer* buffer) {
    if (!checkBufferNotNull(buffer)) {
        return;
    }
    unsigned int i;
    char* sPointer = (char*) buffer->s;
    for (i = 0; i < buffer->length; i++) {
        // Shift to the right cell index
        *sPointer = 0;
        sPointer++;
    }
    clearBuffer(buffer);
}

InputStream* getInputStream(Buffer* buffer) {
    if (!checkBufferNotNull(buffer)) {
        return NULL;
    }
    return &(buffer->inputStream);
}

OutputStream* getOutputStream(Buffer* buffer) {
    if (!checkBufferNotNull(buffer)) {
        return NULL;
    }
    return &(buffer->outputStream);
}

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
        char c = *sPointer;
        if (c == 0) {
            // To avoid [00] on Console
            append(outputStream, '#');
        }
        else {
            append(outputStream, c);
        }
        sPointer++;
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
        char c = bufferGetCharAtIndex(buffer, i);
        append(outputStream, c);
    }
    appendCRLF(outputStream);

}
