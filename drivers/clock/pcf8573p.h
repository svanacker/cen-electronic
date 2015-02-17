#ifndef PCF8573P_H
#define PCF8573P_H

#include "../../common/clock/clock.h"

#include "../../common/i2c/i2cCommon.h"

#define PCF8573P_READ_ADDRESS       PCF8573P_WRITE_ADDRESS + 1

/**
 * Initializes a clock object with a PCF8573 hardware component.
 * @param clock a pointer on the clock structure.
 */
void initClockPCF8573(Clock* clock, I2cBus* i2cBus);

#endif