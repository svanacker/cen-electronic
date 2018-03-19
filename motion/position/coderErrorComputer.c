#include <math.h>

#include "coderErrorComputer.h"

#include "../../common/math/cenMath.h"

#include "../pid/pidTimer.h"
#include "../pid/instructionType.h"
#include "../../motion/pid/pidMotion.h"
#include "../../motion/pid/alphaTheta.h"

#include "../../motion/position/coders.h"
#include "../../robot/kinematics/robotKinematics.h"
#include "../../common/math/cenMath.h"

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

    // Compute the speed by using the delta between current and previous position / elapsedTime (if not equal to 0))
    float elapsedTimeInSecond = computationValues->pidTimeInSecond - computationValues->lastPidTimeInSecond;
    if (floatEqualsZero(elapsedTimeInSecond)) {
        thetaCurrentValues->currentSpeed = 0.0f;
        alphaCurrentValues->currentSpeed = 0.0f;        
    }
    else {
        thetaCurrentValues->currentSpeed = (theta - thetaCurrentValues->currentPosition) / elapsedTimeInSecond;
        alphaCurrentValues->currentSpeed = (alpha - alphaCurrentValues->currentPosition) / elapsedTimeInSecond;        
    }

    // Store the current Position
    thetaCurrentValues->currentPosition = theta;
    alphaCurrentValues->currentPosition = alpha;
}

