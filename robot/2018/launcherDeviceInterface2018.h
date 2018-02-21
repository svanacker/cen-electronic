#ifndef LAUNCHER_DEVICE_INTERFACE_2018_H
#define LAUNCHER_DEVICE_INTERFACE_2018_H

#include "../../device/device.h"
#include "../../device/deviceConstants.h"

/**
 * Launch one ball.
 */
#define LAUNCHER_BALL_COMMAND          'w'

 /**
 * Index of the left launcher.
 */
#define LAUNCHER_LEFT_COMMAND          0x01

/**
 * Index of the right launcher.
 */
#define LAUNCHER_RIGHT_COMMAND         0x02

/**
 * Get the device interface for launcher 2018.
 */
DeviceInterface* getLauncher2018DeviceInterface(void);

#endif
