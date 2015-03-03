#ifndef REMOTE_CLOCK_H
#define REMOTE_CLOCK_H

#include <stdbool.h>

#include "../../common/clock/clock.h"

bool getRemoteClockData(ClockData* clockData);

bool writeHourRemoteClockData(ClockData* clockData, int dispatcherIndex);

bool writeDateRemoteClockData(ClockData* clockData, int dispatcherIndex);

#endif
