#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include "../i2cConstants.h"

#include "../../../common/io/buffer.h"

#include "../../../common/i2c/i2cCommon.h"

// PORTABLE FUNCTIONS

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 * @param data to write by the I2C master component
 */
unsigned int portableMasterWriteI2C(I2cBus* i2cBus, unsigned char data);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 * @return read by the I2C master component
 */
unsigned char portableMasterReadI2C(I2cBus* i2cBus);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableCloseI2C(I2cBus* i2cBus);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableMasterWaitSendI2C(I2cBus* i2cBus);

// USEFUL FUNCTION

/**
* Sends the buffer to the I2C.
* @param address the address of I2C that we send
* @param buffer the buffer of data
*/
void i2cMasterWriteBuffer(I2cBus* i2cBus, unsigned char address, Buffer* buffer);

/**
* Sends a char to the I2C.
* @param address the address of I2C that we send
* @param c the char to send to I2C bus
*/
void i2cMasterWriteChar(I2cBus* i2cBus, unsigned char address, unsigned char c);

/**
 * Write a command register index, and read the corresponding
 * value.
 * Useful for many I2C Device, but not for stream
 * @see i2cMasterReadChar
 * @param address the address where to read the register value
 * @param commandRegister the register command
 */
unsigned char i2cMasterReadRegisterValue(I2cBus* i2cBus, unsigned char address, unsigned char commandRegister);

/**
 * Read the current value for the I2C device.
 * If data is available, Slave will return the value
 * If not data available, Slave will return 
 * I2C_SLAVE_NO_DATA_IN_READ_BUFFER
 */
unsigned char i2cMasterReadChar(I2cBus* i2cBus, unsigned char address);

/**
 * Read the all values from the I2C device.
 * Slave will return all values and store them in the buffer
 * @param address the address of i2c slave
 * @param register the register selected
 * @param length the number of data to read
 * @param Buffer* buffer the buffer
 */
void i2cMasterRegisterReadBuffer(I2cBus* i2cBus, unsigned char address, unsigned char register, unsigned char length, Buffer* buffer);

/**
 * Read the all values from the I2C device.
 * Slave will return all values and store them in the buffer
 * @param address the address of i2c slave
 * @param length the number of data to read
 * @param Buffer* buffer the buffer
 */
void i2cMasterReadBuffer(I2cBus* i2cBus, unsigned char address, unsigned char length, Buffer* buffer);

#endif
