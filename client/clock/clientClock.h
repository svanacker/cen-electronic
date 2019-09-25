#ifndef CLIENT_CLOCK_H
#define CLIENT_CLOCK_H

#include <stdbool.h>

#include "../../common/clock/clock.h"

bool clientClockGetClockData(ClockData* clockData);

bool clientClockWriteHourClockData(ClockData* clockData, int dispatcherIndex);

bool clientClockWriteDateClockData(ClockData* clockData, int dispatcherIndex);

#endif
