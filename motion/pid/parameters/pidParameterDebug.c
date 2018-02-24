#include "pidParameterDebug.h"
#include "pidParameter.h"

#include "../pidMotion.h"
#include "../pid.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"

#define PID_PARAMETER_PID_INDEX_COLUMN_LENGTH             10
#define PID_PARAMETER_P_COLUMN_LENGTH                     10
#define PID_PARAMETER_I_COLUMN_LENGTH                     10
#define PID_PARAMETER_D_COLUMN_LENGTH                     10
#define PID_PARAMETER_MI_COLUMN_LENGTH                    10

#define PID_PARAMETER_LAST_COLUMN_LENGTH                  10

/**
* Private.
*/
void printPidParameterTableHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
	appendStringHeader(outputStream, "PID Index", PID_PARAMETER_PID_INDEX_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Propor.", PID_PARAMETER_P_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Integral", PID_PARAMETER_I_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Deriv.", PID_PARAMETER_D_COLUMN_LENGTH);
	appendStringHeader(outputStream, "Max Int.", PID_PARAMETER_MI_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_PARAMETER_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private
 */
void printPidParameterLine(OutputStream* outputStream, PidMotion* pidMotion, int pidIndex) {
    unsigned char rollingTestMode = getRollingTestMode(pidMotion);
    PidParameter* localPidParameter= getPidParameter(pidMotion, pidIndex, pidMotion->rollingTestMode);
	appendDecTableData(outputStream, pidIndex, PID_PARAMETER_PID_INDEX_COLUMN_LENGTH);

	appendDecfTableData(outputStream, localPidParameter->p, PID_PARAMETER_P_COLUMN_LENGTH);
	appendDecfTableData(outputStream, localPidParameter->i, PID_PARAMETER_I_COLUMN_LENGTH);
	appendDecfTableData(outputStream, localPidParameter->d, PID_PARAMETER_D_COLUMN_LENGTH);
	appendDecfTableData(outputStream, localPidParameter->maxIntegral, PID_PARAMETER_MI_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, PID_PARAMETER_LAST_COLUMN_LENGTH);
}

void printAllPidParametersTable(OutputStream* outputStream, PidMotion* pidMotion) {
	printPidParameterTableHeader(outputStream);
    int i;
    int pidCount = PID_COUNT;
    for (i = 0; i < pidCount; i++) {
        printPidParameterLine(outputStream, pidMotion, i);
    }
	appendTableHeaderSeparatorLine(outputStream);
}
