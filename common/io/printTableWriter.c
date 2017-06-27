/**
* Contains all string manipulations to write table writer.
*/
#include <stdlib.h>

#include "outputStream.h"
#include "printTableWriter.h"
#include "printWriter.h"

#include "../../common/commons.h"
#include "../../common/error/error.h"


// COMMON

unsigned int appendRepeatedChars(OutputStream* outputStream, char c, int count) {
	int i;
	for (i = 0; i < count; i++) {
		append(outputStream, c);
	}
	if (count < 0) {
		return 0;
	}
	return count;
}

unsigned int appendDashes(OutputStream* outputStream, int count) {
	return appendRepeatedChars(outputStream, '-', count);
}

unsigned int appendSpaces(OutputStream* outputStream, int count) {
	return appendRepeatedChars(outputStream, ' ', count);
}

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

unsigned int appendDecTableData(OutputStream* outputStream, const int value, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendDec(outputStream, value);
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

unsigned int appendCharTableData(OutputStream* outputStream, const char c, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	append(outputStream, c);
	// lenght of char is equal to 1
	return appendSpaces(outputStream, columnSize - 1) + 3;
}


