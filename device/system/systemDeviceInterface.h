#ifndef SYSTEM_DEVICE_INTERFACE_H
#define SYSTEM_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Get the last error if any, 0x0000 if none. */
#define COMMAND_GET_LAST_ERROR      'e'

/** Clear the last error if any */
#define COMMAND_CLEAR_LAST_ERROR    'E'

/** Command to show devices list. */
#define COMMAND_DEVICE_LIST        'd'

/** Command to show the content of a device by his .*/
#define COMMAND_USAGE_SPECIFIC_DEVICE 's'

/** Command to show usage for all devices. */
#define COMMAND_USAGE              'u'

/** Command to show usage all usages with a problem on definition. */
#define COMMAND_USAGE_PROBLEM      'U'

/** Command to show notification for all devices. */
#define COMMAND_NOTIFICATION       'n'

/** Command to wait a certain amount of time (in milliseconds). */
#define COMMAND_WAIT               'W'

/** Command to show the name of the BOARD. */
#define COMMAND_BOARD_NAME           'N'

/** Command to know if the remote board is present. */
#define COMMAND_PING               'P'

/**
* Get the system device interface.
* @return a pointer on the system device Interface.
*/
DeviceInterface* getSystemDeviceInterface(void);

#endif
