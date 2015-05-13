#ifndef ROBOT_INFRARED_DETECTOR_DRIVER_H
#define ROBOT_INFRARED_DETECTOR_DRIVER_H

#include <stdbool.h>

#include "robotInfraredDetector.h"

/**
 * Return true, if there is an obstacle
 * @param type BACKWARD / FORWARD
 */
bool robotInfraredDetectorHasObstacle(enum InfraredDetectorGroupType type);

#endif

