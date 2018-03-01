#include "pidComputationValues.h"

#include "detectedMotionType.h"
#include "pidMotionError.h"
#include "endDetection/motionEndDetection.h"

void clearPidComputationValues(PidComputationValues* pidComputationValues) {
    pidComputationValues->detectedMotionType = DETECTED_MOTION_TYPE_NO_POSITION_TO_REACH;
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