#ifndef I2C_SLAVE_DEBUG_DEVICE_INTERFACE_H
#define I2C_SLAVE_DEBUG_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"

#define I2C_SLAVE_DEBUG_DEVICE_HEADER        'i'

/** Command to debug the I2C. */
#define COMMAND_DEBUG_I2C                     'd'

/** Command to add a char to the master. */
#define COMMAND_SEND_CHAR_I2C_TO_MASTER       'w'

/** Command to add a char to the master. */
#define COMMAND_READ_CHAR_I2C_FROM_MASTER     'r'

/**
* Get the I2C debug device interface.
*/
DeviceInterface* getI2cSlaveDebugDeviceInterface();

#endif
