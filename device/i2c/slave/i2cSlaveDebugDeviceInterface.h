#ifndef I2C_SLAVE_DEBUG_DEVICE_INTERFACE_H
#define I2C_SLAVE_DEBUG_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

/** Command to see the content of the I2C debug. */
#define COMMAND_I2C_DEBUG_SLAVE_DEBUG                         'b'

/** Command to get the address of the I2C Slave. */
#define COMMANG_I2C_DEBUG_SLAVE_ADDRESS                       'd'

/** Command to enable or disable the Debug. */
#define COMMAND_I2C_DEBUG_SLAVE_ENABLE_DISABLE                'e'

/** Command to add a char to the master. */
#define COMMAND_I2C_DEBUG_SLAVE_SEND_CHAR_I2C_TO_MASTER       'w'

/** Command to add a char to the master. */
#define COMMAND_I2C_DEBUG_SLAVE_READ_CHAR_I2C_FROM_MASTER     'r'

/**
 * Get the I2C debug device interface.
 */
DeviceInterface* getI2cSlaveDebugDeviceInterface();

#endif
