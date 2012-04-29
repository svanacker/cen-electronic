#include "trajectoryErrorComputer.h"

#include "../../motion/pid/pid.h"
#include "../../motion/position/trajectory.h"

void computeErrorsUsingTrajectory(PidMotion* pidMotion) {
    // get current position of the robot
    Position* position = getPosition();

    // Get the
    float angle = computeBSplineOrientationWithDerivative(curve, pidMotion->pidTime);

    // alphaMotion->position = position->pos.orientation;

    // pidMotion->thetaError =
}
