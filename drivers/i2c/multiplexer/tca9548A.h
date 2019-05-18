#ifndef PCF9548_H
#define PCF9548_H

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/delay/cenDelay.h"

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/i2c/master/i2cMaster.h"

#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

/**
 * Select the I2C Channel. When the channel is selected, all I2C Command on
 * the bus are forwarded to the selected I2C Channel but not to others.
 * @param i2cBusConnection
 * @param channel a channel between 0 and 7 (and not a binary mask !)
 */
void tca9548A_setChannel(I2cBusConnection* i2cBusConnection, unsigned char channel);

/**
 * Returns the I2C Channel (read operation of tca9548A_setChannel)
 * @param i2cBusConnection
 * @return a channel between 0 and 7
 */
unsigned char tca9548A_getChannel(I2cBusConnection* i2cBusConnection);

#endif