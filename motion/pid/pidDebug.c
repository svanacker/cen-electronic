#include "pidDebug.h"

#include "instructionType.h"
#include "motionInstruction.h"
#include "pid.h"
#include "pidType.h"
#include "pidTypeDebug.h"
#include "pidMotion.h"
#include "pidMotionDefinitionState.h"
#include "computer/pidComputer.h"
#include "../parameters/motionParameterTypeDebug.h"
#include "../extended/bsplineDebug.h"

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/printTableWriter.h"

// PID GENERAL DATA
#define PID_DEBUG_KEY_COLUMN_LENGTH                         25
#define PID_DEBUG_VALUE_COLUMN_LENGTH                       5
#define PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH		        60

// PID MOTION INSTRUCTION
#define PID_DEBUG_INDEX_COLUMN_LENGTH						4
#define PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH			6
#define PID_DEBUG_A_COLUMN_LENGTH							6
#define PID_DEBUG_INITIAL_SPEED_COLUMN_LENGTH				6
#define PID_DEBUG_SPEED_COLUMN_LENGTH						6
#define PID_DEBUG_SPEED_MAX_COLUMN_LENGTH					6
#define PID_DEBUG_END_SPEED_COLUMN_LENGTH				    6
#define PID_DEBUG_T1_COLUMN_LENGTH							6
#define PID_DEBUG_T2_COLUMN_LENGTH							6
#define PID_DEBUG_T3_COLUMN_LENGTH							6
#define PID_DEBUG_P1_COLUMN_LENGTH							6
#define PID_DEBUG_P2_COLUMN_LENGTH							6
#define PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH				6
#define PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH				8
#define PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH		16
#define PID_DEBUG_PID_TYPE_COLUMN_LENGTH		            7
#define PID_DEBUG_LAST_COLUMN_LENGTH		                0

/**
 * Print the global value for motion
 * @Private
 */
