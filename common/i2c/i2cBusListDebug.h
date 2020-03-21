#ifndef I2C_BUS_LIST_DEBUG_H
#define I2C_BUS_LIST_DEBUG_H

#include <stdbool.h>

#include "../../common/io/buffer.h"

// LIST DEBUG

/**
 * Print the list of I2cBus.
 */
void printI2cBusList(OutputStream* outputStream);

#endif
