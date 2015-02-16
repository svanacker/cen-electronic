#ifndef PCF8563_H
#define PCF8563_H

#include "../../common/i2c/i2cConstants.h"
#include "../../common/i2c/i2cCommon.h"

#include "../../common/io/outputStream.h"

#include "../../common/clock/clock.h"

#define PCF8563_READ_ADDRESS            PCF8563_WRITE_ADDRESS + 1

#define PCF8563_CLOCK_REGISTER          0x02

/**
 * Initializes a clock object with a PCF8563 hardware component.
 * @param clock a pointer on the clock structure.
 */
void initClockPCF8563(Clock* clock, I2cBus* i2cBus);

#endif