#ifndef ROBOT_INFRARED_DETECTOR_H
#define ROBOT_INFRARED_DETECTOR_H

#include "../../common/commons.h"

/**
 * Detection is based on 2 GPD12 on left / right, and a gp2y0a02yk on the center
 */

/**
 * Init and a timer to search via infrared detector.
 */
void initRobotInfraredDetector();

/**
 * Returns if there is an obstacle or not.
 */
BOOL getRobotInfraredObstacle();

#endif
