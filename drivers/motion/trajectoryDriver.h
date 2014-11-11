#ifndef TRAJECTORY_DRIVER_H
#define TRAJECTORY_DRIVER_H

#include "../../common/commons.h"

#include "../../drivers/dispatcher/DriverDataDispatcher.h"


bool trajectoryDriverSetAbsolutePosition(float x, float y, float deciDegree);

bool trajectoryDriverUpdateRobotPosition();

#endif
