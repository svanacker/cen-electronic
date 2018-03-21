#include "motionEndDetectionDebug.h"


#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"
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
    appendStringHeader(outputStream, "Value (Hex) x1000", MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
    appendStringHeader(outputStream, "Value (Dec)", MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);

	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);
	appendTableHeaderSeparatorLine(outputStream);
}

void printMotionEndDetectionParameter(OutputStream* outputStream, MotionEndDetectionParameter* parameter) {
    printMotionEndDetectionParameterHeader(outputStream);

	appendStringTableData(outputStream, "Abs Delta Position Integral Factor Threshold", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
	appendHexFloat4TableData(outputStream, parameter->absDeltaPositionIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, parameter->absDeltaPositionIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);    

	appendStringTableData(outputStream, "Max U Integral Factor Threshold", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, parameter->maxUIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, parameter->maxUIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);    

    appendStringTableData(outputStream, "Max U Integral Constant Threshold", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, parameter->maxUIntegralConstantThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, parameter->maxUIntegralConstantThreshold, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);    

    appendStringTableData(outputStream, "Time Range Analysis", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
	appendHexFloat4TableData(outputStream, parameter->timeRangeAnalysisInSecond, MOTION_END_DETECTION_PARAMETER_DIGIT, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, parameter->timeRangeAnalysisInSecond, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);

    appendStringTableData(outputStream, "No Analysis At Startup Range Time", MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, parameter->noAnalysisAtStartupTimeInSecond, MOTION_END_DETECTION_PARAMETER_DIGIT, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
	appendDecfTableData(outputStream, parameter->noAnalysisAtStartupTimeInSecond, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
	appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH); 

    appendTableHeaderSeparatorLine(outputStream);
}

unsigned int appendMotionEndDetectionStatusRegister(OutputStream* outputStream, MotionEndDetectionStatusRegister motionEndDetectionStatusRegister) {
    if (motionEndDetectionStatusRegister.absAccelerationTooHighThanExpected) {
        append(outputStream, 'A');
    }
    else {
        appendSeparator(outputStream);
    }
    if (motionEndDetectionStatusRegister.absSpeedTooLowThanExpected) {
        append(outputStream, 'S');
    }
    else {
        appendSeparator(outputStream);
    }
    if (motionEndDetectionStatusRegister.absUTooHighThanExpected) {
        append(outputStream, 'U');
    }
    else {
        appendSeparator(outputStream);
    }
    // Length of written chars
    return 3;
}

// For Table Data

unsigned int appendMotionEndDetectionStatusRegisterTableData(OutputStream* outputStream, 
                                                             MotionEndDetectionStatusRegister motionEndDetectionStatusRegister,
                                                             unsigned int columnSize) {
    appendTableSeparator(outputStream);
    appendSpace(outputStream);
    unsigned int length = appendMotionEndDetectionStatusRegister(outputStream, motionEndDetectionStatusRegister);
    return length + appendSpaces(outputStream, columnSize - length) + 2;
}
