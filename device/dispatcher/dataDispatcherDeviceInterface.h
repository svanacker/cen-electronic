#ifndef DATA_DISPATCHER_DEVICE_INTERFACE_H
#define DATA_DISPATCHER_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command to see the list of dispacher. */
#define COMMAND_DISPATCHER_LIST          'D'

/**
* Get the data dispatcher device interface.
*/
DeviceInterface* getDataDispatcherDeviceInterface(void);

#endif
