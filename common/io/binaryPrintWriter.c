#include "binaryPrintWriter.h"

#include "printWriter.h"

// BINARY

/**
 * @private
 */
void appendBinaryXX(OutputStream* outputStream, unsigned long value, unsigned length, unsigned groupBy) {
    int i;
    for (i = length - 1; i >= 0; i--) {
        if ((i + 1) % groupBy == 0) {
            append(outputStream, ' ');
        }
		appendBOOL(outputStream, value & (1 << i));
    }
}

void appendBinary32(OutputStream* outputStream, unsigned long value, unsigned groupBy) {
    appendBinaryXX(outputStream, value, 32, groupBy);
}

void appendBinary16(OutputStream* outputStream, unsigned int value, unsigned groupBy) {
    appendBinaryXX(outputStream, value, 16, groupBy);
}

void appendBinary8(OutputStream* outputStream, unsigned char value, unsigned groupBy) {
    appendBinaryXX(outputStream, value, 8, groupBy);
}
