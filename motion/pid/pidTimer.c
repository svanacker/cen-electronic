#include "pidTimer.h"

#include "../../common/timer/cenTimer.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

// TIMER

static unsigned long lastPidTime;

void initPidTimer(void) {
    addTimer(TIMER_PID_CODE, PID_BASE_DIVISER, (interruptTimerCallbackFunc*) NULL, "PID TIME", NULL);
    clearPidTime();
}

/**
 * Get the pid Timer frequency in hertz.
 */
float getPidTimerFrequencyHertz(void) {
    return PID_UPDATE_MOTORS_FREQUENCY_HERZ;
}

float getPidTimeInSecond(void) {
    Timer* timer = getTimerByCode(TIMER_PID_CODE);
    float result = (float) timer->time / (float) TIME_DIVIDER_1_HERTZ;
    return result;
}

// TIMERS

void clearPidTime(void) {
    Timer* timer = getTimerByCode(TIMER_PID_CODE);
    timer->time = 0;
    lastPidTime = 0;
}

bool mustPidBeRecomputed(void) {
    Timer* timer = getTimerByCode(TIMER_PID_CODE);
    unsigned long pidTime = timer->time;
    // Example 1 :
    // pidTime = 687, lastPidTime = 2 ==> pidTime > 624
    // lastPidTime will be : (687 / 312) + 1 = 3 (because we use integer division, and not float division)
    // We will recompute when pidTime > 3 * 312 => if pidTime > 936
    //
    // Example 2 :
    // pidTime = 465, lastPidTime = 3 ==> pidTime < 936
    //
    // Example 3 :
    // pidTime = 1723, lastPidTime = 2 => pidTIme > 624
    // lastPidTime will be 5 (we will not have at any time lastPidTime = 3 or lastPidTime = 4)
    if (pidTime > PID_UPDATE_MOTOR_TIMER_INTERVAL * lastPidTime) {
        unsigned long interval = PID_UPDATE_MOTOR_TIMER_INTERVAL;
        lastPidTime = (pidTime / interval) + 1;
        return true;
    }
    return false;
}
