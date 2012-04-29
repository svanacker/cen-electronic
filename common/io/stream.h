#ifndef STREAM_H
#define STREAM_H

#include "outputStream.h"

#include "../../common/commons.h"

/**
 * Data will not be transfered, because the driver does not correspond to our communication standard
 * (Ex : For All Devantech Devices)
 */
#define TRANSMIT_NONE 	-1

/**
 * Data will be transmitted in local.
 */
#define TRANSMIT_LOCAL 	0

/**
 * Data will be transmitted via I2C.
 */
#define TRANSMIT_I2C 	1

/**
 * Data will be transmitted via UART.
 */
#define TRANSMIT_UART 	2

/**
 * Data will be transmitted via ZIGBEE.
 */
#define TRANSMIT_ZIGBEE 3

/**
 * Init an outputStream which redirect all to NULL (like dev/null in UNIX)
 * It allows compatibility with copy Function, as we can give it an outputStream
 * (because data is read but trashed to NULL)
 */
void initNullOutputStream(OutputStream* outputStream);

#endif
