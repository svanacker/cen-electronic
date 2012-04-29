#ifndef I2C_DEBUG_H
#define I2C_DEBUG_H

#include "../../common/io/buffer.h"

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
void initI2CDebugBuffers(Buffer* aDebugI2cInputBuffer, Buffer* aDebugI2cOutputBuffer);

/**
 * Print the content of debug buffers;
 */
void printI2cDebugBuffers();

#endif
