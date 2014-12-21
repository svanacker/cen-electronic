#ifndef I2C_DEBUG_H
#define I2C_DEBUG_H

#include <stdbool.h>

#include "../../common/io/buffer.h"

/**
 * Returns if we must debug I2C or not.
 * @return true if the I2C debug mode is enabled, false else.
 */
bool getDebugI2cEnabled();

/**
 * Enabled or not the I2C Debug Buffer.
 * @param enabled the new value for the I2C Debug mode
 */
void setDebugI2cEnabled(bool enabled);

/**
 * Get the input buffer to debug I2C.
 * @return a pointer on the buffer used to debug the I2C (Input Part).
 */
Buffer* getDebugI2cInputBuffer();

/**
 * Get the output buffer to debug I2C.
 * @return a pointer on the buffer used to debug the I2C (Output Part).
 */
Buffer* getDebugI2cOutputBuffer();

/**
 * Init the I2C debug buffers.
 * @param aDebugI2cInputBuffer pointer on the debug buffer for I2C Input
 * @param debugI2cInputBufferArray the array of char used by the buffer to store I2C Input
 * @param debugI2cInputBufferLength the length of the array of char used by the buffer to store I2C Input
 * @param aDebugI2cOutputBuffer pointer on the debug buffer for I2C Output
 * @param debugI2cOutputBufferArray the array of char used by the buffer to store I2C Output
 * @param debugI2cOutputBufferLength the length of the array of char used by the buffer to store I2C Output
 */
void initI2CDebugBuffers(Buffer* aDebugI2cInputBuffer,
                         char (*debugI2cInputBufferArray)[],
                         unsigned char debugI2cInputBufferLength,
                         Buffer* aDebugI2cOutputBuffer,
                         char (*debugI2cOutputBufferArray)[],
                         unsigned char debugI2cOutputBufferLength
);

/**
 * Print the content of debug buffers.
 */
void printI2cDebugBuffers();

#endif
