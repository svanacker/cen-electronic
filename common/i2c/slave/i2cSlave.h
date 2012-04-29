#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include "../../../common/io/streamLink.h"

void enabledI2CInterrupt();

/**
 * Store the stream Link for i2c interrupt.
 */
void setI2cStreamLink(StreamLink* astreamLink);

/**
 * Init the debug buffers for I2C.
 */
void initI2CDebugBuffers(Buffer* aDebugI2cInputBuffer,
        Buffer* aDebugI2cOutputBuffer);

/*
 * Print the content of the I2C debug buffers.
 */
void printI2cDebugBuffers();

#endif

