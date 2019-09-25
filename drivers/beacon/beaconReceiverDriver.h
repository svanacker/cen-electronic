#ifndef BEACON_RECEIVER_DRIVER_H
#define BEACON_RECEIVER_DRIVER_H

#include "../../common/commons.h"

#include "../../common/2d/2d.h"

#include "../driver.h"

/**
 * Update the opponent Robot position by calling the beacon Receiver through I2C.
 */
bool updateOpponentRobotPosition(Point* opponentRobotPosition);

#endif
