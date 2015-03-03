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