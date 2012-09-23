#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H

/**
 * Management of OutputStream to send some binary data instead of hexadecimal value with Strings.
 */

#include "outputStream.h"

/**
 * Simple int converted into 2 bytes (high and low bytes in this order).
 * @param value a 16 bit value
 */
void appendWord(OutputStream* outputStream, unsigned int value);

/**
 * Simple byte with no conversion.
 */
void appendByte(OutputStream* outputStream, char value);



#endif

