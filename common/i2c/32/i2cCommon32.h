#ifndef I2C_COMMON_32_H
#define I2C_COMMON_32_H

#include <plib.h>

/**
 * Convert a I2c Port Index into the PIC 32 equivalent
 */
I2C_MODULE getI2C_MODULE(unsigned char portIndex);

#endif
