#ifndef IO_DEVICE_INTERFACE_H
#define IO_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

#define COMMAND_IO_READ          'r'

#define COMMAND_IO_WRITE         'w'

#define COMMAND_IO_DEBUG         'd'

/**
 * Interface for IO Device.
 */
DeviceInterface* getIODeviceInterface(void);

#endif

