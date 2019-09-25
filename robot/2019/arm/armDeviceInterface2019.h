#ifndef ARM_DEVICE_INTERFACE_2019_H
#define ARM_DEVICE_INTERFACE_2019_H

#include "../../../device/device.h"
#include "../../../device/deviceConstants.h"

// ARM ON
#define COMMAND_2019_ARM_ON                       '_'

// ARM OFF
#define COMMAND_2019_ARM_OFF                      '|'


/**
 * Get the device interface for Arm 2019.
 */
DeviceInterface* getArm2019DeviceInterface(void);

#endif
