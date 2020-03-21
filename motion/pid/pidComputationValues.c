#include "pidComputationValues.h"
#include "pidComputationInstructionValues.h"

#include "detectedMotionType.h"

#include "../../common/io/outputStream.h"
#include "../../common/log/logger.h"

void clearPidComputationValues(PidComputationValues* pidComputationValues) {
    setDetectedMotionType(pidComputationValues, DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH);
    pidComputationValues->bSplineAlphaError = 0.0f;
    pidComputationValues->bSplineThetaError = 0.0f;
    pidComputationValues->bSplineThetaXAxisError = 0.0f;
    pidComputationValues->lastPidTimeInSecond = 0.0f;
    pidComputationValues->pidTimeInSecond = 0.0f;

    clearPidComputationInstructionValues(&(pidComputationValues->values[THETA]));
    clearPidComputationInstructionValues(&(pidComputationValues->values[ALPHA]));
}

void setDetectedMotionType(PidComputationValues* pidComputationValues, enum DetectedMotionType detectedMotionType) {
    if (detectedMotionType != pidComputationValues->detectedMotionType) {

        OutputStream* outputStream = getDebugOutputStreamLogger();
        appendDetectedMotionTypeAsString(outputStream, pidComputationValues->detectedMotionType);
        appendString(outputStream, "->");
        appendDetectedMotionTypeAsString(outputStream, detectedMotionType);

        pidComputationValues->detectedMotionType = detectedMotionType;
        println(outputStream);
    }
}