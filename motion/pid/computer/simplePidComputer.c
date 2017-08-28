#include "simplePidComputer.h"
#include "pidComputer.h"

#include "../pidComputationValues.h"
#include "../pid.h"
#include "../instructionType.h"
#include "../parameters/pidParameter.h"
#include "../pidMotion.h"
#include "../pidCurrentValues.h"
#include "../pidMotionError.h"

#include "../../simulation/motionSimulation.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"


/**
 * @private
 * Computes the next value of the pid.
 * @param instructionType the pid that we want to compute (alpha/theta)
 * @param pidType the type of pid that we want to compute (between 0 and PID_TYPE_COUNT)
 * @param currentPosition the current position of the wheels (either alphaPosition, either thetaPosition)
 * @param time the time in pid sampling
 */
float computeNextPID(PidMotion* pidMotion, enum InstructionType instructionType, MotionInstruction* motionInstruction, PidCurrentValues* pidCurrentValues, PidMotionError* motionError, float time) {
    unsigned char rollingTestMode = getRollingTestMode(pidMotion);
    enum PidType pidType = motionInstruction->pidType;
    float currentPosition = pidCurrentValues->position;

    // instructionIndex = Alpha / Theta
    // pidType = Forward / Rotation / Final Approach ...
    unsigned char pidIndex = getIndexOfPid(instructionType, pidType);
    PidParameter* pidParameter = getPidParameter(pidMotion, pidIndex, rollingTestMode);

    if (!pidParameter->enabled) {
        return 0.0f;
    }

    float normalPosition = computeNormalPosition(motionInstruction, time);
    pidCurrentValues->normalPosition = normalPosition;

    float positionError = normalPosition - currentPosition;
    float normalSpeed = computeNormalSpeed(motionInstruction, time);
    float result = computePidCorrection(motionError, pidParameter, normalSpeed, positionError);

    return result;
}

/**
 * Compute the PID when the instruction is very simple (not b spline)
 */
void simpleMotionUCompute(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
	PidComputationValues* computationValues = &(pidMotion->computationValues);
    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaInst = &(motionDefinition->inst[ALPHA]);

    PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
    PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);

    PidMotionError* thetaError = &(computationValues->errors[THETA]);
    PidMotionError* alphaError = &(computationValues->errors[ALPHA]);


    float pidTime = computationValues->pidTime;

    thetaCurrentValues->u = computeNextPID(pidMotion, THETA, thetaInst, thetaCurrentValues, thetaError, pidTime);
    alphaCurrentValues->u = computeNextPID(pidMotion, ALPHA, alphaInst, alphaCurrentValues, alphaError, pidTime);
}