#ifndef I2C_COMMON_32_H
#define I2C_COMMON_32_H

#define _SUPPRESS_PLIB_WARNING
#include <plib.h>

#include "../i2cCommon.h"

/**
 * Convert a I2c Port Index into the PIC 32 equivalent
 */
I2C_MODULE getI2C_MODULE(unsigned char portIndex);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableCommonStartI2C(I2cBusConnection* i2cBusConnection);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableCommonStopI2C(I2cBusConnection* i2cBusConnection);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableCommonAckI2C(I2cBusConnection* i2cBusConnection);

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
void portableCommonNackI2C(I2cBusConnection* i2cBusConnection);


#endif
