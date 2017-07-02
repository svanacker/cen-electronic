#ifndef I2C_COMMON_DEBUG_DEVICE_H
#define I2C_COMMON_DEBUG_DEVICE_H

#include "../../common/i2c/i2cCommon.h"

#include "../../device/deviceDescriptor.h"

/**
 * The descriptor for the I2C Common debug device (list I2CBus, I2cBusConnection)
 */
DeviceDescriptor* getI2cCommonDebugDeviceDescriptor();

#endif
