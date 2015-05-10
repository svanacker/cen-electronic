#ifndef I2C_SLAVE_SETUP_H
#define I2C_SLAVE_SETUP_H

#include "../../../common/i2c/i2cCommon.h"

/**
 * Init the i2c in the slave mode.
 * @param i2cBusConnection the encapsulation of the i2c Address (write address that the master sends)
 * BE CAREFUL that I2CADD register is the address >> 1 (divided by 2) !
 */
void i2cSlaveInitialize(I2cBusConnection* i2cBusConnection);

#endif
