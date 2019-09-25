#ifndef GOLDENIUM_DEVICE_INTERFACE_2019_H
#define GOLDENIUM_DEVICE_INTERFACE_2019_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

#define COMMAND_2019_FORK_PREPARE_TAKE_GOLDENIUM  'p'

#define COMMAND_2019_FORK_TAKE_GOLDENIUM          't'

#define COMMAND_2019_FORK_DROP_GOLDENIUM          'd'

/**
 * Get the device interface for Goldenium 2019.
 */
DeviceInterface* getGoldenium2019DeviceInterface(void);

#endif
