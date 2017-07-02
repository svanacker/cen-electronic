#ifndef I2C_COMMON_DEBUG_DEVICE_INTERFACE_H
#define I2C_COMMON_DEBUG_DEVICE_INTERFACE_H

#include "../../device/deviceInterface.h"
#include "../../device/deviceConstants.h"

/** Command to see the content of the I2C debug. */
#define COMMAND_I2C_DEBUG_COMMON_LIST_BUS                     'L'

/**
* Get the I2C debug device interface.
*/
DeviceInterface* getI2cCommonDebugDeviceInterface();

#endif
