#ifndef TRAJECTORY_DEVICE_H
#define TRAJECTORY_DEVICE_H

#include "../../../common/io/outputStream.h"

#include "../../../device/device.h"

// DEVICE INTERFACE

/**
* Returns a device descriptor on trajectory device.
*/
DeviceDescriptor* getTrajectoryDeviceDescriptor(void);

/**
* Notify the absolute position without the header.
*/
void notifyAbsolutePositionWithoutHeader(OutputStream* outputStream);

#endif
