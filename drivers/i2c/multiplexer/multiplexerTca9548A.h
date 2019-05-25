#ifndef MULTIPLEXER_TCA9548A_H
#define MULTIPLEXER_TCA9548A_H

/**
 * Encapsulates the TCA9548A as an I2C Multiplexer.
 */

#include "../../../common/io/outputStream.h"
#include "../../../common/i2c/i2cCommon.h"

#include "multiplexer.h"

/**
 * Returns the associated I2cBusConnection link to the Multiplexer.
 * @param multiplexer
 * @param i2cConnection
 */
I2cBusConnection* getMultiplexerI2cBusConnection(Multiplexer* multiplexer);


/**
 * Init the Tca9548A by wrapping it into a specific Structure to handle it
 * transparently
 * @param multiplexer
 */
void initMultiplexerTca9548A(Multiplexer* multiplexer, 
                             I2cBusConnection* i2cConnection,
                             bool useChannelMasksCache);

#endif
