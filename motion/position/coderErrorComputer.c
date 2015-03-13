#include <math.h>

#include "coderErrorComputer.h"

#include "../../motion/pid/pid.h"
#include "../../motion/pid/alphaTheta.h"

#include "../../motion/position/coders.h"

void computeErrorsUsingCoders(PidMotion* pidMotion) {
    PidMotionDefinition* currentMotionDefinition = &(pidMotion->currentMotionDefinition);

    MotionInstruction* thetaInst = &(currentMotionDefinition->inst[INSTRUCTION_THETA_INDEX]);
    MotionInstruction* alphaInst = &(currentMotionDefinition->inst[INSTRUCTION_ALPHA_INDEX]);

    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidCurrentValues* thetaCurrentValues = &(computationValues->currentValues[INSTRUCTION_THETA_INDEX]);
    PidCurrentValues* alphaCurrentValues = &(computationValues->currentValues[INSTRUCTION_ALPHA_INDEX]);

    // 2 dependant Wheels (direction + angle)
    float value0 = (float) getCoderValue(CODER_LEFT);
    float value1 = (float) getCoderValue(CODER_RIGHT);

    // Compute real position of wheel
    thetaCurrentValues->position = computeTheta(value0, value1);
    alphaCurrentValues->position = computeAlpha(value0, value1);

    // Compute the difference between next position and real position
    computationValues->thetaError = fabsf(thetaInst->nextPosition - thetaCurrentValues->position);
    computationValues->alphaError = fabsf(alphaInst->nextPosition - alphaCurrentValues->position);
}
