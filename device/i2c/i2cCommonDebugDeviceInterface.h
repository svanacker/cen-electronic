#ifndef I2C_COMMON_DEBUG_DEVICE_INTERFACE_H
#define I2C_COMMON_DEBUG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to see the content of all I2C bus. */
#define COMMAND_I2C_COMMON_DEBUG_LIST_BUS                     'L'

/** Command to see the content of the I2C bus connection. */
#define COMMAND_I2C_COMMON_DEBUG_LIST_BUS_CONNECTION          'l'

/** Command to wait the I2C bus. */
#define COMMAND_I2C_COMMON_DEBUG_WAIT                        'w'
/**
* Get the I2C debug device interface.
*/
DeviceInterface* getI2cCommonDebugDeviceInterface();

#endif
