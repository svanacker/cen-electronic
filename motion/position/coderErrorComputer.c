#include <math.h>

#include "coderErrorComputer.h"

#include "../pid/instructionType.h"
#include "../../motion/pid/pidMotion.h"
#include "../../motion/pid/alphaTheta.h"

#include "../../motion/position/coders.h"

void computeCurrentPositionUsingCoders(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
    PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);

    // 2 dependant Wheels (direction + angle)
    float value0 = (float)getCoderValue(CODER_LEFT);
    float value1 = (float)getCoderValue(CODER_RIGHT);

    // Compute real position of wheel
    thetaCurrentValues->position = computeTheta(value0, value1);
    alphaCurrentValues->position = computeAlpha(value0, value1);
}

void computeErrorsWithNextPositionUsingCoders(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {

    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaInst = &(motionDefinition->inst[ALPHA]);

    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[THETA]);
    PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[ALPHA]);

    // Compute the difference between next position and real position
    // In fact, we store thetaError and alphaError with nextPosition just to know if the error is small
    // enough to consider that we are in final approach !
    computationValues->thetaError = fabsf(thetaInst->nextPosition - thetaCurrentValues->position);
    computationValues->alphaError = fabsf(alphaInst->nextPosition - alphaCurrentValues->position);
}
