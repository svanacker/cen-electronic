#ifndef BSPLINE_PID_COMPUTER_H
#define BSPLINE_PID_COMPUTER_H

#include "../pidMotion.h"

/**
* Define the function used to compute U for both alpha / theta motion in case of bspline.
*/
void bSplineMotionUCompute(PidMotion* pidMotion, PidMotionDefinition* pidMotionDefinition);

#endif
