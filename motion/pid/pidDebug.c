#include "pidDebug.h"

#include "instructionType.h"
#include "motionInstruction.h"
#include "pid.h"
#include "pidMotion.h"
#include "pidMotionDefinitionState.h"
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
#define PID_DEBUG_A_COLUMN_LENGTH							3
#define PID_DEBUG_SPEED_COLUMN_LENGTH						5
#define PID_DEBUG_SPEED_MAX_COLUMN_LENGTH					5
#define PID_DEBUG_T1_COLUMN_LENGTH							4
#define PID_DEBUG_T2_COLUMN_LENGTH							4
#define PID_DEBUG_T3_COLUMN_LENGTH							4
#define PID_DEBUG_P1_COLUMN_LENGTH							6
#define PID_DEBUG_P2_COLUMN_LENGTH							6
#define PID_DEBUG_NEXT_POSITION_COLUMN_LENGTH				6
#define PID_DEBUG_PROFILE_TYPE_COLUMN_LENGTH				8
#define PID_DEBUG_MOTION_PARAMETER_TYPE_COLUMN_LENGTH		15
#define PID_DEBUG_PID_TYPE_COLUMN_LENGTH		            6
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
	appendDecTableData(outputStream, pidMotion->readIndex, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

	appendStringTableData(outputStream, "writeIndex", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendDecTableData(outputStream, pidMotion->writeIndex, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

	appendStringTableData(outputStream, "length", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendDecTableData(outputStream, pidMotion->length, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

	appendStringTableData(outputStream, "stackMotionDefinition", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, pidMotion->stackMotionDefinitions, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

	appendStringTableData(outputStream, "mustReachPosition", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, pidMotion->mustReachPosition, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);

	appendStringTableData(outputStream, "rollingTestMode", PID_DEBUG_KEY_COLUMN_LENGTH);
	appendBoolTableData(outputStream, pidMotion->rollingTestMode, PID_DEBUG_KEY_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_KEY_VALUE_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

// MOTION_TYPE_NORMAL

/**
 * @private
 */
void printMotionInstructionStateHeader(OutputStream* outputStream, PidMotionDefinition* pidMotionDefinition) {
    appendDashes(outputStream, 40);
    appendSpace(outputStream);
    int stateLength = appendMotionDefinitionStateString(outputStream, pidMotionDefinition->state);
    appendDashes(outputStream, PRINT_TABLE_WRITER_DEFAULT_PAGE_CHAR_WIDTH - 40 - stateLength - 2);
}

/**
* Private.
*/
void printMotionInstructionHeader(OutputStream* outputStream, PidMotionDefinition* pidMotionDefinition) {
	printMotionInstructionStateHeader(outputStream, pidMotionDefinition);
	appendStringHeader(outputStream, "Idx", PID_DEBUG_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "T/A", PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
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

void printMotionInstructionLine(OutputStream* outputStream, PidMotion* pidMotion, int index, enum InstructionType instructionType, MotionInstruction* motionInstruction) {
	appendDecTableData(outputStream, index, PID_DEBUG_INDEX_COLUMN_LENGTH);
	addInstructionTypeTableData(outputStream, instructionType, PID_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
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
	unsigned int length = pidMotion->length;
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

// PID DEBUG DATA

#define PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH                     10
#define PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH                             8
#define PID_DEBUG_DATA_PID_TYPE_TYPE_COLUMN_LENGTH                        8
#define PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH                      10
#define PID_DEBUG_DATA_POSITION_COLUMN_LENGTH                             8
#define PID_DEBUG_DATA_ERROR_COLUMN_LENGTH                                5
#define PID_DEBUG_DATA_U_COLUMN_LENGTH                                    4
#define PID_DEBUG_DATA_MOTION_END_INTEGRAL_TIME_COLUMN_LENGTH             17
#define PID_DEBUG_DATA_MOTION_END_ABS_DELTA_POSITION_INT_COLUMN_LENGTH    17
#define PID_DEBUG_DATA_MOTION_END_ABS_INTEGRAL_COLUMN_LENGTH              17
#define PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH		            0


/**
* Private.
*/
void printDebugDataHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "Inst Type", PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pid Time", PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Pid Type", PID_DEBUG_DATA_PID_TYPE_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Normal Pos", PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Position", PID_DEBUG_DATA_POSITION_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Error", PID_DEBUG_DATA_ERROR_COLUMN_LENGTH);
	appendStringHeader(outputStream, "U", PID_DEBUG_DATA_U_COLUMN_LENGTH);
	appendStringHeader(outputStream, "End Integral Time", PID_DEBUG_DATA_MOTION_END_INTEGRAL_TIME_COLUMN_LENGTH);
	appendStringHeader(outputStream, "End Abs Delta Pos", PID_DEBUG_DATA_MOTION_END_ABS_DELTA_POSITION_INT_COLUMN_LENGTH);
	appendStringHeader(outputStream, "End Abs Integral", PID_DEBUG_DATA_MOTION_END_ABS_INTEGRAL_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}


/**
 * Print a line of data for a specific Instruction Type
 */
void printDebugDataInstructionTypeLine(OutputStream* outputStream, PidMotion* pidMotion, enum InstructionType instructionType) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidMotionDefinition* motionDefinition = pidMotionGetCurrentMotionDefinition(pidMotion);
    MotionInstruction motionInstruction = motionDefinition->inst[instructionType];
    PidMotionError* localError = &(computationValues->errors[instructionType]);

    PidCurrentValues* pidCurrentValues = &(computationValues->currentValues[instructionType]);
	enum PidType pidType = getPidType(motionInstruction.motionParameterType);

	addInstructionTypeTableData(outputStream, instructionType, PID_DEBUG_DATA_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) computationValues->pidTime, PID_DEBUG_DATA_PID_TIME_COLUMN_LENGTH);
	addPidTypeTableData(outputStream, pidType, PID_DEBUG_DATA_PID_TYPE_TYPE_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) pidCurrentValues->normalPosition, PID_DEBUG_DATA_NORMAL_POSITION_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) pidCurrentValues->position, PID_DEBUG_DATA_POSITION_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) localError->error, PID_DEBUG_DATA_ERROR_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) pidCurrentValues->u, PID_DEBUG_DATA_U_COLUMN_LENGTH);

    MotionEndInfo* motionEnd = &(computationValues->motionEnd[instructionType]);
	appendDecTableData(outputStream, motionEnd->integralTime, PID_DEBUG_DATA_MOTION_END_INTEGRAL_TIME_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionEnd->absDeltaPositionIntegral, PID_DEBUG_DATA_MOTION_END_ABS_DELTA_POSITION_INT_COLUMN_LENGTH);
	appendDecTableData(outputStream, (int) motionEnd->absUIntegral, PID_DEBUG_DATA_MOTION_END_ABS_INTEGRAL_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_DEBUG_DATA_LAST_COLUMN_LENGTH_COLUMN_LENGTH);
}

void printPidDataDebugTable(OutputStream* outputStream, PidMotion* pidMotion) {
	printDebugDataHeader(outputStream);
	printDebugDataInstructionTypeLine(outputStream, pidMotion, THETA);
	printDebugDataInstructionTypeLine(outputStream, pidMotion, ALPHA);
	appendTableHeaderSeparatorLine(outputStream);
}
