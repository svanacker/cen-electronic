#include "binaryWriter.h"

#include "outputStream.h"

void appendWord(OutputStream* outputStream, unsigned int value) {
	append(outputStream, (value >> 8) & 0xFF);
	append(outputStream, value & 0xFF);
}

void appendDoubleWord(OutputStream* outputStream, unsigned long value) {
	append(outputStream, (value >> 24) & 0xFF);
	append(outputStream, (value >> 16) & 0xFF);
	append(outputStream, (value >> 8) & 0xFF);
	append(outputStream, value & 0xFF);
}


void appendByte(OutputStream* outputStream, char value) {
	append(outputStream, value);
}
