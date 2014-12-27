#ifndef SERIAL_DEBUG_DEVICE_INTERFACE_H
#define SERIAL_DEBUG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"

/** Command to see the content of Serial Input Buffers. */
#define COMMAND_SERIAL_INPUT_BUFFERS     'b'

/**
* Get the serial debug device interface.
*/
DeviceInterface* getSerialDebugDeviceInterface(void);

#endif
