#include <math.h>

#include "coderErrorComputer.h"

#include "../../motion/pid/pid.h"
#include "../../motion/pid/alphaTheta.h"

#include "../../motion/position/coders.h"

void computeErrorsUsingCoders(PidMotion* pidMotion) {
    MotionInstruction* thetaInst = pidMotion->inst[INSTRUCTION_THETA_INDEX];
    MotionInstruction* alphaInst = pidMotion->inst[INSTRUCTION_ALPHA_INDEX];

    Motion* thetaMotion = pidMotion->motion[INSTRUCTION_THETA_INDEX];
    Motion* alphaMotion = pidMotion->motion[INSTRUCTION_ALPHA_INDEX];

    // 2 dependant Wheels (direction + angle)
    float value0 = (float) getCoderValue(CODER_LEFT);
    float value1 = (float) getCoderValue(CODER_RIGHT);

    // Compute real position of wheel
    thetaMotion->position = computeTheta(value0, value1);
    alphaMotion->position = computeAlpha(value0, value1);

    // Compute the difference between next position and real position
    pidMotion->thetaError = fabsf(thetaInst->nextPosition - thetaMotion->position);
    pidMotion->alphaError = fabsf(alphaInst->nextPosition - alphaMotion->position);
}
