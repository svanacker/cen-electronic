#ifndef LOG_DEVICE_INTERFACE_H
#define LOG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to show log configuration. */
#define COMMAND_LOG_HANDLER_LIST               'r'

/** Command to know how many logger are registered. */
#define COMMAND_GET_LOG_COUNT                  'c'

/** Command to change the log configuration for a specific Handler. */
#define COMMAND_WRITE_HANDLER_LOG_LEVEL            'w'

/** Command to change the log configuration for the global configuration. */
#define COMMAND_WRITE_GLOBAL_LOG_LEVEL            'W'

/** Command to write Hello World for a specified level. */
#define COMMAND_TEST_LOG                          'T'

/**
 * Get the Log device interface.
 * @return a pointer on the log device Interface.
 */
DeviceInterface* getLogDeviceInterface(void);

#endif
