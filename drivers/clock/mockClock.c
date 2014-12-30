#include "mockClock.h"

#include <stdlib.h>
#include <time.h>

#include "../../common/clock/clock.h"

/**
* @see clock.h
* @private
* Mock a clock on the PC 
* @param clockParam the clock
*/
ClockData* _readMockClock(Clock* clockParam) {
    time_t rawtime;
    struct tm timeinfo;
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);

    ClockData* data = &(clockParam->clockData);
    data->year = timeinfo.tm_year - 100; // we store the date after 2000 (100 = 2000 - 1900)
    data->month = timeinfo.tm_mon;
    data->day = timeinfo.tm_mday;
    data->dayofweek = timeinfo.tm_wday;
    data->hour = timeinfo.tm_hour;
    data->minute = timeinfo.tm_min;
    data->second = timeinfo.tm_sec;

    return &(clockParam->clockData);
}

/**
 * @see clock.h
 * @private 
 * Set the Clock into the Mock
 * @param clockParam the new value of clock
 */
void _writeMockClock(Clock* clockParam) {
    // We don't want to write the clock Data !
}

void initMockClock(Clock* clockParam) {
    initClock(clockParam, _writeMockClock, _readMockClock);
}