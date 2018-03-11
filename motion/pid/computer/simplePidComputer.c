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
float computeNextPID(PidMotion* pidMotion,
                    PidMotionDefinition* motionDefinition,
                     enum InstructionType instructionType) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    MotionInstruction* motionInstruction = &(motionDefinition->inst[instructionType]);
    PidComputationInstructionValues* computationInstructionValues = &(computationValues->values[instructionType]);

    enum PidType pidType = motionInstruction->initialPidType;
    computationInstructionValues->pidType = pidType;

    // pidType = Forward / Rotation / Final Approach ...
    PidParameter* pidParameter = getPidParameterByPidType(pidMotion, pidType);

    if (!pidParameter->enabled) {
        return 0.0f;
    }

    float pidTimeInSecond = computationValues->pidTime;

    // Position
    float currentPosition = computationInstructionValues->currentPosition;
    float normalPosition = computeNormalPosition(motionInstruction, pidTimeInSecond);
    computationInstructionValues->normalPosition = normalPosition;

    // Error
    float positionError = normalPosition - currentPosition;
    
    // Speed
    float normalSpeed = computeNormalSpeed(motionInstruction, pidTimeInSecond);
    computationInstructionValues->normalSpeed = normalSpeed;
    
    // Do the compute on P, I, D and return u
    float result = computePidCorrection(computationInstructionValues, pidParameter, normalSpeed, positionError);
    computationInstructionValues->u = result;

    // For History
    storePidComputationInstructionValueHistory(computationInstructionValues, pidTimeInSecond);

    return result;
}

/**
 * Compute the PID when the instruction is very simple (not b spline).
 */
void simpleMotionUCompute(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    computeNextPID(pidMotion, motionDefinition, THETA);
    computeNextPID(pidMotion, motionDefinition, ALPHA);
}