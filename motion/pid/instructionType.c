#include "instructionType.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

unsigned int appendInstructionTypeAsString(OutputStream* outputStream, enum InstructionType instructionType) {
	if (instructionType == THETA) {
		return appendString(outputStream, "THETA");
	}
	else if (instructionType == ALPHA) {
		return appendString(outputStream, "ALPHA");
	}
	else {
		append(outputStream, '?');
		return 1;
	}
	return 0;
}
