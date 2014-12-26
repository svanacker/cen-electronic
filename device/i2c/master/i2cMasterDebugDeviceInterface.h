#ifndef I2C_MASTER_DEBUG_DEVICE_INTERFACE_H
#define I2C_MASTER_DEBUG_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

/** Command to debug the I2C. */
#define COMMAND_I2C_DEBUG_MASTER_DEBUG                     'd'

/** Command to enable or disable the Debug. */
#define COMMAND_I2C_DEBUG_MASTER_ENABLE_DISABLE              'e'

/** Command to add a char to an I2C slave with an address. */
#define COMMAND_I2C_DEBUG_MASTER_SEND_CHAR_TO_SLAVE           'w'

/** Command to read a char to an I2C slave with an address. */
#define COMMAND_I2C_DEBUG_MASTER_READ_CHAR_FROM_SLAVE         'r'

/** Command to do some intensive call to testDevice via Driver. */
#define COMMAND_I2C_DEBUG_MASTER_INTENSIVE_CALL_TO_SLAVE      'i'

/**
* Get the I2C debug device interface.
*/
DeviceInterface* getI2cMasterDebugDeviceInterface();

#endif
