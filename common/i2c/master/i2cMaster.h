#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include "../i2cConstants.h"

#include "../../../common/io/buffer.h"

/**
* Sends the buffer to the I2C.
* @param address the address of I2C that we send
* @param buffer the buffer of data
*/
void i2cMasterWriteBuffer( char address, Buffer* buffer );

/**
* Sends a char to the I2C.
* @param address the address of I2C that we send
* @param c the char to send to I2C bus
*/
void i2cMasterWriteChar(char address, char c);

/**
 * Write a command register index, and read the corresponding
 * value.
 * Useful for many I2C Device, but not for stream
 * @see i2cMasterReadChar
 */
unsigned char i2cMasterReadRegisterValue(char address,
								char commandRegister);

/**
 * Read the current value for the I2C device.
 * If data is available, Slave will return the value
 * If not data available, Slave will return 
 * I2C_SLAVE_NO_DATA_IN_READ_BUFFER
 */
unsigned char i2cMasterReadChar(char address);


#endif
