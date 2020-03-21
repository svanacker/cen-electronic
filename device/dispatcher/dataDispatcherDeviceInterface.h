#ifndef DATA_DISPATCHER_DEVICE_INTERFACE_H
#define DATA_DISPATCHER_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

#define COMMAND_DISPATCHER_DEBUG_DRIVER_REQUEST_BUFFER   'o'
#define COMMAND_DISPATCHER_DEBUG_DRIVER_RESPONSE_BUFFER  'i'

/** Command to see the list of dispatcher. */
#define COMMAND_DISPATCHER_LIST          'L'

/**
 * Get the data dispatcher device interface.
 */
DeviceInterface* getDataDispatcherDeviceInterface(void);

#endif
