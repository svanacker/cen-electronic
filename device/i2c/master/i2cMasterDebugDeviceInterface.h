#ifndef I2C_MASTER_DEBUG_DEVICE_INTERFACE_H
#define I2C_MASTER_DEBUG_DEVICE_INTERFACE_H

#include "../../../device/deviceInterface.h"
#include "../../../device/deviceConstants.h"

/** Command to debug the I2C. */
#define COMMAND_I2C_MASTER_DEBUG_PRINT_BUFFER                'd'

/** Command to enable or disable the Debug. */
#define COMMAND_I2C_MASTER_DEBUG_ENABLE_DISABLE              'e'

/** Command to add a char to an I2C slave with an address. */
#define COMMAND_I2C_MASTER_DEBUG_SEND_CHAR_TO_SLAVE          'w'

/** Command to read a char to an I2C slave with an address. */
#define COMMAND_I2C_MASTER_DEBUG_READ_CHAR_FROM_SLAVE        'r'

/** Command to start the I2C bus. */
#define COMMAND_I2C_MASTER_DEBUG_START_I2C_BUS               'S'

/** Command to stop the I2C bus. */
#define COMMAND_I2C_MASTER_DEBUG_STOP_I2C_BUS                's'

/** Command to do an ack to the I2C Bus. */
#define COMMAND_I2C_MASTER_DEBUG_ACK                         'K'

/** Command to do an Nack to the I2C Bus. */
#define COMMAND_I2C_MASTER_DEBUG_NACK                        'k'

/**
* Get the I2C debug device interface.
*/
DeviceInterface* getI2cMasterDebugDeviceInterface();

#endif
