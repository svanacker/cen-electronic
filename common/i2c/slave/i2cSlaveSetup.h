#ifndef I2C_SLAVE_SETUP_H
#define I2C_SLAVE_SETUP_H

/**
 * Init the i2c in the slave mode.
 * @param writeAddress (write address that the master sends)
 * BE CAREFUL that I2CADD register is the address >> 1 (divided by 2) !
 */
void i2cSlaveInitialize(unsigned char writeAddress);

unsigned char getI2cWriteAddress(void);

unsigned char getI2cReadAddress(void);

#endif
