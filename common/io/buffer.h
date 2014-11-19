#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>
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
 * @param buffer the pointer on the buffer (simulates object programming)
 * @param an array of char to store value into the buffer
 * @param length the length of the array
 * @param name the name of the buffer (for debugging purpose)
 * @param type the type (as string) of the buffer (for debugging purpose). Often to distinguish IN or OUT buffer
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
void initBuffer(Buffer* buffer, char (*s)[], unsigned char length, char* name, char* type);

/**
 * Retuns if a buffer is initialized or not.
 * @param buffer the pointer on buffer (simulates object programming)
 * @return true if the buffer is initialized, false else
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
bool isBufferInitialized(Buffer* buffer);

/**
 * Clears the buffer.
 * @param buffer the buffer to clear (simulates object programming)
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
void clearBuffer(Buffer* buffer);

/**
 * Do a deep clear of buffer (write 0 on all cells of array);
 * @param buffer the buffer to clear very deeply (simulates object programming)
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
void deepClearBuffer(Buffer* buffer);

/**
 * Returns true if the buffer is full, false else.
 * @param buffer the buffer (simulates object programming)
 * @return true if the buffer is full, false else
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
bool isBufferFull(const Buffer* buffer);

/**
 * Returns true if the buffer is empty, false else.
 * @param buffer the buffer (simulates object programming)
 * @return true if the buffer is empty, false else
 */
bool isBufferEmpty(const Buffer* buffer);

/**
 * Returns true if the buffer is equals exactly to the string, and contains no more and no less characters than the passed string into parameters
 * @param buffer the buffer (simulates object programming)
 * @param s the string to compare with the buffer
 * @returns true if the buffer is equals exactly to the string, and contains no more and no less characters than the passed string into parameters, false else
 */
bool isBufferEqualsToString(const Buffer* buffer, char* s);

/**
 * Returns the number of elements.
 * @param buffer the buffer (simulates object programming)
 * @return the number of elements.
 */
int getBufferElementsCount(const Buffer* buffer);

/**
 * Returns the total capacity to store Elements.
 * As we use a circular buffer, we only store n - 1 elements (where n is the size of the array), and not n, because if we use n, we cannot distinguish when buffer is empty or full (if readIndex == writeIndex).
 * @param buffer the buffer (simulates object programming)
 * @return the total capacity to store Elements.
 */
int getBufferCapacity(const Buffer* buffer);

/**
 * Get and result the first char inserted (FIFO Stack)..
 * Shift the read buffer to the next char.
 * @param buffer the buffer (simulates object programming)
 * @return the the first char inserted (FIFO Stack).
 */
char bufferReadChar(Buffer* buffer);

/**
 * Get the char at the specified index, but DO NOT shift to this index (=> DO NOT REMOVE the char).
 * @param buffer the buffer (simulates object programming)
 * @param charIndex the index of the char (0 = first char)
 * @return the char at the specified index
 */
char bufferGetCharAtIndex(const Buffer* buffer, int charIndex);

/**
 * Append a character to the buffer (FIFO buffer).
 * @param buffer the buffer (simulates object programming)
 * @param c the char which will be appended
 */
void bufferWriteChar(Buffer* buffer, char c);

/**
 * Get a compatible InputStream associated to the buffer.
 * @param buffer the buffer (simulates object programming)
 * @return the inputStream associated to the buffer.
 */
InputStream* getInputStream(Buffer* buffer);

/**
 * Get a compatible OutputStream with the buffer.
 * @param buffer the buffer (simulates object programming)
 * @return the outputStream associated to the buffer.
 */
OutputStream* getOutputStream(Buffer* buffer);

/**
 * Print the buffer in a debug mode, with all variables.
 * @param outputStream the output stream (often debug) where we writes some values
 * @param buffer the buffer (simulates object programming)
 */
void printDebugBuffer(OutputStream* outputStream, Buffer* buffer);

#endif
