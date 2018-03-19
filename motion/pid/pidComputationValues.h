#ifndef PID_COMPUTATION_VALUES_H
#define PID_COMPUTATION_VALUES_H

#include "pidComputationInstructionValues.h"
#include "detectedMotionType.h"
#include "instructionType.h"

#include "endDetection/motionEndInfo.h"

/**
 * All current values about the current motion in progress.
 */
typedef struct PidComputationValues {
    // The current motion Type
    enum DetectedMotionType detectedMotionType;
    // theta error for bSpline
    float bSplineThetaError;
    // angle error
    float bSplineAlphaError;
    // determine the distance between normal trajectory tangent line
    // and real trajectory tangent line
    float bSplineThetaXAxisError;
    // store the last pid time (in second)
    float lastPidTimeInSecond;
    // store the current pid time (in second))
    float pidTimeInSecond;
    /** Store all values indexed by INSTRUCTION_TYPE */
    PidComputationInstructionValues values[INSTRUCTION_TYPE_COUNT];

} PidComputationValues;

/**
 * Change the motion Type.
 * @param pidComputationValues
 * @param detectedMotionType
 */
void setDetectedMotionType(PidComputationValues* pidComputationValues, enum DetectedMotionType detectedMotionType);

/**
 * Clear all current values so that we will be sure not to keep some old values from the previous Pid.
 * @param pidComputationValues
 */
void clearPidComputationValues(PidComputationValues* pidComputationValues);

#endif
