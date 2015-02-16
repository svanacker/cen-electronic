#ifndef I2C_MASTER_INPUT_STREAM_H
#define I2C_MASTER_INPUT_STREAM_H

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"

/**
 * A global structure used to store every information about the I2C inputStream.
 */
typedef struct {
    // The bus we manage
    I2cBus* i2cBus;
    // The inputStream object with specific callback
    InputStream* outputStream;
    // The underlying input buffer
    Buffer* inputBuffer;
} I2cMasterInputStream;

/**
* Init an inputStream around i2c with an address.
* @param 
* @param i2cInputBuffer the buffer to read from i2c slave
* @param inputStream a structure to initialize
* @param the write address for I2C
*/
void initMasterI2cInputStream(I2cMasterInputStream* i2cMasterInputStream,
                              I2cBus* i2cBus,
                              Buffer* i2cInputBuffer,
                              InputStream* inputStream,
                              unsigned char i2cWriteAddress);

#endif
