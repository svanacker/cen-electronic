#ifndef PLIERS_DEVICE_INTERFACE_2011_H
#define PLIERS_DEVICE_INTERFACE_2011_H

#include "../../device/device.h"

/**
 * Close the pliers to take the pawns.
 */
#define COMMAND_PLIERS_2011_CLOSE        'J'

/**
 * Close the pliers to close the pliers at the beginning.
 */
#define COMMAND_PLIERS_2011_INIT_CLOSE    '#'

/**
 * Open the pliers.
 */
#define COMMAND_PLIERS_2011_OPEN        'I'

/**
 * Get the device interface for pliers 2011.
 */
DeviceInterface* getPliers2011DeviceInterface();

#endif
