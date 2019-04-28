#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H

/**
 * Management of OutputStream to send some binary data instead of hexadecimal value with Strings.
 */
#include "outputStream.h"

/**
 * Simple int converted into 2 bytes (high and low bytes in this order).
 * @param outputStream the outputStream in which we write the value
 * @param value a 16 bit value
 */
void appendWord(OutputStream* outputStream, unsigned int value);

/**
 * Simple long converted into 4 bytes (high and low bytes in this order).
 * @param outputStream the outputStream in which we write the value
 * @param value a 32 bit value
 */
void appendDoubleWord(OutputStream* outputStream, unsigned long value);

/**
 * Simple byte with no conversion.
 * @param outputStream the outputStream in which we write the value
 * @param value the value that we want to write
 */
void appendByte(OutputStream* outputStream, unsigned char value);

#endif
