#include <math.h>

#include "coderErrorComputer.h"

#include "../pid/pidTimer.h"
#include "../pid/instructionType.h"
#include "../../motion/pid/pidMotion.h"
#include "../../motion/pid/alphaTheta.h"

#include "../../motion/position/coders.h"
#include "../../robot/kinematics/robotKinematics.h"

void computeCurrentPositionUsingCoders(PidMotion* pidMotion) {
    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    // 2 dependant Wheels (left / right)
    float coderValueLeft = (float)getCoderValue(CODER_LEFT);
    float coderValueRight = (float)getCoderValue(CODER_RIGHT);

    RobotKinematics* robotKinematics = getRobotKinematics();
    float coderValueDistanceMMLeft = getCoderLeftWheelLengthForOnePulse(robotKinematics) * coderValueLeft;
    float coderValueDistanceMMRight = getCoderRightWheelLengthForOnePulse(robotKinematics) * coderValueRight;

    // left / right => theta / alpha
    float theta = computeTheta(coderValueDistanceMMLeft, coderValueDistanceMMRight);
    float alpha = computeAlpha(coderValueDistanceMMLeft, coderValueDistanceMMRight);

    // Compute the speed by multiplying the delta between current and previous position by the frequency
    thetaCurrentValues->currentSpeed = (theta - thetaCurrentValues->currentPosition) * getPidTimerFrequencyHertz();
    alphaCurrentValues->currentSpeed = (alpha - thetaCurrentValues->currentPosition) * getPidTimerFrequencyHertz();

    // Store the current Position
    thetaCurrentValues->currentPosition = theta;
    alphaCurrentValues->currentPosition = alpha;
}

void computeErrorsWithNextPositionUsingCoders(PidMotion* pidMotion, PidMotionDefinition* motionDefinition) {
    MotionInstruction* thetaInst = &(motionDefinition->inst[THETA]);
    MotionInstruction* alphaInst = &(motionDefinition->inst[ALPHA]);

    PidComputationValues* computationValues = &(pidMotion->computationValues);
    PidComputationInstructionValues* thetaCurrentValues = &(computationValues->values[THETA]);
    PidComputationInstructionValues* alphaCurrentValues = &(computationValues->values[ALPHA]);

    // Compute the difference between next position and real position
    // In fact, we store thetaError and alphaError with nextPosition just to know if the error is small
    // enough to consider that we are in final approach !
    computationValues->thetaError = fabsf(thetaInst->nextPosition - thetaCurrentValues->currentPosition);
    computationValues->alphaError = fabsf(alphaInst->nextPosition - alphaCurrentValues->currentPosition);
}
