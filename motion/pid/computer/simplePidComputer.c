#include "simplePidComputer.h"
#include "pidComputer.h"

#include "../pidComputationValues.h"
#include "../pid.h"
#include "../instructionType.h"
#include "../parameters/pidParameter.h"
#include "../pidMotion.h"
#include "../pidMotionDefinition.h"
#include "../pidCurrentValues.h"
#include "../pidMotionError.h"

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
float computeNextPID(enum InstructionType instructionType, MotionInstruction* motionInstruction, PidCurrentValues* pidCurrentValues, PidMotionError* motionError, float time) {
    unsigned char rollingTestMode = getRollingTestMode();
    enum PidType pidType = motionInstruction->pidType;
    float currentPosition = pidCurrentValues->position;

    // instructionIndex = Alpha / Theta
    // pidType = Forward / Rotation / Final Approach ...
    unsigned pidIndex = getIndexOfPid(instructionType, pidType);
    PidParameter* pidParameter = getPidParameter(pidIndex, rollingTestMode);

    if (!pidParameter->enabled) {
        return 0.0f;
    }

    float normalPosition = computeNormalPosition(motionInstruction, time);
    float normalSpeed = computeNormalSpeed(motionInstruction, time);

    float positionError = normalPosition - currentPosition;
    float result = computePidCorrection(motionError, pidParameter, normalSpeed, positionError);

    return result;
}

/**
 * Compute the PID when the instruction is very simple (not b spline)
 */
void simpleMotionUCompute(void) {
    PidMotion* pidMotion = getPidMotion();
    PidMotionDefinition* motionDefinition = &(pidMotion->currentMotionDefinition);
    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaInst = &(motionDefinition->inst[ALPHA]);

    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
    PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);

    PidMotionError* thetaErr = &(computationValues->err[THETA]);
    PidMotionError* alphaErr = &(computationValues->err[ALPHA]);


    float pidTime = computationValues->pidTime;

    thetaCurrentValues->u = computeNextPID(THETA, thetaInst, thetaCurrentValues, thetaErr, pidTime);
    alphaCurrentValues->u = computeNextPID(ALPHA, alphaInst, alphaCurrentValues, alphaErr, pidTime);
}