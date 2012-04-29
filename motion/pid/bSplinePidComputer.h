#ifndef BSPLINE_PID_COMPUTER_H
#define BSPLINE_PID_COMPUTER_H

#include "pidComputer.h"
#include "pid.h"

/**
* Define the function used to compute U for both alpha / theta motion in case of bspline.
*/
void bSplineMotionUCompute(MotionInstruction* thetaInst,
                                    MotionInstruction* alphaInst,
                                    Motion* thetaMotion,
                                    Motion* alphaMotion, 
									float pidTime);

#endif
