#include "pidTimer.h"

#include <stdlib.h>
#include <stdbool.h>

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/timer/cenTimer.h"
#include "../../common/timer/timerList.h"

// TIMER

static float lastPidTimeInSecond;

void initPidTimer(void) {
    addTimer(TIMER_PID_CODE, PID_UPDATE_MOTORS_TIME_DIVISER, (interruptTimerCallbackFunc*) NULL, "PID TIME", NULL);
    clearPidTime();
}

/**
* Get the pid Timer frequency in hertz.
*/
float getPidTimerFrequencyHertz(void) {
    return PID_UPDATE_MOTORS_FREQUENCY_HERTZ;
}

float getPidTimeInSecond(void) {
    Timer* timer = getTimerByCode(TIMER_PID_CODE);
    float result = (float) timer->time / PID_UPDATE_MOTORS_FREQUENCY_HERTZ;
    return result;
}

// TIMERS

void clearPidTime(void) {
    Timer* timer = getTimerByCode(TIMER_PID_CODE);
    timer->time = 0;
    lastPidTimeInSecond = 0;
}

bool mustPidBeRecomputed(void) {
    float pidTimeInSecond = getPidTimeInSecond();
    if (pidTimeInSecond > lastPidTimeInSecond) {
        lastPidTimeInSecond = pidTimeInSecond;
        return true;
    }
    return false;
}
