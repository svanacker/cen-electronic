#ifndef SYSTEM_DEBUG_DEVICE_INTERFACE_H
#define SYSTEM_DEBUG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command to show log configuration. */
#define COMMAND_LOG '$'

/** Command to debug the I2C. */
#define COMMAND_DEBUG_I2C '"'

/**
* Get the system debug device interface.
*/
DeviceInterface* getSystemDeviceInterface();

#endif
