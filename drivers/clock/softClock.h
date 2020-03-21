#ifndef SOFT_CLOCK_H
#define SOFT_CLOCK_H

#include "../../common/timer/cenTimer.h"

#include "../../common/clock/clock.h"


#define SOFT_CLOCK_UPDATE_TIME_DIVISER     TIME_DIVIDER_1_HERTZ

/**
 * Initializes a clock object which is updatable by soft (no RTC embedded).
 * @param clock a pointer on the clock structure.
 */
void initSoftClock(Clock* clock);

#endif

