#ifndef I2C_SLAVE_LINK_H
#define I2C_SLAVE_LINK_H

#include "../../../common/io/outputStream.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/buffer.h"
#include "../../../common/io/streamLink.h"


/**
 * SCHEMA OF I2C SLAVE STREAM ARCHITECTURE
 *        _________________
 *       |                 |      (READ ADDRESS : ex : 0x41)
 *       |   I2C SLAVE     |------------------------------------------------v
 *       |  I2C interrupt  |                                                |
 *       |_________________|                                                |
 *              |                                                           |
 *              | (WRITE ADDRESS : ex : 0x40)                               |
 *              | int data = SlaveReadI2C()                                 |
 *  ____________|______________________                                     |
 * |            v                      |                                    |
 * | i2cSlaveInputBuffer->outputStream |                                    |
 * |-----------------------------------|                                    |
 * |      i2cSlaveInputBuffer          |                                    |
 * |-----------------------------------|                                    |
 * |  i2cSlaveInputBuffer->inputStream |                                    |
 * |___________________________________|                                    |
 *              |                                                           |
 *              v                                                           |
 *  Handle asynchronously by Main Procedure                                 |
 *              |                                                           |
 *              v                                                           |
 *  ____________|______________________                                     |
 * |            v                      |                                    |
 * | i2cSlaveOutputBuffer->outputStream|                                    |
 * |-----------------------------------|                                    |
 * |      i2cSlaveOutputBuffer         |                                    |
 * |-----------------------------------|                                    |
 * | i2cSlaveOutputBuffer->inputStream | <--------READ DATA-----------------|
 * |___________________________________|                                    |
 *                                                                          v
 *                                                                SlaveWriteI2C(data)
 *                                                                          |
 *                                                                          v
 *                                                                   _________________
 *                                                                   |   I2C MASTER   |
 *                                                                   | InputStream    |
 *                                                                   |________________|
 * We expose i2cSlaveBuffer as an inputStream by the main procedure.
 * With this, i2c is considered as a stream
 */

/**
 * Open a stream link for I2C.
 * We do not use inputStream and outputStream arround I2C, because
 * I2C is not really a stream because it uses interrupt do load and send info.
 * So we just use input/output buffer which exposes input/outputStream
 */
void openSlaveI2cStreamLink(StreamLink* i2cStreamLink,
        Buffer* inputBuffer,
		char (*inputBufferArray)[],
		unsigned char inputBufferLength,
        Buffer* outputBuffer,
		char (*outputBufferArray)[],
		unsigned char outputBufferLength,
        int i2cAddress);

#endif


