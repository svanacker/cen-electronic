#include "motionEndDetectionDebug.h"


#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"
#include "motionEndInfo.h"
#include "motionEndDetectionParameter.h"
#include "../instructionType.h"

#define MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH        45
#define MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH  20
#define MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH  20
#define MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH       10

// PARAMETERS

/**
* Private.
*/
void printMotionEndDetectionParameterHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
    appendStringHeader(outputStream, "Key", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value (Hex)", MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value (Dec)", MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printMotionEndDetectionParameter(OutputStream* outputStream, MotionEndDetectionParameter* parameter) {
    printMotionEndDetectionParameterHeader(outputStream);

	appendStringTableData(outputStream, "Abs Delta Position Integral Factor Threshold", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
	appendHex6TableData(outputStream, (long) parameter->absDeltaPositionIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, parameter->absDeltaPositionIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);    

	appendStringTableData(outputStream, "Max U Integral Factor Threshold", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
	appendHex4TableData(outputStream, (long) parameter->maxUIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, parameter->maxUIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);    

    appendStringTableData(outputStream, "Max U Integral Constant Threshold", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
	appendHex4TableData(outputStream, (long) parameter->maxUIntegralConstantThreshold, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, parameter->maxUIntegralConstantThreshold, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);    

    appendStringTableData(outputStream, "Time Range Analysis", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
	appendHex4TableData(outputStream, parameter->timeRangeAnalysis, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecTableData(outputStream, parameter->timeRangeAnalysis, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);

    appendStringTableData(outputStream, "No Analysis At Startup Range Time", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
	appendHex4TableData(outputStream, parameter->noAnalysisAtStartupTime, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecTableData(outputStream, parameter->noAnalysisAtStartupTime, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH); 

    appendStringTableData(outputStream, "Max History Count", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
    appendHex2TableData(outputStream, MAX_HISTORY_COUNT, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
    appendDecTableData(outputStream, MAX_HISTORY_COUNT, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);

    appendTableHeaderSeparatorLine(outputStream);
}

// COMPUTATION VALUES

#define MOTION_END_DETECTION_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH                     11
#define MOTION_END_DETECTION_DEBUG_INTEGRAL_TIME_COLUMN_LENGTH                        9
#define MOTION_END_DETECTION_DEBUG_INDEX_COLUMN_LENGTH                                6
#define MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_INTEGRAL_COLUMN_LENGTH          18
#define MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_COLUMN_LENGTH                   18
#define MOTION_END_DETECTION_DEBUG_ABS_U_INTEGRAL_COLUMN_LENGTH                       10
#define MOTION_END_DETECTION_DEBUG_ABS_U_COLUMN_LENGTH                                10
#define MOTION_END_DETECTION_DEBUG_LAST_COLUMN_LENGTH                                 0

/**
* Private.
*/
void printMotionEndInfoDebugHeader(OutputStream* outputStream) {
	println(outputStream);
	appendTableHeaderSeparatorLine(outputStream);
    
    // First header Line
    appendStringHeader(outputStream, "Instruction", MOTION_END_DETECTION_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "integral", MOTION_END_DETECTION_DEBUG_INTEGRAL_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "index", MOTION_END_DETECTION_DEBUG_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "abs Delta", MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_INTEGRAL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "abs Delta", MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "abs U", MOTION_END_DETECTION_DEBUG_ABS_U_INTEGRAL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "abs U", MOTION_END_DETECTION_DEBUG_ABS_U_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_DEBUG_LAST_COLUMN_LENGTH);
    
    // Second header line
    appendStringHeader(outputStream, "Type", MOTION_END_DETECTION_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Time", MOTION_END_DETECTION_DEBUG_INTEGRAL_TIME_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", MOTION_END_DETECTION_DEBUG_INDEX_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Position Integral", MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_INTEGRAL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Position", MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Integral", MOTION_END_DETECTION_DEBUG_ABS_U_INTEGRAL_COLUMN_LENGTH);
    appendStringHeader(outputStream, "", MOTION_END_DETECTION_DEBUG_ABS_U_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_DEBUG_LAST_COLUMN_LENGTH);
    
	appendTableHeaderSeparatorLine(outputStream);
}

/**
 * @private
 */
void printMotionEndInfoLine(OutputStream* outputStream,
                            enum InstructionType instructionType,
                            MotionEndDetectionParameter* motionEndDetectionParameter,
                            MotionEndInfo* motionEndInfo) {
    addInstructionTypeTableData(outputStream, instructionType, MOTION_END_DETECTION_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
    appendDecTableData(outputStream, motionEndInfo->integralTime, MOTION_END_DETECTION_DEBUG_INTEGRAL_TIME_COLUMN_LENGTH);
    appendDecTableData(outputStream, motionEndInfo->index, MOTION_END_DETECTION_DEBUG_INDEX_COLUMN_LENGTH);
    
    // Delta Position
    appendDecfTableData(outputStream, motionEndInfo->absDeltaPositionIntegral, MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_INTEGRAL_COLUMN_LENGTH);
    appendStringTableData(outputStream, "", MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_COLUMN_LENGTH);
    
    // Delta U
    appendDecfTableData(outputStream, motionEndInfo->absUIntegral, MOTION_END_DETECTION_DEBUG_ABS_U_INTEGRAL_COLUMN_LENGTH);
    appendStringTableData(outputStream, "", MOTION_END_DETECTION_DEBUG_ABS_U_INTEGRAL_COLUMN_LENGTH);

    appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_DEBUG_LAST_COLUMN_LENGTH);

    // Detail of History
    int i;
    for (i = 0; i < MAX_HISTORY_COUNT; i++) {
        appendStringTableData(outputStream, "", MOTION_END_DETECTION_DEBUG_INSTRUCTION_TYPE_COLUMN_LENGTH);
        appendStringTableData(outputStream, "", MOTION_END_DETECTION_DEBUG_INTEGRAL_TIME_COLUMN_LENGTH);
        appendDecTableData(outputStream, i, MOTION_END_DETECTION_DEBUG_INDEX_COLUMN_LENGTH);

        // Delta Position
        appendStringTableData(outputStream, "", MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_INTEGRAL_COLUMN_LENGTH);
        appendDecfTableData(outputStream, motionEndInfo->absDeltaPositionIntegralHistory[i], MOTION_END_DETECTION_DEBUG_ABS_DELTA_POSITION_COLUMN_LENGTH);

        // Delta U
        appendStringTableData(outputStream, "", MOTION_END_DETECTION_DEBUG_ABS_U_INTEGRAL_COLUMN_LENGTH);
        appendDecfTableData(outputStream, motionEndInfo->absUIntegralHistory[i], MOTION_END_DETECTION_DEBUG_ABS_U_COLUMN_LENGTH);


        appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_DEBUG_LAST_COLUMN_LENGTH);
    }
    appendTableHeaderSeparatorLine(outputStream);
}

void printMotionEndInfos(OutputStream* outputStream, PidMotion* pidMotion) {
    printMotionEndInfoDebugHeader(outputStream);
    MotionEndDetectionParameter* motionEndDetectionParameter = &(pidMotion->globalParameters.motionEndDetectionParameter);
    printMotionEndInfoLine(outputStream, THETA, motionEndDetectionParameter, &(pidMotion->computationValues.motionEnd[THETA]));
    printMotionEndInfoLine(outputStream, ALPHA, motionEndDetectionParameter, &(pidMotion->computationValues.motionEnd[ALPHA]));
}
