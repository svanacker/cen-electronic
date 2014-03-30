#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include "../../../common/io/streamLink.h"

void enabledI2CInterrupt();

/**
 * Store the stream Link for i2c interrupt.
 */
void setI2cStreamLink(StreamLink* astreamLink);

/**
 * Returns the stream link.
 */
StreamLink* getI2cStreamLink();


#endif

