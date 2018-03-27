#ifndef IO_EXPANDER_DEVICE_INTERFACE_H
#define IO_EXPANDER_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

#define COMMAND_IO_EXPANDER_READ_SINGLE_BIT     'r'

#define COMMAND_IO_EXPANDER_READ_VALUE          'R'

#define COMMAND_IO_EXPANDER_WRITE_SINGLE_BIT    'w'

#define COMMAND_IO_EXPANDER_WRITE_VALUE         'W'

#define COMMAND_IO_EXPANDER_DEBUG               'd'

/**
* Interface for IO Device.
*/
DeviceInterface* getIOExpanderDeviceInterface(void);

#endif

