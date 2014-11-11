#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include "../../../common/io/streamLink.h"

/**
 * Store the stream Link for i2c interrupt.
 * @param aStreamLink the pointer on the streamLink which manage input and input on I2C link.
 */
void setI2cStreamLink(StreamLink* aStreamLink);

/**
 * Returns the stream link.
 * @return the stream link
 */
StreamLink* getI2cStreamLink();

#endif

