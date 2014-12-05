#ifndef MOCK_CLOCK_H
#define MOCK_CLOCK_H

#include "../../common/clock/clock.h"

#define PCF8573P_READ_ADDRESS       PCF8573P_WRITE_ADDRESS + 1

/**
* Initializes a clock object with a mock on the PC
* @param clock a pointer on the clock structure.
*/
void initMockClock(Clock* clock);

#endif

