#include <stdlib.h>

#include "printWriter.h"
#include "outputStream.h"

#include "../../common/commons.h"

/**
 * Contains all string manipulations which writes data to an outputStream
 * @author svanacker
 */

// STRINGS

void append(OutputStream* outputStream, char c) {
	if (outputStream == NULL) {
		return;
	}
    outputStream->writeChar(outputStream, c);
}

void appendBOOL(OutputStream* outputStream, BOOL b) {
    if (b) {
        append(outputStream, '1');
    } else {
        append(outputStream, '0');
    }
}

void appendSeparator(OutputStream* outputStream) {
    append(outputStream, '-');
}

void appendString(OutputStream* outputStream, const char* s) {
    while (*s != '\0') {
        append(outputStream, *s++);
    }
}

void appendStringCRLF(OutputStream* outputStream, const char* s) {
    appendString(outputStream, s);
    appendCRLF(outputStream);
}

void appendCRLF(OutputStream* outputStream) {
    append(outputStream, CR);
    append(outputStream, LF);
}

void println(OutputStream* outputStream) {
    appendCRLF(outputStream);
}

void appendAck(OutputStream* outputStream) {
    append(outputStream, ACK);
}

// BUFFER

void printBuffer(OutputStream* outputStream, Buffer* buffer) {
	while(!isBufferEmpty(buffer)) {
        unsigned char c = bufferReadChar(buffer);
        append(outputStream, c);
    }
}

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

// HEXADECIMAL

void appendHex(OutputStream* outputStream, unsigned char c) {
    // Value between 0 and 9
    if (c < 10) {
        c += 48;
    } else {
        // Value between A and F
        // (65 - 10 + c)
        c += 55;
    }
    append(outputStream, c);
}

void internalAppendHex(OutputStream* outputStream, signed long value, int shiftMax) {
    int i;
    for (i = shiftMax; i >= 0; i -= 4) {
        appendHex(outputStream, (value >> i) & 0xF);
    }
}

void appendHex2(OutputStream* outputStream, unsigned char value) {
    internalAppendHex(outputStream, value, 4);
}

void appendHex3(OutputStream* outputStream, signed int value) {
	internalAppendHex(outputStream, value, 8);
}

void appendHex4(OutputStream* outputStream, signed int value) {
    internalAppendHex(outputStream, value, 12);
}

void appendHex5(OutputStream* outputStream, signed int value) {
    internalAppendHex(outputStream, value, 16);
}

void appendHex6(OutputStream* outputStream, signed long value) {
	internalAppendHex(outputStream, value, 20);
}

void appendHex8(OutputStream* outputStream, signed long value) {
    internalAppendHex(outputStream, value, 28);
}

void appendHexFloat4(OutputStream* stream, float value, float factorToTrunc) {
    signed long longValue = (signed long) (value * factorToTrunc);
    appendHex4(stream, longValue);
}

void appendHexFloat8(OutputStream* stream, float value, float factorToTrunc) {
    signed long longValue = (signed long) (value * factorToTrunc);
    appendHex4(stream, longValue);
}

// DECIMAL CONVERSION

int appendDec(OutputStream* stream, signed long value) {
    char num[11]; // 2^31 plus sign
    int pos = 0;
    int nchars = 0;

    if (value < 0) {
        append(stream, '-');
        value = -value;
        nchars++;
    } else if (value == 0) {
        append(stream, '0');
        nchars++;
        return nchars;
    }

    while (value != 0) {
        char c = value % 10;
        value = value / 10;
        num[pos++] = c + '0';
    }

    if (pos == 0)
        num[pos++] = '0';

    while (--pos >= 0) {
        append(stream, num[pos]);
        nchars++;
    }

    return nchars;
}

int appendDecf(OutputStream* stream, float value) {
    int result = 0;
    unsigned long decimalValue;

    if (value < 0) {
        decimalValue = (value - (long) value) * -1000;
        append(stream, '-');
        result++;
        result += appendDec(stream, -(long) value);
    } else {
        decimalValue = (value - (long) value) * 1000;
        result += appendDec(stream, (long) value);
    }

    append(stream, DECIMAL_SEPARATOR);
    result++;

    if (decimalValue < 100) {
        append(stream, '0');
        if (decimalValue < 10) {
            append(stream, '0');
        }
        if (decimalValue < 1) {
            append(stream, '0');
        }
    }
    result += appendDec(stream, decimalValue);

    return result;
}

// AGGREGATION


void appendStringAndDecf(OutputStream* stream, const char* s, float value) {
	appendString(stream, s);
    appendDecf(stream, value);
}

void appendStringAndDec(OutputStream* stream, const char* s, long value) {
    appendString(stream, s);
    appendDec(stream, value);
}

void appendKeyAndName(OutputStream* stream, const char* key, const char* name) {
    appendString(stream, key);
    appendString(stream, name);
}

