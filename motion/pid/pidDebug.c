#include "pidDebug.h"

#include "instructionType.h"
#include "motionInstruction.h"
#include "pid.h"
#include "pidMotion.h"

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"


#define PID_DEBUG_INDEX_COLUMN_LENGTH						4
#define PID_DEBUG_INSTRUCITON_TYPE_COLUMN_LENGTH			6
#define PID_DEBUG_A_COLUMN_LENGTH							3
#define PID_DEBUG_SPEED_COLUMN_LENGTH						3
#define PID_DEBUG_SPEED_MAX_COLUMN_LENGTH					5
#define PID_DEBUG_T1_COLUMN_LENGTH							4
#define PID_DEBUG_T2_COLUMN_LENGTH							4
#define PID_DEBUG_T3_COLUMN_LENGTH							4
#define PID_DEBUG_P1_COLUMN_LENGTH							6
#define PID_DEBUG_P2_COLUMN_LENGTH							6
#define PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH				6
#define PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH				8
#define PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH		15
#define PID_DEBUG_PID_TYPE_COLUMN_LENGTH		            10
#define PID_DEBUG_LAST_COLUMN_LENGTH		                0

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

/**
* Private.
*/
void printMotionInstructionHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Idx", PID_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "T/A", PID_DEBUG_INSTRUCITON_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "a", PID_DEBUG_A_COLUMN_LENGTH);
	appendStringHeader(outputStream, "s", PID_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "sMax", PID_DEBUG_SPEED_MAX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t1", PID_DEBUG_T1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t2", PID_DEBUG_T2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t3", PID_DEBUG_T3_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p1", PID_DEBUG_P1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p2", PID_DEBUG_P2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p3", PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "profile", PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "motionParamType", PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "pidType", PID_DEBUG_PID_TYPE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printMotionInstructionLine(OutputStream* outputStream, int index, enum InstructionType instructionType, MotionInstruction* motionInstruction) {
	appendDecTableData(outputStream, index, PID_DEBUG_INDEX_COLUMN_LENGTH);
	addInstructionTypeTableData(outputStream, instructionType, PID_DEBUG_INSTRUCITON_TYPE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->a, PID_DEBUG_A_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->speed, PID_DEBUG_SPEED_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->speedMax, PID_DEBUG_SPEED_MAX_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->t1, PID_DEBUG_T1_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->t2, PID_DEBUG_T2_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->t3, PID_DEBUG_T3_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->p1, PID_DEBUG_P1_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->p2, PID_DEBUG_P2_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionInstruction->nextPosition, PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH);
	addMotionProfileTypeTableData(outputStream, motionInstruction->profileType, PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH);
	addMotionParameterTypeTableData(outputStream, motionInstruction->motionParameterType, PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH);
	addPidTypeTableData(outputStream, motionInstruction->pidType, PID_DEBUG_PID_TYPE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);
}

void printMotionInstructionTable(OutputStream* outputStream) {
	printMotionInstructionHeader(outputStream);
	int i;
	int count = getMotionDefinitionCount();
	for (i = 0; i < count; i++) {
		PidMotionDefinition* pidMotionDefinition = getMotionDefinition(i);
		MotionInstruction* theta = &(pidMotionDefinition->inst[THETA]);
		printMotionInstructionLine(outputStream, i, THETA, theta);
		MotionInstruction* alpha = &(pidMotionDefinition->inst[ALPHA]);
		printMotionInstructionLine(outputStream, i, ALPHA, alpha);
		appendTableHeaderSeparatorLine(outputStream);
	}
}

