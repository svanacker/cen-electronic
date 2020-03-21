#ifndef I2C_MASTER_SETUP_H
#define I2C_MASTER_SETUP_H

#include "../../../common/i2c/i2cCommon.h"

/**
 * Initializes the I2C bus for a master.
 */
void i2cMasterInitialize(I2cBus* i2cBus);

/**
 * Finalizes the I2C bus for a master.
 */
void i2cMasterFinalize(I2cBus* i2cBus);

#endif
