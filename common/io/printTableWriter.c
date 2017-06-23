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

unsigned int appendStringHeader(OutputStream* outputStream, char* s) {
    if (outputStream == NULL) {
        return 0;
    }
	appendTableSeparator(outputStream);
	append(outputStream, ' ');
	unsigned int result = appendString(outputStream, s);
	append(outputStream, ' ');
	return result + 3;
}

unsigned int appendRepeatedChars(OutputStream* outputStream, char c, int count) {
	int i;
	for (i = 0; i < count; i++) {
		append(outputStream, c);
	}
	return count;
}

unsigned int appendRepeatedDash(OutputStream* outputStream, int count) {
	return appendRepeatedChars(outputStream, '-', count);
}

unsigned int appendSpaces(OutputStream* outputStream, int count) {
	return appendRepeatedChars(outputStream, ' ', count);
}

void appendStringTableData(OutputStream* outputStream, const char* s, int totalLength) {
	appendTableSeparator(outputStream);
	append(outputStream, ' ');
	int length = appendString(outputStream, s);
	append(outputStream, ' ');
	appendSpaces(outputStream, totalLength - length);
}

void appendCharTableData(OutputStream* outputStream, const char c, int totalLength) {
	appendTableSeparator(outputStream);
	append(outputStream, ' ');
	append(outputStream, c);
	appendSpaces(outputStream, totalLength - 1);
}


