/**
* Contains all string manipulations to write table writer.
*/
#include <stdlib.h>
#include <stdbool.h>

#include "outputStream.h"
#include "binaryPrintWriter.h"
#include "printTableWriter.h"
#include "printWriter.h"

#include "../../common/commons.h"
#include "../../common/error/error.h"



// TABLE HEADER

void appendTableHeaderSeparatorLine(OutputStream* outputStream) {
	appendDashes(outputStream, PRINT_TABLE_WRITER_DEFAULT_PAGE_CHAR_WIDTH);
	println(outputStream);
}

void appendTableSeparator(OutputStream* outputStream) {
	append(outputStream, '|');
}

void appendStringHeader(OutputStream* outputStream, char* s, int totalLength) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendString(outputStream, s);
	appendSpaces(outputStream, totalLength - length);
}

void appendStringAndDecHeader(OutputStream* outputStream, char* s, int value, int totalLength) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendString(outputStream, s);
    length += appendDec(outputStream, value);
    appendSpaces(outputStream, totalLength - length);
}

void appendEndOfTableColumn(OutputStream* outputStream, int columnSize) {
	appendSpaces(outputStream, columnSize);
	appendTableSeparator(outputStream);
	println(outputStream);
}

// TABLE DATA

unsigned int appendStringTableData(OutputStream* outputStream, const char* s, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendString(outputStream, s);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int appendFixedCharArrayTableData(OutputStream* outputStream, FixedCharArray* s, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendFixedCharArray(outputStream, s);
	return length + appendSpaces(outputStream, columnSize - length) + FIXED_CHAR_ARRAY_LENGTH + 2;
}

unsigned int appendHexFixedCharArrayTableData(OutputStream* outputStream, FixedCharArray* s, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendHexFixedCharArray(outputStream, s);
	return length + appendSpaces(outputStream, columnSize - length) + FIXED_CHAR_ARRAY_LENGTH + 2;
}

unsigned int appendDecTableData(OutputStream* outputStream, const int value, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendDec(outputStream, value);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int appendDecfTableData(OutputStream* outputStream, const float value, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendDecf(outputStream, value);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int appendBoolTableData(OutputStream* outputStream, const bool value, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendBool(outputStream, value);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int appendBoolAsStringTableData(OutputStream* outputStream, const bool value, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    int length = appendBoolAsString(outputStream, value);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}

unsigned int appendHex2TableData(OutputStream* outputStream, char value, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	appendHex2(outputStream, value);
	// length of hex2 = 2
	return appendSpaces(outputStream, columnSize - 2) + 4;
}

unsigned int appendHex4TableData(OutputStream* outputStream, signed int value, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	appendHex4(outputStream, value);
	// length of hex4 = 4
	return appendSpaces(outputStream, columnSize - 4) + 6;
}

unsigned int appendHexFloat4TableData(OutputStream* outputStream, float value, unsigned int digitPrecision, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    appendHexFloat4(outputStream, value, digitPrecision);
    // length of hexFloat4 = 4
    return appendSpaces(outputStream, columnSize - 4) + 6;
}


unsigned int appendHex6TableData(OutputStream* outputStream, signed long value, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	appendHex6(outputStream, value);
	// length of hex6 = 6
	return appendSpaces(outputStream, columnSize - 6) + 8;
}

unsigned int appendHexFloat6TableData(OutputStream* outputStream, float value, unsigned int digitPrecision, int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    appendHexFloat6(outputStream, value, digitPrecision);
    // length of hexFloat6 = 6
    return appendSpaces(outputStream, columnSize - 6) + 8;
}

unsigned int appendBinary16TableData(OutputStream* outputStream, unsigned int value, unsigned int groupBy, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendBinary16(outputStream, value, groupBy);
	return appendSpaces(outputStream, columnSize - length) + 3;
}

unsigned int appendBinary8TableData(OutputStream* outputStream, unsigned int value, unsigned int groupBy, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendBinary8(outputStream, value, groupBy);
	return appendSpaces(outputStream, columnSize - length) + 3;
}

unsigned int appendCharTableData(OutputStream* outputStream, const char c, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	append(outputStream, c);
	// lenght of char is equal to 1
	return appendSpaces(outputStream, columnSize - 1) + 3;
}

