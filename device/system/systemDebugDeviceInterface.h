#ifndef SYSTEM_DEBUG_DEVICE_INTERFACE_H
#define SYSTEM_DEBUG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to change the log configuration. */
#define COMMAND_WRITE_LOG_LEVEL           'L'

/** Command to see the list of dispacher. */
#define COMMAND_DISPATCHER_LIST          'D'

/** Command to see the content of Serial Input Buffers. */
#define COMMAND_SERIAL_INPUT_BUFFERS     'S'

/**
* Get the system debug device interface.
*/
DeviceInterface* getSystemDebugDeviceInterface();

#endif