void printMotionGlobalVarsData(OutputStream* outputStream, PidMotion* pidMotion) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Key", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Value", PID_DEBUG_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);

	appendStringTableData(outputStream, "readIndex", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendDecTableData(outputStream, pidMotion->motionReadIndex, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

	appendStringTableData(outputStream, "writeIndex", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendDecTableData(outputStream, pidMotion->motionWriteIndex, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

	appendStringTableData(outputStream, "length", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendDecTableData(outputStream, pidMotion->motionLength, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

	appendStringTableData(outputStream, "stackMotionDefinition", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, pidMotion->stackMotionDefinitions, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

    appendStringTableData(outputStream, "detectedMotionType", PID_DEBUG_KEY_COLUMN_LENGTH);
	addDetectedMotionTypeTableData(outputStream, pidMotion->computationValues.detectedMotionType, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}

// MOTION_TYPE_NORMAL

/**
 * @private
 */
void printMotionInstructionStateHeader(OutputStream* outputStream, PidMotionDefinition* pidMotionDefinition) {
    int cursorLength = 35;
    appendDashes(outputStream, cursorLength);
    appendSpace(outputStream);
    cursorLength += appendString(outputStream, "state=");
    cursorLength += appendMotionDefinitionStateString(outputStream, pidMotionDefinition->state);
    appendSpace(outputStream);
    appendDashes(outputStream, PRINT_TABLE_WRITER_DEFAULT_PAGE_CHAR_WIDTH - cursorLength - 2);
    println(outputStream);
}

/**
* Private.
*/
void printMotionInstructionHeader(OutputStream* outputStream, PidMotionDefinition* pidMotionDefinition) {
	printMotionInstructionStateHeader(outputStream, pidMotionDefinition);

    // First Line Header
	appendStringHeader(outputStream, "Idx", PID_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "T/A", PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "a", PID_DEBUG_A_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Init s", PID_DEBUG_INITIAL_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "s", PID_DEBUG_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "sMax", PID_DEBUG_SPEED_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "End s", PID_DEBUG_END_SPEED_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t1", PID_DEBUG_T1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t2", PID_DEBUG_T2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "t3", PID_DEBUG_T3_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p1", PID_DEBUG_P1_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p2", PID_DEBUG_P2_COLUMN_LENGTH);
	appendStringHeader(outputStream, "p3", PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "profile", PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "motion Param", PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "pid", PID_DEBUG_PID_TYPE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);

    // Second Line Header
    appendStringHeader(outputStream, "", PID_DEBUG_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm/s^2", PID_DEBUG_A_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm/s", PID_DEBUG_INITIAL_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm/s", PID_DEBUG_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm/s", PID_DEBUG_SPEED_MAX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm/s", PID_DEBUG_END_SPEED_COLUMN_LENGTH);
    appendStringHeader(outputStream, "sec", PID_DEBUG_T1_COLUMN_LENGTH);
    appendStringHeader(outputStream, "sec", PID_DEBUG_T2_COLUMN_LENGTH);
    appendStringHeader(outputStream, "sec", PID_DEBUG_T3_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm", PID_DEBUG_P1_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm", PID_DEBUG_P2_COLUMN_LENGTH);
    appendStringHeader(outputStream, "mm", PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "type", PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "type", PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "type", PID_DEBUG_PID_TYPE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);


	appendTableHeaderSeparatorLine(outputStream);
}

void printMotionInstructionLine(OutputStream* outputStream, PidMotion* pidMotion, int index, enum InstructionType instructionType, MotionInstruction* motionInstruction) {
	appendDecTableData(outputStream, index, PID_DEBUG_INDEX_COLUMN_LENGTH);
	addInstructionTypeTableData(outputStream, instructionType, PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionInstruction->a, PID_DEBUG_A_COLUMN_LENGTH);
    appendDecfTableData(outputStream, motionInstruction->initialSpeed, PID_DEBUG_SPEED_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionInstruction->speed, PID_DEBUG_SPEED_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionInstruction->speedMax, PID_DEBUG_SPEED_MAX_COLUMN_LENGTH);
    appendDecfTableData(outputStream, motionInstruction->endSpeed, PID_DEBUG_END_SPEED_COLUMN_LENGTH);
    appendDecfTableData(outputStream, motionInstruction->t1, PID_DEBUG_T1_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionInstruction->t2, PID_DEBUG_T2_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionInstruction->t3, PID_DEBUG_T3_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionInstruction->p1, PID_DEBUG_P1_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionInstruction->p2, PID_DEBUG_P2_COLUMN_LENGTH);
	appendDecfTableData(outputStream, motionInstruction->nextPosition, PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH);
	addMotionProfileTypeTableData(outputStream, motionInstruction->profileType, PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH);
	addMotionParameterTypeTableData(outputStream, motionInstruction->motionParameterType, PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH);
	addPidTypeTableData(outputStream, motionInstruction->initialPidType, PID_DEBUG_PID_TYPE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);
}

// MOTION_TYPE_UNDEFINED

/**
* Private.
*/
void printUndefinedMotionHeader(OutputStream* outputStream, PidMotionDefinition* pidMotionDefinition) {
    printMotionInstructionStateHeader(outputStream, pidMotionDefinition);
	appendStringHeader(outputStream, "Idx", PID_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Undefined", PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printUndefinedMotionLine(OutputStream* outputStream, PidMotionDefinition* pidMotionDefinition, int index) {
	appendDecTableData(outputStream, index, PID_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringTableData(outputStream, "UNDEFINED", PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_LAST_COLUMN_LENGTH);
}


void printMotionInstructionTable(OutputStream* outputStream, PidMotion* pidMotion) {
	printMotionGlobalVarsData(outputStream, pidMotion);
	unsigned int i;
	// unsigned int count = getPidMotionElementsCount(pidMotion);
	unsigned int length = pidMotion->motionLength;
	PidMotionDefinition* pidMotionDefinition = (PidMotionDefinition*)pidMotion->motionDefinitions;
    pidMotionDefinition--;
	for (i = 0; i < length; i++) {
        pidMotionDefinition++;
		// PidMotionDefinition* pidMotionDefinition = getMotionDefinition(pidMotion, i);
		enum PidMotionType currentPidMotionType = pidMotionDefinition->motionType;
		println(outputStream);
		// Header Management
		switch (currentPidMotionType) {
			case MOTION_TYPE_NORMAL: {
				printMotionInstructionHeader(outputStream, pidMotionDefinition);
				MotionInstruction* theta = &(pidMotionDefinition->inst[THETA]);
				printMotionInstructionLine(outputStream, pidMotion, i, THETA, theta);
				MotionInstruction* alpha = &(pidMotionDefinition->inst[ALPHA]);
				printMotionInstructionLine(outputStream, pidMotion, i, ALPHA, alpha);
				appendTableHeaderSeparatorLine(outputStream);
				continue;
			}
			case MOTION_TYPE_BSPLINE: {
				appendTableHeaderSeparatorLine(outputStream);
				writeBSplineDefinitionTableHeader(outputStream);
				writeBSplineDefinitionRow(outputStream, i, &(pidMotionDefinition->curve));
				appendTableHeaderSeparatorLine(outputStream);
				continue;
			}
			case MOTION_TYPE_UNDEFINED:
				printUndefinedMotionHeader(outputStream, pidMotionDefinition);
				printUndefinedMotionLine(outputStream, pidMotionDefinition, i);
				appendTableHeaderSeparatorLine(outputStream);
				continue;
		}
	}
}
