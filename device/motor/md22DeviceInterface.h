#ifndef MD22_DEVICE_INTERFACE_H
#define MD22_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/**
 * Defines the header to move the motor.
 */
#define COMMAND_MD22_MOVE         'w'

/**
 * Defines the header to move the motor.
 */
#define COMMAND_MD22_READ_VALUE   'r'

/**
 * Defines the header to get the version of the software on MD22
 */
#define COMMAND_MD22_SOFTWARE_REVISION   'v'

/**
 * Defines the header to stop the motors.
 */
#define COMMAND_MD22_STOP         'c'

/**
 * Interface for Device.
 */
DeviceInterface* getMD22DeviceInterface(void);

#endif
