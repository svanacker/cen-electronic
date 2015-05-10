#ifndef I2C_MASTER_OUTPUT_STREAM_H
#define I2C_MASTER_OUTPUT_STREAM_H

#include "../../../common/i2c/i2cCommon.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/buffer.h"

/**
 * A global structure used to store every information about the I2C outputStream.
 */
typedef struct {
    // The bus connection we manage
    I2cBusConnection* i2cBusConnection;
    // The outputStream object with specific callback
    OutputStream* outputStream;
    // The underlying buffer
    Buffer* outputBuffer;
} I2cMasterOutputStream;

/**
* Init an outputStream around i2c with an address.
* @param i2cMasterOutputStream a global structure used to store every information about the outputStream
* @param outputStream a structure to initialize
* @param i2cBuffer an internal i2cBuffer to avoid unefficient multiples calls with chars
*/
void initMasterI2cOutputStream(I2cMasterOutputStream* i2cMasterOutputStream,
                               I2cBusConnection* i2cBusConnection,
                               OutputStream* outputStream,
                               Buffer* i2cBuffer);

#endif
