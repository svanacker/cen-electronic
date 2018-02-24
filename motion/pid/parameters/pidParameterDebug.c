#include "pidParameterDebug.h"
#include "pidParameter.h"

#include "../instructionType.h"
#include "../pidType.h"
#include "../pidMotion.h"
#include "../pid.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"


#define PID_PARAMETER_PID_INDEX_COLUMN_LENGTH                 8
#define PID_PARAMETER_PID_TYPE_COLUMN_LENGTH                  10
#define PID_PARAMETER_INSTRUCTION_TYPE_COLUMN_LENGTH          10

#define PID_PARAMETER_P_DEC_COLUMN_LENGTH                     13
#define PID_PARAMETER_I_DEC_COLUMN_LENGTH                     12
#define PID_PARAMETER_D_DEC_COLUMN_LENGTH                     13
#define PID_PARAMETER_MI_DEC_COLUMN_LENGTH                    14

#define PID_PARAMETER_P_HEX_COLUMN_LENGTH                     13
#define PID_PARAMETER_I_HEX_COLUMN_LENGTH                     12
#define PID_PARAMETER_D_HEX_COLUMN_LENGTH                     13
#define PID_PARAMETER_MI_HEX_COLUMN_LENGTH                    14


#define PID_PARAMETER_LAST_COLUMN_LENGTH                  10

/**
* Private.
*/
void printPidParameterTableHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "PID Idx", PID_PARAMETER_PID_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "PID Type", PID_PARAMETER_PID_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Inst Type", PID_PARAMETER_INSTRUCTION_TYPE_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Prop. (Dec).", PID_PARAMETER_P_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Int. (Dec)", PID_PARAMETER_I_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Deriv. (Dec)", PID_PARAMETER_D_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Max Int. (Dec)", PID_PARAMETER_MI_DEC_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Prop. (Hex).", PID_PARAMETER_P_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Int. (Hex)", PID_PARAMETER_I_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Deriv. (Hex)", PID_PARAMETER_D_HEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Max Int. (Hex)", PID_PARAMETER_MI_HEX_COLUMN_LENGTH);
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

	appendHex2TableData(outputStream, localPidParameter->p, PID_PARAMETER_P_HEX_COLUMN_LENGTH);
	appendHex2TableData(outputStream, localPidParameter->i, PID_PARAMETER_I_HEX_COLUMN_LENGTH);
	appendHex2TableData(outputStream, localPidParameter->d, PID_PARAMETER_D_HEX_COLUMN_LENGTH);
	appendHex2TableData(outputStream, localPidParameter->maxIntegral, PID_PARAMETER_MI_HEX_COLUMN_LENGTH);

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
