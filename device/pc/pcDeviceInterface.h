#ifndef PC_DEVICE_INTERFACE_H
#define PC_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to see the list of Pipe. */
#define COMMAND_PIPE_LIST           'p'

/** Command to load some commands from a file. */
#define COMMAND_LOAD_COMMAND_FILE 'L'

/**
 * Get the pc device interface.
 * @return a pointer on the system device Interface.
 */
DeviceInterface* getPcDeviceInterface(void);

#endif
