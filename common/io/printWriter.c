#include <stdlib.h>

#include "printWriter.h"
#include "outputStream.h"

#include "../../common/commons.h"
#include "../../common/error/error.h"

/**
 * Contains all string manipulations which writes data to an outputStream
 */

// STRINGS

void append(OutputStream* outputStream, char c) {
    if (outputStream == NULL) {
        return;
    }
    outputStream->writeChar(outputStream, c);
}

unsigned int appendBool(OutputStream* outputStream, bool b) {
    if (b) {
        append(outputStream, '1');
    } else {
        append(outputStream, '0');
    }
	return 1;
}

unsigned int appendBoolAsString(OutputStream* outputStream, bool b) {
    if (b) {
        return appendString(outputStream, "true");
    }
    else {
        return appendString(outputStream, "false");
    }
}

void appendSeparator(OutputStream* outputStream) {
    append(outputStream, '-');
}

void appendSpace(OutputStream* outputStream) {
	append(outputStream, ' ');
}

unsigned int appendString(OutputStream* outputStream, const char* s) {
    unsigned int result = 0;
	if (s == NULL) {
        return result;
    }
    while (*s != '\0') {
        append(outputStream, *s++);
		result++;
    }
	return result;
}

unsigned int appendHexFixedCharArray(OutputStream* outputStream, const FixedCharArray* s) {
	unsigned int i;
	char* sPointer = (char*)s;
	for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
		char c = *sPointer;
		appendHex2(outputStream, c);
		sPointer++;
	}
	return FIXED_CHAR_ARRAY_LENGTH * 2;
}

unsigned int appendFixedCharArray(OutputStream* outputStream, const FixedCharArray* s) {
    unsigned int i;
    char* sPointer = (char*)s;
    for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
        char c = *sPointer;
        append(outputStream, c);
        sPointer++;
    }
	return FIXED_CHAR_ARRAY_LENGTH;
}

unsigned int appendStringCRLF(OutputStream* outputStream, const char* s) {
    unsigned int result;
	result = appendString(outputStream, s);
    result += appendCRLF(outputStream);
	return result;
}

unsigned int appendCR(OutputStream* outputStream) {
    append(outputStream, CR);
	return 1;
}

unsigned int appendLF(OutputStream* outputStream) {
    append(outputStream, LF);
	return 1;
}

unsigned int appendCRLF(OutputStream* outputStream) {
    append(outputStream, CR);
    append(outputStream, LF);
	return 2;
}

unsigned int println(OutputStream* outputStream) {
    return appendLF(outputStream);
}

unsigned int appendAck(OutputStream* outputStream) {
    append(outputStream, ACK);
	return 1;
}

// BUFFER

unsigned int printBuffer(OutputStream* outputStream, Buffer* buffer) {
    unsigned int result = 0;
	while(!isBufferEmpty(buffer)) {
        char c = bufferReadChar(buffer);
        append(outputStream, c);
		result++;
    }
	return result;
}

// HEXADECIMAL

unsigned char convertToHex(char c) {
    // Value between 0 and 9
    if (c < 10) {
        return c + 48;
    }
    else if (c < 16) {
        // Value between A and F
        // (65 - 10 + c)
        return c + 55;
    }
    writeError(PRINT_WRITER_NOT_HEX_VALUE);
    return 0;
}

bool appendHex(OutputStream* outputStream, char c) {
    unsigned char hexChar = convertToHex(c);
    if (hexChar != 0) {
        append(outputStream, hexChar);
        return true;
    }
    return false;
}

void internalAppendHex(OutputStream* outputStream, signed long value, int shiftMax) {
    int i;
    for (i = shiftMax; i >= 0; i -= 4) {
        appendHex(outputStream, (value >> i) & 0xF);
    }
}

void appendHex2(OutputStream* outputStream, char value) {
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

// FLOAT

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
    float decimalValue;
    long decimalValueLong;

    if (value < 0) {
        decimalValue = ((value - (long) value) * -1000);
        append(stream, '-');
        result++;
        result += appendDec(stream, -(long) value);
    } else {
        decimalValue = ((value - (long) value) * 1000);
        result += appendDec(stream, (long) value);
    }
    decimalValueLong = (long) decimalValue;

    if (decimalValue - decimalValueLong > 0.5f) {
        decimalValueLong++;
    }

    append(stream, DECIMAL_SEPARATOR);
    result++;

    if (decimalValueLong < 100) {
        append(stream, '0');
        if (decimalValueLong < 10) {
            append(stream, '0');
        }
        if (decimalValueLong < 1 && decimalValueLong > 0) {
            append(stream, '0');
        }
    }
    result += appendDec(stream, decimalValueLong);

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
