#ifndef SYSTEM_DEBUG_DEVICE_INTERFACE_H
#define SYSTEM_DEBUG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define SYSTEM_DEBUG_DEVICE_HEADER        '*'

/** Command to change the log configuration. */
#define COMMAND_WRITE_LOG_LEVEL           'L'

/** Command to debug the I2C. */
#define COMMAND_DEBUG_I2C                'I'

/** Command to see the list of dispacher. */
#define COMMAND_DISPATCHER_LIST          'D'

/**
* Get the system debug device interface.
*/
DeviceInterface* getSystemDebugDeviceInterface();

#endif
