#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "motionEndDetection.h"

#include "../../../common/commons.h"
#include "../../../common/math/cenMath.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../detectedMotionType.h"
#include "../pidComputationValues.h"
#include "../pidConstants.h"
#include "../pid.h"


/**
 * private function
 */
void updateAggregateValues(MotionEndInfo* endMotion) {
    endMotion->absDeltaPositionIntegral = 0;
    endMotion->absUIntegral = 0;
    int index = endMotion->index;
    int i;
    for (i = index + 1; i < index + MAX_HISTORY_COUNT; i++) {
        endMotion->absDeltaPositionIntegral += endMotion->absDeltaPositionIntegralHistory[i % MAX_HISTORY_COUNT];
        endMotion->absUIntegral += endMotion->absUIntegralHistory[i % MAX_HISTORY_COUNT];
    }
}

/**
 * @private
 * @param computationValues
 * @param instructionType
 * @param endMotion
 * @param parameter
 * @param time
 */
void updateEndMotionData(PidComputationValues* computationValues, 
	                     enum InstructionType instructionType,
	                     MotionEndInfo* endMotion,
	                     MotionEndDetectionParameter* parameter,
	                     unsigned int time) {
    PidCurrentValues* pidCurrentValues = &(computationValues->currentValues[instructionType]);

    // Do not analyze it during startup time
    if (time < parameter->noAnalysisAtStartupTime) {
        pidCurrentValues->oldPosition = pidCurrentValues->position;
        return;
    }
    if ((time % parameter->timeRangeAnalysis) == 0) {
        endMotion->integralTime++;
        // the current array value is full
        if ((endMotion->integralTime % MAX_HISTORY_COUNT) == 0) {
            // get the next Index
            endMotion->index = (endMotion->index + 1) % MAX_HISTORY_COUNT;
            // clean it before using it
            endMotion->absUIntegralHistory[endMotion->index] = 0;
            endMotion->absDeltaPositionIntegralHistory[endMotion->index] = 0;
        }
    }
    float absU = fabsf(pidCurrentValues->u);
    float absDeltaPosition = fabsf(pidCurrentValues->position - pidCurrentValues->oldPosition);

    // In every case
    endMotion->absUIntegralHistory[endMotion->index] += absU;
    endMotion->absDeltaPositionIntegralHistory[endMotion->index] += absDeltaPosition;

    // To compute for next iteration
    pidCurrentValues->oldPosition = pidCurrentValues->position;

    // Update aggregate Values
    updateAggregateValues(endMotion);
}

/**
 * @private
 * @param instructionType
 * @param endMotion
 * @param parameter
 * @return 
 */
bool isEndOfMotion(enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter) {
    if (endMotion->integralTime < parameter->timeRangeAnalysis) {
        return false;
    }
    if (endMotion->absDeltaPositionIntegral < (parameter->absDeltaPositionIntegralFactorThreshold * parameter->timeRangeAnalysis * MAX_HISTORY_COUNT)) {
        return true;
    }
    return false;
}

/**
 * @private
 * @param motionDefinition
 * @param instructionType
 * @param endMotion
 * @param parameter
 * @return 
 */
bool isMotionInstructionIsBlocked(PidMotionDefinition* motionDefinition, enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter) {
    if (endMotion->integralTime < parameter->timeRangeAnalysis) {
        return false;
    }
    MotionInstruction* localInst = &(motionDefinition->inst[instructionType]);
    float normalU = getNormalU(localInst->speed);
    float value = parameter->maxUIntegralConstantThreshold + normalU * parameter->maxUIntegralFactorThreshold;
    float limitValue = limitFloat(value, PID_NEXT_VALUE_LIMIT);
    float maxUIntegral = fabsf(limitValue * parameter->timeRangeAnalysis);
    if (endMotion->absUIntegral > maxUIntegral) {
        return true;
    }
    return false;
}

void detectIfRobotIsBlocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    MotionEndDetectionParameter* endDetectionParameter = getMotionEndDetectionParameter(pidMotion);
        
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
    PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);
    
        
    MotionEndInfo* thetaEndMotion = &(computationValues->motionEnd[THETA]);
    MotionEndInfo* alphaEndMotion = &(computationValues->motionEnd[ALPHA]);

    thetaCurrentValues->currentSpeed = thetaCurrentValues->position - thetaCurrentValues->oldPosition;
    alphaCurrentValues->currentSpeed = alphaCurrentValues->position - alphaCurrentValues->oldPosition;

    updateEndMotionData(computationValues, THETA, thetaEndMotion, endDetectionParameter, (int) computationValues->pidTime);
    updateEndMotionData(computationValues, ALPHA, alphaEndMotion, endDetectionParameter, (int) computationValues->pidTime);

    bool isThetaEnd = isEndOfMotion(THETA, thetaEndMotion, endDetectionParameter);
    bool isAlphaEnd = isEndOfMotion(ALPHA, alphaEndMotion, endDetectionParameter);

    bool isThetaBlocked = isMotionInstructionIsBlocked(motionDefinition, THETA, thetaEndMotion, endDetectionParameter);
    bool isAlphaBlocked = isMotionInstructionIsBlocked(motionDefinition, ALPHA, alphaEndMotion, endDetectionParameter);

    if (isThetaEnd && isAlphaEnd) {
        if (isThetaBlocked || isAlphaBlocked) {
            setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_BLOCKED_WHEELS);
            return;
        } else {
            setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_REACHED);
            return;
        }
    }
    // If not blocked or not reached -> In Progress
    setDetectedMotionType(computationValues, DETECTED_MOTION_TYPE_POSITION_IN_PROGRESS);
}