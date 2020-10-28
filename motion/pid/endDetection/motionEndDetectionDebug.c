#include "motionEndDetectionDebug.h"


#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"
#include "parameters/motionEndDetectionParameter.h"
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

void printMotionEndDetectionParameterLine(OutputStream* outputStream, char* keyName, float value) {
    appendStringTableData(outputStream, keyName, MOTION_END_DETECTION_PARAMETERS_KEY_COLUMN_LENGTH);
    appendHexFloat4TableData(outputStream, value, MOTION_END_DETECTION_PARAMETER_DIGIT, MOTION_END_DETECTION_PARAMETERS_DEC_VALUE_COLUMN_LENGTH);
    appendDecfTableData(outputStream, value, MOTION_END_DETECTION_PARAMETERS_HEX_VALUE_COLUMN_LENGTH);
    appendEndOfTableColumn(outputStream, MOTION_END_DETECTION_PARAMETERS_LAST_COLUMN_LENGTH);
}

void printMotionEndDetectionParameter(OutputStream* outputStream, MotionEndDetectionParameter* parameter) {
    printMotionEndDetectionParameterHeader(outputStream);

    // DETAIL PHASE
    printMotionEndDetectionParameterLine(outputStream, "Acceleration Too High Threshold Factor", parameter->accelerationTooHighTresholdFactor);
    printMotionEndDetectionParameterLine(outputStream, "Speed Too low Threshold Factor", parameter->speedTooLowThresholdFactor);
    printMotionEndDetectionParameterLine(outputStream, "U Too High Threshold Factor", parameter->uTooHighTresholdFactor);
    printMotionEndDetectionParameterLine(outputStream, "Speed min Threshold Factor", parameter->speedMinThreshold);
    printMotionEndDetectionParameterLine(outputStream, "U Min Threshold Value", parameter->uMinThresholdValue);
    appendTableHeaderSeparatorLine(outputStream);

    // AGGREGATION PHASE
    printMotionEndDetectionParameterLine(outputStream, "Abs Delta Position Integral Factor Threshold", parameter->absDeltaPositionIntegralFactorThreshold);
    printMotionEndDetectionParameterLine(outputStream, "Max U Integral Factor Threshold", parameter->maxUIntegralFactorThreshold);
    printMotionEndDetectionParameterLine(outputStream, "Max U Integral Constant Threshold", parameter->maxUIntegralConstantThreshold);
    printMotionEndDetectionParameterLine(outputStream, "Time Range Analysis", parameter->timeRangeAnalysisInSecond);
    printMotionEndDetectionParameterLine(outputStream, "No Analysis At Startup Range Time", parameter->noAnalysisAtStartupTimeInSecond);
    appendTableHeaderSeparatorLine(outputStream);

    // FAILED
    printMotionEndDetectionParameterLine(outputStream, "Failed Timeout After T3 In Sec", parameter->failedTimeoutAfterT3InSecond);
    appendTableHeaderSeparatorLine(outputStream);
    // REACHED
    printMotionEndDetectionParameterLine(outputStream, "Reached Window Count", parameter->reachedWindowCount);
    printMotionEndDetectionParameterLine(outputStream, "Reached Derivative Error Threshold", parameter->reachedDerivativeErrorThreshold);
    appendTableHeaderSeparatorLine(outputStream);
    // SHOCKED
    printMotionEndDetectionParameterLine(outputStream, "Shocked Acc Max For One Value Threshold", parameter->shockedAccelerationMaxForOneValueThreshold);
    printMotionEndDetectionParameterLine(outputStream, "Shocked Acc Window Analysis Count", parameter->shockedAccelerationWindowAnalysisCount);
    printMotionEndDetectionParameterLine(outputStream, "Shocked Acc Window Match Count", parameter->shockedAccelerationWindowsMatchCount);
    appendTableHeaderSeparatorLine(outputStream);
    // BLOCKED
    printMotionEndDetectionParameterLine(outputStream, "Blocked Window Analysis Count", parameter->blockedWindowsAnalysisCount);
    printMotionEndDetectionParameterLine(outputStream, "Blocked Percentage Threshold", parameter->blockedPercentageThreshold);
    appendTableHeaderSeparatorLine(outputStream);
}

unsigned int appendMotionEndDetectionStatusRegister(OutputStream* outputStream, MotionEndDetectionStatusRegister motionEndDetectionStatusRegister) {
    if (motionEndDetectionStatusRegister.absAccelerationTooHighThanExpected) {
        append(outputStream, 'A');
    } else {
        appendSeparator(outputStream);
    }
    if (motionEndDetectionStatusRegister.absSpeedTooLowThanExpected) {
        append(outputStream, 'S');
    } else {
        appendSeparator(outputStream);
    }
    if (motionEndDetectionStatusRegister.absUTooHighThanExpected) {
        append(outputStream, 'U');
    } else {
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
