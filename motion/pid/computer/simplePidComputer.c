#include "simplePidComputer.h"
#include "pidComputer.h"

#include "../pidComputationValues.h"
#include "../pid.h"
#include "../instructionType.h"
#include "../parameters/pidParameter.h"
#include "../pidMotion.h"
#include "../pidComputationInstructionValues.h"

#include "../../simulation/motionSimulation.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"
#include "../../../common/io/printWriter.h"

#include "../../../common/math/cenMath.h"


/**
 * @private
 * Computes the next value of the pid.
 * @param instructionType the pid that we want to compute (alpha/theta)
 * @param pidType the type of pid that we want to compute (between 0 and PID_TYPE_COUNT)
 * @param currentPosition the current position of the wheels (either alphaPosition, either thetaPosition)
 * @param time the time in pid sampling
 */
float computeNextPID(PidMotion* pidMotion, enum InstructionType instructionType, MotionInstruction* motionInstruction, PidComputationInstructionValues* values, float time) {
    unsigned char rollingTestMode = getRollingTestMode(pidMotion);
    enum PidType pidType = motionInstruction->pidType;
    float currentPosition = values->currentPosition;

    // instructionIndex = Alpha / Theta
    // pidType = Forward / Rotation / Final Approach ...
    unsigned char pidIndex = getIndexOfPid(instructionType, pidType);
    PidParameter* pidParameter = getPidParameter(pidMotion, pidIndex, rollingTestMode);

    if (!pidParameter->enabled) {
        return 0.0f;
    }

    float normalPosition = computeNormalPosition(motionInstruction, time);
    values->normalPosition = normalPosition;
    float positionError = normalPosition - currentPosition;
    
    float normalSpeed = computeNormalSpeed(motionInstruction, time);
    values->normalSpeed = normalSpeed;
    
    float result = computePidCorrection(values, pidParameter, normalSpeed, positionError);

    return result;
}

void simpleMotionUComputeInstruction(PidMotion* pidMotion, PidMotionDefinition* motionDefinition, enum InstructionType instructionType) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    MotionInstruction* motionInstruction = &(motionDefinition->inst[instructionType]);
    PidComputationInstructionValues* computationInstructionValues = &(computationValues->values[instructionType]);

    float pidTime = computationValues->pidTime;
    computationInstructionValues->u = computeNextPID(pidMotion, instructionType, motionInstruction, computationInstructionValues, pidTime);
}

/**
 * Compute the PID when the instruction is very simple (not b spline).
 */
void simpleMotionUCompute(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    simpleMotionUComputeInstruction(pidMotion, motionDefinition, THETA);
    simpleMotionUComputeInstruction(pidMotion, motionDefinition, ALPHA);
}