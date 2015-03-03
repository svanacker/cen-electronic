#ifndef SOFT_CLOCK_H
#define SOFT_CLOCK_H

#include "../../common/clock/clock.h"

/**
* Initializes a clock object which is updatable by soft (no RTC embedded).
* @param clock a pointer on the clock structure.
*/
void initSoftClock(Clock* clock);

#endif

