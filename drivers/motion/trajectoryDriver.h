#ifndef TRAJECTORY_DRIVER_H
#define TRAJECTORY_DRIVER_H

#include <stdbool.h>

bool trajectoryDriverSetAbsolutePosition(float x, float y, float deciDegree);

bool trajectoryDriverUpdateRobotPosition();

#endif
