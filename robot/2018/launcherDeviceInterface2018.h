#ifndef LAUNCHER_DEVICE_INTERFACE_2018_H
#define LAUNCHER_DEVICE_INTERFACE_2018_H

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

/**
 * Prepare the launch of one ball
 */
#define LAUNCHER_PREPARE_BALL_COMMAND  'p'

/**
 * Send the ball
 */
#define LAUNCHER_SEND_BALL_COMMAND     's'

/**
 * Get the device interface for launcher 2018.
 */
DeviceInterface* getLauncher2018DeviceInterface(void);

#endif
