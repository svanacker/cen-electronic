#ifndef I2C_COMMON_H
#define I2C_COMMON_H

#include "../../common/io/buffer.h"

#define NACK    0

/**
 * Indirection for IdleI2C() used to manage Simulation
 */
void WaitI2C();

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
inline void portableStartI2C();

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
inline void portableStopI2C();

/**
 * Indirection for I2C used to manage 30F/32 compatibility.
 */
inline void portableAckI2C();

#endif

