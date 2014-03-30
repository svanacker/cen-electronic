#ifndef ROBOT_INFRARED_DETECTOR_DRIVER_H
#define ROBOT_INFRARED_DETECTOR_DRIVER_H

#include "../../common/commons.h"

#include "robotInfraredDetectorDeviceInterface.h"

/**
 * Return TRUE, if there is an obstacle
 * @param type BACKWARD / FORWARD
 */
bool robotInfraredDetectorHasObstacle(unsigned char type);

#endif

