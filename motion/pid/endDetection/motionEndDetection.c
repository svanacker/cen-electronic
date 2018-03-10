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
#include "../computer/pidComputer.h"
#include "../pidConstants.h"
#include "../pid.h"


/**
 * Aggregates the value by doing the integral of the speed, and the integral of the U
 * private function
 */
void updateAggregateValues(MotionEndInfo* endMotion) {
    /*
    endMotion->absSpeedIntegral = 0;
    endMotion->absUIntegral = 0;
    int index = endMotion->writeIndex;
    int i;
    for (i = index + 1; i < index + MAX_HISTORY_COUNT; i++) {
        endMotion->absSpeedIntegral += endMotion->absSpeedIntegralHistory[i % MAX_HISTORY_COUNT];
        endMotion->absUIntegral += endMotion->absUIntegralHistory[i % MAX_HISTORY_COUNT];
    }
    */
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
    /*
    PidCurrentValues* pidCurrentValues = &(computationValues->values[instructionType].currentValues);

    // Do not analyze it during startup time
    if (time < parameter->noAnalysisAtStartupTime) {
        // Store it for next pid loop and return
        pidCurrentValues->oldPosition = pidCurrentValues->currentPosition;
        return;
    }
    // We launch analysis only each timeRangeAnalysis (reason why there is modulo)
    if ((time % parameter->timeRangeAnalysis) == 0) {
        endMotion->integralTime++;
        // the current array value is full
        if ((endMotion->integralTime % MAX_HISTORY_COUNT) == 0) {
            // get the next Index
            endMotion->writeIndex = (endMotion->writeIndex + 1) % MAX_HISTORY_COUNT;
        }
        float absU = fabsf(pidCurrentValues->u);
        float absDeltaPosition = fabsf(pidCurrentValues->currentPosition - pidCurrentValues->oldPosition);

        endMotion->absUIntegralHistory[endMotion->writeIndex] = absU;
        endMotion->absSpeedIntegralHistory[endMotion->writeIndex] = absDeltaPosition;

        // To compute for next iteration
        pidCurrentValues->oldPosition = pidCurrentValues->currentPosition;

        // Update aggregate Values
        updateAggregateValues(endMotion);
    }
    */
}

/**
 * Detect if we are at the end of the motion. End of motion means that 
 * the integral of 
 * @private
 * @param instructionType
 * @param endMotion
 * @param parameter
 * @return 
 */
bool isEndOfMotion(enum InstructionType instructionType, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter) {
    
    if (endMotion->integralTime < parameter->timeRangeAnalysisInSecond) {
        return false;
    }
    if (endMotion->absSpeedIntegral < (parameter->absDeltaPositionIntegralFactorThreshold * parameter->timeRangeAnalysisInSecond * MAX_HISTORY_COUNT)) {
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
    if (endMotion->integralTime < parameter->timeRangeAnalysisInSecond) {
        return false;
    }
    MotionInstruction* localInst = &(motionDefinition->inst[instructionType]);
    float normalU = getNormalU(localInst->speed);
    float value = parameter->maxUIntegralConstantThreshold + normalU * parameter->maxUIntegralFactorThreshold;
    float maxUIntegral = fabsf(value * parameter->timeRangeAnalysisInSecond);
    if (endMotion->absUIntegral > maxUIntegral) {
        return true;
    }
    return false;
}

void detectIfRobotIsBlocked(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    /*
    MotionEndDetectionParameter* endDetectionParameter = getMotionEndDetectionParameter(pidMotion);
        
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);
        
    MotionEndInfo* thetaEndMotion = &(computationValues->values[THETA].motionEnd);
    MotionEndInfo* alphaEndMotion = &(computationValues->values[ALPHA].motionEnd);

    thetaCurrentValues->currentSpeed = thetaCurrentValues->currentPosition - thetaCurrentValues->oldPosition;
    alphaCurrentValues->currentSpeed = alphaCurrentValues->currentPosition - alphaCurrentValues->oldPosition;

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
    */
}