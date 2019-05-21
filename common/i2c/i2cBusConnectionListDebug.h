#ifndef I2C_CONNECTION_LIST_DEBUG_H
#define I2C_CONNECTION_LIST_DEBUG_H

#include <stdbool.h>

#include "../../common/io/buffer.h"

/**
* Print the list of I2cBusConnection.
*/
void printI2cBusConnectionList(OutputStream* outputStream);

#endif
