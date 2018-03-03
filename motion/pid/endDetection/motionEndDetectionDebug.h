#ifndef MOTION_END_DETECTION_DEBUG_H
#define MOTION_END_DETECTION_DEBUG_H

#include "../../../common/io/outputStream.h"
#include "../pidMotion.h"
#include "../parameters/pidParameter.h"
#include "motionEndDetectionParameter.h"

// PARAMETERS
void printMotionEndDetectionParameter(OutputStream* outputStream, MotionEndDetectionParameter* parameter);

// COMPUTATION VALUES

/**
 * Show a table with all parameters and current motion End Infos
 * @param outputStream
 * @param pidMotion
 */
void printMotionEndInfos(OutputStream* outputStream, PidMotion* pidMotion);

#endif
