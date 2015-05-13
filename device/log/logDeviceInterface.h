#ifndef LOG_DEVICE_INTERFACE_H
#define LOG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to show log configuration. */
#define COMMAND_LOG                        'r'

/** Command to change the log configuration for a specific Handler. */
#define COMMAND_WRITE_HANDLER_LOG_LEVEL            'w'

/** Command to change the log configuration for the global configuration. */
#define COMMAND_WRITE_GLOBAL_LOG_LEVEL            'W'

/**
* Get the Log device interface.
* @return a pointer on the log device Interface.
*/
DeviceInterface* getLogDeviceInterface(void);

#endif
