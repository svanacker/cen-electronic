#ifndef I2C_SLAVE_STREAM_H
#define I2C_SLAVE_STREAM_H

#include "../../../common/io/outputStream.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/buffer.h"

/**
* Wrap all useful information when handling
* I2C Slave Interruption Data
*/
typedef struct I2cSlaveLink{
    /** The address to read. */
    char readAddress;
    /** The address to write. */
    char writeAddress;
    /** The inputStream. */
    InputStream* i2cInputStream;
    /** The inputBuffer to handle Input Stream. */
    Buffer* i2cInputBuffer;
} I2cSlaveLink;

// --- INPUT STREAM ---

/**
* Init an inputStream around i2c with an address.
* @param inputStream a structure to initialize
* @param i2cBuffer an internal i2cBuffer 
* @param i2cAddress the address to respond to i2c request
*/
void openSlaveI2cInputStream(InputStream* inputStream,
                         Buffer* i2cInputBuffer,
                         unsigned char i2cAddress);

// --- OUTPUT STREAM ---

/**
* Open a link (input/output) around i2c with an address.
* @param outputStream a structure to initialize
* @param i2cBuffer an internal i2cBuffer 
* @param i2cAddress the address to respond to i2c request
*/
void openSlaveI2cOutputStream(OutputStream* outputStream,
                         Buffer* i2cBuffer,
                         unsigned char i2cWriteAddress);

#endif
