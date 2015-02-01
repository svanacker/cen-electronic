#ifndef LOG_DEVICE_INTERFACE_H
#define LOG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to show log configuration. */
#define COMMAND_LOG                        'r'

/** Command to change the log configuration. */
#define COMMAND_WRITE_LOG_LEVEL            'w'

/**
* Get the Log device interface.
* @return a pointer on the log device Interface.
*/
DeviceInterface* getLogDeviceInterface(void);

#endif
