#ifndef MOTION_CALIBRATION_H
#define MOTION_CALIBRATION_H

#include "../../common/io/outputStream.h"

#include "../pid/pidMotion.h"

// CALIBRATION

void squareCalibration(PidMotion* pidMotion, unsigned char type, float lengthInMM, OutputStream* notificationOutputStream);

void squareCalibrationUsingSpline(PidMotion* pidMotion, unsigned char type, float lengthInMM, OutputStream* notificationOutputStream);
#endif
