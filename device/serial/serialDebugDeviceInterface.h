#ifndef SERIAL_DEBUG_DEVICE_INTERFACE_H
#define SERIAL_DEBUG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command to see the content of all Serial Input Buffers. */
#define COMMAND_SERIAL_INPUT_ALL_BUFFER     'R'

/** Command to see the content of a specific Serial Input Buffer. */
#define COMMAND_SERIAL_INPUT_BUFFER         'r'

/** Command to clear the of a specific Serial Input Buffer. */
#define COMMAND_SERIAL_CLEAR_INPUT_BUFFER   'c'

/**
* Get the serial debug device interface.
*/
DeviceInterface* getSerialDebugDeviceInterface(void);

#endif
