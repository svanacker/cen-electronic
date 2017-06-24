/**
* Contains all string manipulations to write table writer.
*/
#include <stdlib.h>

#include "outputStream.h"
#include "printTableWriter.h"
#include "printWriter.h"

#include "../../common/commons.h"
#include "../../common/error/error.h"

void appendTableSeparator(OutputStream* outputStream) {
	append(outputStream, '|');
}

void appendStringHeader(OutputStream* outputStream, char* s, int totalLength) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendString(outputStream, s);
	appendSpace(outputStream);
	appendSpaces(outputStream, totalLength - length);
}

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

unsigned int appendStringTableData(OutputStream* outputStream, const char* s, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendString(outputStream, s);
	appendSpace(outputStream);
	return length + appendSpaces(outputStream, columnSize - length) + 3;
}

unsigned int appendDecTableData(OutputStream* outputStream, const value, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	int length = appendDec(outputStream, value);
	appendSpace(outputStream);
	return length + appendSpaces(outputStream, columnSize - length) + 3;
}

unsigned int appendCharTableData(OutputStream* outputStream, const char c, int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	append(outputStream, c);
	appendSpace(outputStream);
	// lenght of char is equal to 1
	return appendSpaces(outputStream, columnSize - 1) + 4;
}


