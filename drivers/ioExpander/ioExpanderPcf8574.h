#ifndef IO_EXPANDER_PCF8574_H
#define IO_EXPANDER_PCF8574_H

/**
 * Encapsulates the PCF8574 as an IOExpander.
 */

#include "../../common/io/outputStream.h"
#include "../../common/i2c/i2cCommon.h"

#include "ioExpander.h"

/**
 * Init the PCF8574 by wrapping it into a specific Structure to handle it
 * transparently
 * @param ioExpander
 */
void initIOExpanderPCF8574(IOExpander* ioExpander, I2cBusConnection* i2cConnection);

#endif
