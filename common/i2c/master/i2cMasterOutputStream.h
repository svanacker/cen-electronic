#ifndef I2C_MASTER_OUTPUT_STREAM_H
#define I2C_MASTER_OUTPUT_STREAM_H

#include "../../../common/io/outputStream.h"
#include "../../../common/io/buffer.h"

/**
* Init an outputStream arround i2c with an address.
* @param outputStream a structure to initialize
* @param i2cBuffer an internal i2cBuffer to avoid
* @param i2cWriteAddress the I2C address corresponding to the I2C Slave address
*/
void initMasterI2cOutputStream(OutputStream* outputStream,
                         Buffer* i2cBuffer,
                         unsigned char i2cWriteAddress);

#endif
