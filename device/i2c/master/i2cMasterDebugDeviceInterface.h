#ifndef I2C_MASTER_DEBUG_DEVICE_INTERFACE_H
#define I2C_MASTER_DEBUG_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"

#define I2C_MASTER_DEBUG_DEVICE_HEADER        'I'

/** Command to debug the I2C. */
#define COMMAND_DEBUG_I2C                     'd'

/** Command to add a char to an I2C slave with an address. */
#define COMMAND_SEND_CHAR_I2C_SLAVE           'w'

/** Command to read a char to an I2C slave with an address. */
#define COMMAND_READ_CHAR_I2C_SLAVE           'r'

/**
* Get the I2C debug device interface.
*/
DeviceInterface* getI2cMasterDebugDeviceInterface();

#endif
