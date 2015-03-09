#include "softClock.h"

#include <stdlib.h>

#include "../../common/clock/clock.h"

/**
* @see clock.h
* @private
* @param clockParam the clock
*/
ClockData* _readSoftClock(Clock* clockParam) {
    return &(clockParam->clockData);
}

void incrementOneSecondSoftClock(ClockData* clockData) {
    clockData->second++;
    if (clockData->second >= 60) {
        clockData->second -= 60;
        clockData->minute++;
        if (clockData->minute >= 60) {
            clockData->minute -= 60;
            clockData->hour++;
            if (clockData->hour >= 24) {
                clockData->hour -= 24;
                clockData->day++;
                // DOES NOT MANAGE THE CHANGE OF MORE THAN ONE DAY, the robot is not ON enough
            }
        }
    }
}

/**
 * @see clock.h
 * @private 
 * Set the software Clock 
 * @param clockParam the new value of clock
 */
void _writeSoftClock(Clock* clockParam) {
    // Data is in Memory, the data is modified by a call to field member
}

void initSoftClock(Clock* clockParam) {
    initClock(clockParam, _writeSoftClock, _readSoftClock, NULL);
}