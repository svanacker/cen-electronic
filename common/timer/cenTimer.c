#include <stdbool.h>
#include <stdlib.h>

#include "cenTimer.h"

#include "../../common/commons.h"
#include "../../common/error/error.h"

float timeDiviserToFrequencyInHertz(float timeDiviser) {
    return TIME_DIVIDER_1_HERTZ / timeDiviser;
}

unsigned long getTime(Timer* timer) {
    return timer->time;
}

void setTime(Timer* timer, unsigned long value) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return;
    }
    timer->time = value;
}

// STARTS / STOP

void startTimer(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return;
    }
    timer->enabled = true;
}

void stopTimer(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return;
    }
    timer->enabled = false;
}

// MARK

unsigned long markTimer(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return 0L;
    }
    if (!timer->enabled) {
        writeError(TIMER_MARK_WHEREAS_DISABLED);
        return 0L;
    }
    timer->markTime = timer->time;
    return timer->markTime;
}

unsigned long getTimeSinceLastMark(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return 0L;
    }
    return (timer->time - timer->markTime);
}

bool timeout(Timer* timer, unsigned long timeToCheck) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return false;
    }
    unsigned long timeSinceLastMarkValue = getTimeSinceLastMark(timer);
    return timeSinceLastMarkValue > timeToCheck;
}

// LOCK / UNLOCK

void lockAndWaitForTimer(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return;
    }
    // we lock the timer to be sure that he will not be fired
    timer->lock = true;

    // we wait after the end of the timer callback
    // do be sure that variables are ok
    while (timer->working) {
        // do nothing
    }
}

void lockTimer(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return;
    }
    timer->lock = true;
}

void unlockTimer(Timer* timer) {
    if (timer == NULL) {
        writeError(TIMER_NULL);
        return;
    }
    timer->lock = false;
}
