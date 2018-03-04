#include "instructionType.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

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

unsigned int addInstructionTypeTableData(OutputStream* outputStream, enum InstructionType instructionType, unsigned int columnSize) {
	appendTableSeparator(outputStream);
	appendSpace(outputStream);
	unsigned int length = appendInstructionTypeAsString(outputStream, instructionType);
	return length + appendSpaces(outputStream, columnSize - length) + 2;
}

