#ifndef I2C_DEBUG_H
#define I2C_DEBUG_H

#include "../../common/io/buffer.h"

/**
 * Returns if we must debug I2C or not.
 */
bool getDebugI2cCEnabled();

/**
 * Enabled or not the I2C Debug Buffer.
 */
void setDebugI2cEnabled(bool enabled);

/**
 * Get the input buffer to debug I2C.
 */
Buffer* getDebugI2cInputBuffer();

/**
 * Get the output buffer to debug I2C.
 */
Buffer* getDebugI2cOutputBuffer();

/**
 * Init the debug buffers.
 */
void initI2CDebugBuffers(Buffer* aDebugI2cInputBuffer,
                         char (*debugI2cInputBufferArray)[],
                         unsigned char debugI2cInputBufferLength,
                         Buffer* aDebugI2cOutputBuffer,
                         char (*debugI2cOutputBufferArray)[],
                         unsigned char debugI2cOutputBufferLength
);

/**
 * Print the content of debug buffers;
 */
void printI2cDebugBuffers();

#endif
