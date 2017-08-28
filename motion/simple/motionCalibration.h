#ifndef MOTION_CALIBRATION_H
#define MOTION_CALIBRATION_H

#include "../pid/pidMotion.h"

// CALIBRATION

void squareCalibration(PidMotion* pidMotion, unsigned char type, float lengthInMM);

#endif
