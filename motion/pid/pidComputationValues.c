#include "pidComputationValues.h"

#include "detectedMotionType.h"
#include "pidMotionError.h"
#include "endDetection/motionEndDetection.h"

#include "../../common/io/outputStream.h"
#include "../../common/log/logger.h"

void clearPidComputationValues(PidComputationValues* pidComputationValues) {
    setDetectedMotionType(pidComputationValues, DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH);
    pidComputationValues->alphaError = 0.0f;
    pidComputationValues->thetaError = 0.0f;
    pidComputationValues->thetaXAxisError = 0.0f;
    pidComputationValues->pidTime = 0.0f;
    
    resetMotionEndInfo(&(pidComputationValues->motionEnd[THETA]));
    resetMotionEndInfo(&(pidComputationValues->motionEnd[ALPHA]));
    
    clearPidCurrentValues(&(pidComputationValues->currentValues[THETA]));
    clearPidCurrentValues(&(pidComputationValues->currentValues[ALPHA]));
     
    clearMotionError(&(pidComputationValues->errors[THETA]));
    clearMotionError(&(pidComputationValues->errors[ALPHA]));
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