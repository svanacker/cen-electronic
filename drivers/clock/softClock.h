#ifndef SOFT_CLOCK_H
#define SOFT_CLOCK_H

#include "../../common/clock/clock.h"

#define TIMER_SOFT_CLOCK_CODE           96
#define SOFT_CLOCK_UPDATE_FREQUENCY     28800

/**
* Initializes a clock object which is updatable by soft (no RTC embedded).
* @param clock a pointer on the clock structure.
*/
void initSoftClock(Clock* clock);

#endif

