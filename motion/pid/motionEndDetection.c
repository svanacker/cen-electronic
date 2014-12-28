#include <math.h>
#include <stdlib.h>
#include "motionEndDetection.h"

#include "pid.h"

#include "../../common/commons.h"
#include "../../common/math/cenMath.h"

#include "../../common/io/buffer.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

void resetMotionEndData(MotionEndInfo* endMotion) {
    endMotion->integralTime = 0;
    endMotion->index = 0;
    int i;
    for (i = 0; i < MAX_HISTORY_COUNT; i++) {
        endMotion->absDeltaPositionIntegralHistory[i] = 0;
        endMotion->absUIntegralHistory[i] = 0;
    }
    endMotion->absDeltaPositionIntegral = 0;
    endMotion->absUIntegral = 0;
}

void initMotionEndParameter(MotionEndDetectionParameter* parameter) {
    parameter->absDeltaPositionIntegralFactorThreshold = (unsigned char) ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD;
	parameter->maxUIntegralFactorThreshold = (unsigned char) MAX_U_INTEGRAL_FACTOR_THRESHOLD;
	parameter->maxUIntegralConstantThreshold = (unsigned char) MAX_U_INTEGRAL_CONSTANT_THRESHOLD;
    parameter->timeRangeAnalysis = BLOCKING_OR_REACH_DETECTION_DELAY;
    parameter->noAnalysisAtStartupTime = BLOCKING_OR_REACH_SKIP_DETECTION_DELAY;
}

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

void updateEndMotionData(int instructionIndex, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter, int time) {
    PidMotion* pidMotion = getPidMotion();
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    Motion* motion = &(computationValues->motion[instructionIndex]);

    // Do not analyze it during startup time
    if (time < parameter->noAnalysisAtStartupTime) {
        motion->oldPosition = motion->position;
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
    float absU = fabsf(motion->u);
    float absDeltaPosition = fabsf(motion->position - motion->oldPosition);

    // In every case
    endMotion->absUIntegralHistory[endMotion->index] += absU;
    endMotion->absDeltaPositionIntegralHistory[endMotion->index] += absDeltaPosition;

    // To compute for next iteration
    motion->oldPosition = motion->position;

    // Update aggregate Values
    updateAggregateValues(endMotion);
}


bool isEndOfMotion(int instructionIndex, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter) {
    if (endMotion->integralTime < parameter->timeRangeAnalysis) {
        return false;
    }
    if (endMotion->absDeltaPositionIntegral < (parameter->absDeltaPositionIntegralFactorThreshold * parameter->timeRangeAnalysis * MAX_HISTORY_COUNT)) {
        return true;
    }
    return false;
}

bool isRobotBlocked(int instructionIndex, MotionEndInfo* endMotion, MotionEndDetectionParameter* parameter) {
    if (endMotion->integralTime < parameter->timeRangeAnalysis) {
        return false;
    }
    PidMotionDefinition* motionDefinition = &(getPidMotion()->currentMotionDefinition);
    MotionInstruction* localInst = &(motionDefinition->inst[instructionIndex]);
    float normalU = getNormalU(localInst->speed);
    float value = parameter->maxUIntegralConstantThreshold + normalU * parameter->maxUIntegralFactorThreshold;
    float limitValue = (float) limit((long) value, (long) PID_NEXT_VALUE_LIMIT);
    float maxUIntegral = fabsf(limitValue * parameter->timeRangeAnalysis);
    if (endMotion->absUIntegral > maxUIntegral) {
        return true;
    }
    return false;
}
