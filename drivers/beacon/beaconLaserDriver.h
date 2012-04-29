#ifndef BEACON_LASER_DRIVER_H
#define BEACON_LASER_DRIVER_H

#include "../../common/2d/2d.h"
#include "../../common/io/outputStream.h"

#include "../../drivers/dispatcher/DriverDataDispatcher.h"

/**
 * Start remotely the beacon laser (with servo).
 */
BOOL beaconLaserDriverServoStart();

/**
 * Stop remotely the beacon laser (with servo).
 */
BOOL beaconLaserDriverServoStop();

/**
 * Notify the robot position to an outputStream.
 */
void appendRobotPosition(OutputStream* outputStream, char header, Point* point);

/**
 * Notify the beacon receiver
 */
BOOL notifyRobotPosition(Point* point);

#endif
