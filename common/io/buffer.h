#ifndef BUFFER_H
#define BUFFER_H

#include "../../common/commons.h"

#include "inputStream.h"
#include "outputStream.h"

/**
 * Defines a circular buffer which can be used to insert at the end, and remove at first (with inputStream / outputStream interface) in constant time.
 * This is an alternatif to linked list which consumes more memory. We don't have to delete or insert in the middle, so this structure is perfect for us.
 * See following article http://en.wikipedia.org/wiki/Circular_buffer to understand the implementation
 * @author svanacker
 */

/**
 * Define a buffer structure with an array of string, size, direction ...
 */
typedef struct {
    /** a name to identify the struct. */
    char* name;
    /** A type if name are equals. */
    char* type;
    /** A pointer on an array of char. */
    char (*s)[];
	/** The max length of the buffer. */
	unsigned char length;
    /** The pointer used to write Data (we write at the end). */
    unsigned int writeIndex;
    /** The pointer used to read (we read at the begin). */
    unsigned int readIndex;
    /** the corresponding outputStream. */
    OutputStream outputStream;
    /** the corresponding inputStream. */
    InputStream inputStream;
} Buffer;

/**
 * Init the buffer and give it the port.
 * @param buffer the pointer on the buffer
 */
void initBuffer(Buffer* buffer, char (*s)[], unsigned char length, char* name, char* type);

/**
 * Clears the buffer.
 * @param buffer the buffer to clear
 */
void clearBuffer(Buffer* buffer);

/**
 * Do a deep clear of buffer (write 0 on all cells of array);
 */
void deepClearBuffer(Buffer* buffer);

/**
 * Returns TRUE if the buffer is full, false else.
 */
BOOL isBufferFull(const Buffer* buffer);

/**
 * Returns TRUE if the buffer is empty, false else.
 */
BOOL isBufferEmpty(const Buffer* buffer);

/**
 * Returns the number of elements
 */
int getBufferElementsCount(const Buffer* buffer);

/**
 * Get and result the first char inserted (FIFO Stack).
 * Shift the read buffer to the next char.
 */
char bufferReadChar(Buffer* buffer);

/**
 * Get the first char, but DO NOT shift to the next char.
 */
char bufferGetFirstChar(Buffer* buffer);

/**
 * Append a character to the buffer (FIFO buffer).
 * @param c the char which will be appended
 */
void bufferWriteChar(Buffer* buffer, char c);

/**
 * Get a compatible InputStream with the buffer.
 */
InputStream* getInputStream(Buffer* buffer);

/**
 * Get a compatible OutputStream with the buffer.
 */
OutputStream* getOutputStream(Buffer* buffer);

/**
 * Print the buffer in a debug mode, with all variables.
 */
void printDebugBuffer(OutputStream* outputStream, Buffer* buffer);

#endif
