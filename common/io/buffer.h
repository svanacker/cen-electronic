#ifndef BUFFER_H
#define BUFFER_H

#include <stdbool.h>
#include "../../common/commons.h"

#include "inputStream.h"
#include "outputStream.h"

/**
 * Defines a circular buffer which can be used to insert at the end, and remove at first (with inputStream / outputStream interface) in constant time.
 * This is an alternative to linked list which consumes more memory. We don't have to delete or insert in the middle, so this structure is perfect for us.
 * See following article http://en.wikipedia.org/wiki/Circular_buffer to understand the implementation
 */

/**
 * Define a buffer structure with an array of string, size, direction ...
 */
typedef struct {
    /** a name to identify the struct. */
    const char* name;
    /** A type if name are equals. */
	const char* type;
    /** A pointer on an array of char. */
    unsigned char (*s)[];
    /** The max length of the buffer. */
    unsigned int length;
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
 * Useful method to check if the buffer is not NULL (to prevent reset)
 * @param buffer
 * @return 
 */
bool checkBufferNotNull(const Buffer* buffer);

/**
 * Init the buffer and give it the port.
 * @param buffer the pointer on the buffer (simulates object programming)
 * @param an array of char to store value into the buffer
 * @param length the length of the array
 * @param name the name of the buffer (for debugging purpose)
 * @param type the type (as string) of the buffer (for debugging purpose). Often to distinguish IN or OUT buffer
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
void initBuffer(Buffer* buffer, unsigned char (*s)[], unsigned int length, const char* name, const char* type);

/**
 * Returns if a buffer is initialized or not.
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
 * TODO : Unit Test
 * Clear last "n" chars
 * @param buffer the buffer to clear (simulates object programming)
 * @param charToRemoveCount how many char must be removed
 * @throws IO_BUFFER_NULL if the pointer is NULL
 * @throws IO_BUFFER_NOT_ENOUGH_DATA
 */
void bufferClearLastChars(Buffer* buffer, unsigned char charToRemoveCount);

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
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
bool isBufferEmpty(const Buffer* buffer);

/**
 * Returns true if the buffer is equals exactly to the string, and contains no more and no less characters than the passed string into parameters
 * @param buffer the buffer (simulates object programming)
 * @param s the string to compare with the buffer
 * @returns true if the buffer is equals exactly to the string, and contains no more and no less characters than the passed string into parameters, false else
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
bool isBufferEqualsToString(const Buffer* buffer, char* s);

/**
 * Returns the number of elements.
 * @param buffer the buffer (simulates object programming)
 * @return the number of elements.
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
int getBufferElementsCount(const Buffer* buffer);

/**
 * Returns the total capacity to store Elements.
 * As we use a circular buffer, we only store n - 1 elements (where n is the size of the array), and not n, because if we use n, we cannot distinguish when buffer is empty or full (if readIndex == writeIndex).
 * @param buffer the buffer (simulates object programming)
 * @return the total capacity to store Elements.
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
int getBufferCapacity(const Buffer* buffer);

/**
 * Get and result the first char inserted (FIFO Stack)..
 * Shift the read buffer to the next char.
 * @param buffer the buffer (simulates object programming)
 * @return the the first char inserted (FIFO Stack).
 * @throws IO_BUFFER_NULL if the pointer is NULL
 * @throws IO_BUFFER_EMPTY if not enough char in the buffer
 */
unsigned char bufferReadChar(Buffer* buffer);

/**
 * Get the char at the specified index, but DO NOT shift to this index (=> DO NOT REMOVE the char).
 * @param buffer the buffer (simulates object programming)
 * @param charIndex the index of the char (0 = first char)
 * @return the char at the specified index
 * @throws IO_BUFFER_NULL if the pointer is NULL
 * @throws IO_BUFFER_NOT_ENOUGH_DATA if not enough char in the buffer
 */
unsigned char bufferGetCharAtIndex(const Buffer* buffer, int charIndex);

/**
 * Append a character to the buffer (FIFO buffer).
 * @param buffer the buffer (simulates object programming)
 * @param c the char which will be appended
 * @throws IO_BUFFER_NULL if the pointer is NULL
 * @throws IO_BUFFER_FULL if not enough space
 */
void bufferWriteChar(Buffer* buffer, unsigned char c);

/**
 * @param buffer the buffer (simulates object programming).
 * @param charIndex the index where we want to write
 * @param c the new value for the index
 * @return true if it was successfully updated, false else (not enough data, bad index ...)
 * @throws IO_BUFFER_NULL if the pointer is NULL
 * @throws IO_BUFFER_ILLEGAL_INDEX_ACCESS if we try to access to an non existing char
 */
bool bufferWriteCharAtIndex(const Buffer* buffer, int charIndex, unsigned char c);

/**
 * Get a compatible InputStream associated to the buffer.
 * @param buffer the buffer (simulates object programming)
 * @return the inputStream associated to the buffer.
 * @throws IO_BUFFER_NULL if the pointer is NULL
 */
InputStream* getInputStream(Buffer* buffer);

/**
 * Get a compatible OutputStream with the buffer.
 * @param buffer the buffer (simulates object programming)
 * @return the outputStream associated to the buffer.
 * @throws IO_BUFFER_NULL if the pointer is NULL 
 */
OutputStream* getOutputStream(Buffer* buffer);


#endif
