#include "reader.h"

#include "filter.h"
#include "inputStream.h"
#include "printWriter.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/error/error.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/math/hexUtils.h"

/**
 * Contains all parse string manipulation which can be done on inputStream
 * @author svanacker
 */

// READ METHODS

char readFilteredChar(InputStream* inputStream) {
    unsigned char b0 = inputStream->readChar(inputStream);
    unsigned char result;
    if (filterBinaryToValueChar(b0, &result)) {
        return result;
    } else {
        writeError(IO_READER_READ_FILTERED_CHAR);
		appendString(getErrorOutputStreamLogger(), "Char:");
        append(getErrorOutputStreamLogger(), b0);
		appendString(getErrorOutputStreamLogger(), "Hex:");
        appendHex2(getErrorOutputStreamLogger(), b0);

        return -1;
    }
}

int readHex(InputStream* inputStream) {
    char b1 = readFilteredChar(inputStream);
    int result = hex2CharToInt(0, b1);
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
    int result = hex4CharToLong(b0, b1, b2, b3);
    return result;
}

signed long readSignedHex4(InputStream* inputStream) {
	signed long result = readHex4(inputStream);
	if (result > 0x7FFF) {
		result -= 0x10000;
	}	
	return result;
}

float readHex6(InputStream* inputStream) {
    char b0 = readFilteredChar(inputStream);
    char b1 = readFilteredChar(inputStream);
    char b2 = readFilteredChar(inputStream);
    char b3 = readFilteredChar(inputStream);
    char b4 = readFilteredChar(inputStream);
    char b5 = readFilteredChar(inputStream);
    float result = hex6CharToFloat(b0, b1, b2, b3, b4, b5);
    return result;
}


// CHECK METHODS

BOOL isAck(InputStream* inputStream) {
    char ack = inputStream->readChar(inputStream);
    return ack == COMMAND_ACK;
}

BOOL isChar(InputStream* inputStream, char expectedChar) {
    char readChar = inputStream->readChar(inputStream);
    return readChar == expectedChar;
}

BOOL checkIsAck(InputStream* inputStream) {
    char ack = inputStream->readChar(inputStream);
    if (ack != COMMAND_ACK) {
        OutputStream* outputStream = getErrorOutputStreamLogger();
        appendString(outputStream, " CHK:ACK:EXP:a:find:");
        append(outputStream, ack);
    }
    return TRUE;
}

BOOL checkIsChar(InputStream* inputStream, char expectedChar) {
    char readChar = inputStream->readChar(inputStream);
    if (expectedChar != readChar) {
        OutputStream* outputStream = getErrorOutputStreamLogger();
        appendString(outputStream, " CHK:CHAR:EXP:");
        append(outputStream, expectedChar);
        appendString(outputStream, ":find:");
        append(outputStream, readChar);
    }
    return TRUE;
}
