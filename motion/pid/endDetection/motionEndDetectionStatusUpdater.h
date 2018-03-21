#ifndef MOTION_END_DETECTION_STATUS_UPDATER_H
#define MOTION_END_DETECTION_STATUS_UPDATER_H

#include <stdbool.h>

#include "../pidMotion.h"

/**
 * Update the status of the end motion detection.
 */
void updateEndDetectionStatusRegister(PidMotion* pidMotion, PidMotionDefinition* motionDefinition);

#endif
