#include "binaryPrintWriter.h"

#include "printWriter.h"
#include "outputStream.h"

// BINARY

/**
 * @private
 */
unsigned int appendBinaryXX(OutputStream* outputStream, unsigned long value, unsigned length, unsigned groupBy) {
	unsigned int result = 0;
	int i;
    for (i = length - 1; i >= 0; i--) {
        if ((i + 1) % groupBy == 0) {
            appendSpace(outputStream);
			result++;
        }
        appendBool(outputStream, value & (1 << i));
		result++;
    }
	return result;
}

unsigned int appendBinary32(OutputStream* outputStream, unsigned long value, unsigned groupBy) {
    return appendBinaryXX(outputStream, value, 32, groupBy);
}

unsigned int appendBinary16(OutputStream* outputStream, unsigned int value, unsigned groupBy) {
	return appendBinaryXX(outputStream, value, 16, groupBy);
}

unsigned int appendBinary8(OutputStream* outputStream, unsigned char value, unsigned groupBy) {
	return appendBinaryXX(outputStream, value, 8, groupBy);
}
