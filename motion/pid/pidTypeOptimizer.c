#include "pidConstants.h"

#include <math.h>

#include "pidMotion.h"

#include "../position/coderErrorComputer.h"

void changePidTypeIfFinalApproach(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    float pidTime = pidMotion->computationValues.pidTimeInSecond;

    PidComputationValues* computationValues = &(pidMotion->computationValues);

    // Theta and Alpha Error are only used compared to the next position as
    // we only use it to change the PID Type for final Approach
    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaInst = &(motionDefinition->inst[ALPHA]);
    
    PidComputationInstructionValues* thetaValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaValues = &(computationValues->values[ALPHA]);
    
    float thetaError = fabsf(thetaInst->nextPosition - thetaValues->currentPosition);
    float alphaError = fabsf(alphaInst->nextPosition - alphaValues->currentPosition);

    // Change PID type for final Approach
    if ((thetaError < ERROR_FOR_STRONG_PID) && (pidTime > thetaInst->t3 + TIME_PERIOD_AFTER_END_FOR_STRONG_PID)
        && (alphaError < ERROR_FOR_STRONG_PID) && (pidTime > alphaInst->t3 + TIME_PERIOD_AFTER_END_FOR_STRONG_PID)) {
        thetaInst->initialPidType = PID_TYPE_FINAL_APPROACH_INDEX;
        alphaInst->initialPidType = PID_TYPE_FINAL_APPROACH_INDEX;
    }
}