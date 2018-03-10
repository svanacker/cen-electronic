#include "pidParameterDebug.h"
#include "pidParameter.h"

#include "../instructionType.h"
#include "../pidType.h"
#include "../pidMotion.h"
#include "../pid.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"


#define PID_PARAMETER_PID_INDEX_COLUMN_LENGTH                 4
#define PID_PARAMETER_PID_TYPE_COLUMN_LENGTH                  11
#define PID_PARAMETER_INSTRUCTION_TYPE_COLUMN_LENGTH          11

#define PID_PARAMETER_P_DEC_COLUMN_LENGTH                     6
#define PID_PARAMETER_I_DEC_COLUMN_LENGTH                     6
#define PID_PARAMETER_D_DEC_COLUMN_LENGTH                     7
#define PID_PARAMETER_MI_DEC_COLUMN_LENGTH                    9

#define PID_PARAMETER_P_HEX_COLUMN_LENGTH                     6
#define PID_PARAMETER_I_HEX_COLUMN_LENGTH                     6
#define PID_PARAMETER_D_HEX_COLUMN_LENGTH                     7
#define PID_PARAMETER_MI_HEX_COLUMN_LENGTH                    9


#define PID_PARAMETER_LAST_COLUMN_LENGTH                      5

/**
* Private.
*/
void printPidParameterTableHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
    // First Header Line
	appendStringHeader(outputStream, "PID", PID_PARAMETER_PID_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "PID", PID_PARAMETER_PID_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Instruction", PID_PARAMETER_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Prop.", PID_PARAMETER_P_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Int.", PID_PARAMETER_I_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Deriv.", PID_PARAMETER_D_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Max Int.", PID_PARAMETER_MI_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Prop.", PID_PARAMETER_P_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Int.", PID_PARAMETER_I_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Deriv.", PID_PARAMETER_D_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Max Int.", PID_PARAMETER_MI_HEX_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_PARAMETER_LAST_COLUMN_LENGTH);
    
    // Second Header Line
	appendStringHeader(outputStream, "Idx", PID_PARAMETER_PID_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Type", PID_PARAMETER_PID_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Type", PID_PARAMETER_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec).", PID_PARAMETER_P_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", PID_PARAMETER_I_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", PID_PARAMETER_D_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Dec)", PID_PARAMETER_MI_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", PID_PARAMETER_P_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", PID_PARAMETER_I_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", PID_PARAMETER_D_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "(Hex)", PID_PARAMETER_MI_HEX_COLUMN_LENGTH);
    
	appendEndOfTableColumn(outputStream, PID_PARAMETER_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private
 */
void printPidParameterLine(OutputStream* outputStream, PidMotion* pidMotion, enum PidType pidType, enum InstructionType instructionType) {
	unsigned pidIndex = getIndexOfPid(instructionType, pidType);
    unsigned char rollingTestMode = getRollingTestMode(pidMotion);

    PidParameter* localPidParameter= getPidParameter(pidMotion, pidIndex, pidMotion->rollingTestMode);
	appendDecTableData(outputStream, pidIndex, PID_PARAMETER_PID_INDEX_COLUMN_LENGTH);
	addPidTypeTableData(outputStream, pidType, PID_PARAMETER_PID_TYPE_COLUMN_LENGTH);
	addInstructionTypeTableData(outputStream, instructionType, PID_PARAMETER_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, localPidParameter->p, PID_PARAMETER_P_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, localPidParameter->i, PID_PARAMETER_I_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, localPidParameter->d, PID_PARAMETER_D_DEC_COLUMN_LENGTH);
	appendDecfTableData(outputStream, localPidParameter->maxIntegral, PID_PARAMETER_MI_DEC_COLUMN_LENGTH);

	appendHexFloat4TableData(outputStream, localPidParameter->p, PID_VALUE_DIGIT_PRECISION, PID_PARAMETER_P_HEX_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, localPidParameter->i, PID_VALUE_DIGIT_PRECISION, PID_PARAMETER_I_HEX_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, localPidParameter->d, PID_VALUE_DIGIT_PRECISION, PID_PARAMETER_D_HEX_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, localPidParameter->maxIntegral, PID_VALUE_DIGIT_PRECISION, PID_PARAMETER_MI_HEX_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, PID_PARAMETER_LAST_COLUMN_LENGTH);
}

void printAllPidParametersTable(OutputStream* outputStream, PidMotion* pidMotion) {
	printPidParameterTableHeader(outputStream);
    enum PidType pidType;
    for (pidType = 0; pidType < PID_TYPE_COUNT; pidType++) {
        printPidParameterLine(outputStream, pidMotion, pidType, THETA);
        printPidParameterLine(outputStream, pidMotion, pidType, ALPHA);
    }
	appendTableHeaderSeparatorLine(outputStream);
}
