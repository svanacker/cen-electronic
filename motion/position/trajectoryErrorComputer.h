#ifndef TRAJECTORY_ERROR_COMPUTER_H
#define TRAJECTORY_ERROR_COMPUTER_H

#include "../../motion/pid/pid.h"

/**
* Compute errors using trajectory ( => absolute position)).
*/
void computeErrorsUsingTrajectory(    PidMotion* pidMotion);

#endif
