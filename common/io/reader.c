#include "reader.h"

#include <stdbool.h>

#include "filter.h"
#include "inputStream.h"
#include "printWriter.h"

#include "../../common/string/cenString.h"
#include "../../common/cmd/commonCommand.h"

#include "../../common/error/error.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/hexUtils.h"

/**
 * Contains all parse string manipulation which can be done on inputStream
 */

// READ METHODS

bool readBool(InputStream* inputStream) {
    char c = inputStream->readChar(inputStream);
    if (c == '0') {
        return false;
    }
    else if (c == '1') {
        return true;
    }
    writeError(IO_READER_NOT_BOOL_VALUE);
    return true;
}

char readFilteredChar(InputStream* inputStream) {
    char b0 = inputStream->readChar(inputStream);
    char result;
    if (filterBinaryToValueChar(b0, &result)) {
        return result;
    } else {
        writeError(IO_READER_READ_FILTERED_CHAR);
        OutputStream* debugOutputStream = getErrorOutputStreamLogger();
        appendString(debugOutputStream, "Char:");
        append(debugOutputStream, b0);
        appendString(debugOutputStream, "Hex:");
        appendHex2(debugOutputStream, b0);

        return FILTERED_RESULT;
    }
}

char readBinaryChar(InputStream* inputStream) {
    char result = inputStream->readChar(inputStream);
    return result;
}

int readBinaryWord(InputStream* inputStream) {
    char b0 = inputStream->readChar(inputStream);
    char b1 = inputStream->readChar(inputStream);
    return (b0 << 8) | b1;
}

int readHex(InputStream* inputStream) {
    char b0 = readFilteredChar(inputStream);
    int result = hex2CharToInt(0, b0);
    return result;
}

int readHex2(InputStream* inputStream) {
    char b0 = readFilteredChar(inputStream);
    char b1 = readFilteredChar(inputStream);
    int result = hex2CharToInt(b0, b1);
    return result;
}

signed int readSignedHex2(InputStream* inputStream) {
    char b0 = readFilteredChar(inputStream);
    char b1 = readFilteredChar(inputStream);
    signed int result = hex2CharToInt(b0, b1);
    if (result > 0x7F) {
        result -= 0x100;
    }
    return result;
}

long readHex4(InputStream* inputStream) {
    char b0 = readFilteredChar(inputStream);
    char b1 = readFilteredChar(inputStream);
    char b2 = readFilteredChar(inputStream);
    char b3 = readFilteredChar(inputStream);
    long result = hex4CharToLong(b0, b1, b2, b3);
    return result;
}

signed long readSignedHex4(InputStream* inputStream) {
    signed long result = readHex4(inputStream);
    if (result > 0x7FFF) {
        result -= 0x10000;
    }    
    return result;
}

long readHex6(InputStream* inputStream) {
    char b0 = readFilteredChar(inputStream);
    char b1 = readFilteredChar(inputStream);
    char b2 = readFilteredChar(inputStream);
    char b3 = readFilteredChar(inputStream);
    char b4 = readFilteredChar(inputStream);
    char b5 = readFilteredChar(inputStream);
    long result = hex6CharToLong(b0, b1, b2, b3, b4, b5);
    return result;
}

signed long readSignedHex6(InputStream* inputStream) {
    signed long result = readHex6(inputStream);
    if (result > 0x7FFFFF) {
        result -= 0x1000000;
    }
    return result;
}

float readHexFloat2(InputStream* inputStream, unsigned int digitPrecision) {
    float result = (float)readSignedHex2(inputStream);
    unsigned int i;
    for (i = 0; i < digitPrecision; i++) {
        result /= 10.0f;
    }
    return result;
}

float readHexFloat4(InputStream* inputStream, unsigned int digitPrecision) {
    float result = (float) readSignedHex4(inputStream);
    unsigned int i;
    for (i = 0; i < digitPrecision; i++) {
        result /= 10.0f;
    }
    return result;
}

float readHexFloat6(InputStream* inputStream, unsigned int digitPrecision) {
    float result = (float)readSignedHex6(inputStream);
    unsigned int i;
    for (i = 0; i < digitPrecision; i++) {
        result /= 10.0f;
    }
    return result;
}

void readHexFixedCharArray(InputStream* inputStream, const FixedCharArray* s) {
    int i;
    char* sPointer = (char*) s;
    for (i = 0; i < FIXED_CHAR_ARRAY_LENGTH; i++) {
        char c = (char) readHex2(inputStream);
        *sPointer = c;
        sPointer++;
    }
}


// CHECK METHODS

bool isAck(InputStream* inputStream) {
    char ack = inputStream->readChar(inputStream);
    return ack == COMMAND_ACK;
}

bool isChar(InputStream* inputStream, char expectedChar) {
    char readChar = inputStream->readChar(inputStream);
    return readChar == expectedChar;
}

bool checkIsAck(InputStream* inputStream) {
    char ack = inputStream->readChar(inputStream);
    if (ack != COMMAND_ACK) {
        writeError(IO_READER_CHECK_CHAR_PROBLEM);
        OutputStream* outputStream = getErrorOutputStreamLogger();
        appendString(outputStream, "\nCHK:ACK EXP:a \t but \t find:");
        append(outputStream, ack);
        println(outputStream);
        return false;
    }
    return true;
}

bool checkIsChar(InputStream* inputStream, char expectedChar) {
    char readChar = inputStream->readChar(inputStream);
    if (expectedChar != readChar) {
        writeError(IO_READER_CHECK_CHAR_PROBLEM);
        OutputStream* outputStream = getErrorOutputStreamLogger();
        appendString(outputStream, "\nCHK:CHAR:EXP:");
        append(outputStream, expectedChar);
        appendString(outputStream, " \t but \t find:");
        append(outputStream, readChar);
        println(outputStream);
        return false;
    }
    return true;
}

bool checkIsSeparator(InputStream* inputStream) {
    return checkIsChar(inputStream, '-');
}
