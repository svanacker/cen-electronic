#include "delayTimer.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/error/error.h"
#include "timerList.h"
#include "timerConstants.h"

void timerDelayMilliSeconds(unsigned int delayMilliSeconds) {
    TimerList* timerList = getTimerList();
    // Avoid to be blocked
    if (!timerList->started) {
        return;
    }
    // TODO : If we use markTimer inside a timer interrupt, we will blocked by the while loop which will never exit

    // Check That the delay Timer exists and is active
    Timer* timer = getTimerByCode(SYSTEM_TIMER_DELAY_CODE);
    if (timer == NULL) {
        writeError(TIMER_DELAY_NOT_FOUND);
        return;
    }
    // If the timer is disabled, we will not be able to enter in the loop
    if (!timer->enabled) {
        writeError(TIMER_DELAY_DISABLED);
        return;
    }
    // Mark the timer so that we could know when we need to release it
    markTimer(timer);
    // The frequency is 100 Hz => We multiply by 10
    unsigned timerSinceLastMarkThreshold = delayMilliSeconds / 10;
    while(getTimeSinceLastMark(timer) <= timerSinceLastMarkThreshold) {
        // Do nothing, other interrupt will occur
    }
}

/**
 * The interrupt timer.
 */
void interruptSystemDelayCallbackFunc(Timer* timer) {
    // NOTHING TO DO
}

bool initSystemDelayTimer(void) {
    TimerList* timerList = getTimerList();
    if (timerList == NULL) {
        writeError(TIMERS_LIST_NULL);
        return false;
    }
    if (getTimerByCode(SYSTEM_TIMER_DELAY_CODE) != NULL) {
        writeError(TIMER_DELAY_ALREADY_INITIALIZED);
        return false;
    }
    // Init the system timer for delay
    // and add the timer to the list, so that the interrupt function will
    // update at a certain frequency
    Timer* timer = addTimer(SYSTEM_TIMER_DELAY_CODE,
                            TIME_DIVIDER_100_HERTZ,
                            &interruptSystemDelayCallbackFunc,
                            "TIMER DELAY", 
							NULL);
    timer->enabled = true;
    return true;
}