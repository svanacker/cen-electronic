#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include "../i2cConstants.h"

#include "../../../common/io/buffer.h"

// PORTABLE FUNCTIONS

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
inline int portableMasterWriteI2C(char data);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
inline char portableMasterReadI2C( void );

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
inline void portableCloseI2C( void );

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
inline void portableMasterWaitSendI2C( void );

// USEFUL FUNCTION

/**
* Sends the buffer to the I2C.
* @param address the address of I2C that we send
* @param buffer the buffer of data
 *@param reg    the register to select
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
char i2cMasterReadRegisterValue(char address,
                                char commandRegister);

/**
 * Read the current value for the I2C device.
 * If data is available, Slave will return the value
 * If not data available, Slave will return 
 * I2C_SLAVE_NO_DATA_IN_READ_BUFFER
 */
char i2cMasterReadChar(char address);

/** BY JEROME
 * Read the all values from the I2C device.
 * Slave will return all values and store them in the buffer
 * @param address        the adress of i2c slave
 * @param reg            the register selected
 * @param length         the number of data to read
 * @param Buffer* buffer the buffer
 */
void i2cMasterRegisterReadBuffer(char address,char reg, char length, Buffer* buffer);

/** BY JEROME
 * Read the all values from the I2C device.
 * Slave will return all values and store them in the buffer
 * @param address        the adress of i2c slave
 * @param length         the number of data to read
 * @param Buffer* buffer the buffer
 */
void i2cMasterReadBuffer(char address, char length, Buffer* buffer);

#endif
