#ifndef MOTION_END_DETECTION_DEBUG_H
#define MOTION_END_DETECTION_DEBUG_H

#include "../../../common/io/outputStream.h"
#include "../pidMotion.h"
#include "../parameters/pidParameter.h"
#include "motionEndDetectionParameter.h"

// PARAMETERS
void printMotionEndDetectionParameter(OutputStream* outputStream, MotionEndDetectionParameter* parameter);

#endif
