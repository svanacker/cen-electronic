#include <stdlib.h>
#include <stdbool.h>

#include "../../common/commons.h"
#include "../../common/error/error.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "timerList.h"
#include "cenTimer.h"
#include "timerSetup.h"

// We use singleton pattern
static TimerList timerList;

TimerList* getTimerList() {
    return &timerList;
}

void initTimerList(Timer (*timerListArray)[], unsigned char timerListSize) {
    timerList.timers = timerListArray;
    timerList.maxSize = timerListSize;
}

Timer* addTimer(int timerCode,
                unsigned long timeDiviser,
                interruptTimerCallbackFunc* callback,
                char* timerName) {
    if (timerList.maxSize == 0) {
        writeError(TIMERS_LIST_NOT_INITIALIZED);
        return NULL;
    }
    unsigned char size = timerList.size;

    if (size < timerList.maxSize) {
		Timer* result = getTimerByIndex(size);
		if (result == NULL) {
			writeError(TIMER_NULL);
			return;
		}
        result->time = 0;
        result->markTime = 0;
        result->timerCode = timerCode;
        result->timeDiviser = timeDiviser;
        result->callback = callback;
        result->enabled = false;
        result->lock = false;
        result->working = false;
        result->name = timerName;

        timerList.size++;
        return result;
    }
    else {
        writeError(TOO_MUCH_TIMERS);
        return NULL;
    }
}

Timer* getTimerByIndex(int index) {
	if (timerList.maxSize == 0) {
		writeError(TIMERS_LIST_NOT_INITIALIZED);
		return NULL;
	}
	if (index < 0 || index >= timerList.maxSize) {
		writeError(TIMERS_LIST_ILLEGAL_INDEX);
		return NULL;
	}

    Timer* result = (Timer*) timerList.timers;
    result += index;
    return result;
}

Timer* getTimerByCode(int timerCode) {
    int i;
    for (i = 0; i < timerList.size; i++) {
        Timer* timer = getTimerByIndex(i);
		if (timer == NULL) {
			writeError(TIMER_NULL);
			return;
		}
        if (timer->timerCode == timerCode) {
            return timer;
        }
    }
    return NULL;
}

int getTimerCount() {
    return timerList.size;
}

void startTimerList() {
    _initTimers();
    int i;
    for (i = 0; i < timerList.size; i++) {
        Timer* timer = getTimerByIndex(i);
		if (timer == NULL) {
			writeError(TIMER_NULL);
			return;
		}
        startTimer(timer);
    }
}

void stopTimerList() {
    int i;
    for (i = 0; i < timerList.size; i++) {
        Timer* timer = getTimerByIndex(i);
		if (timer == NULL) {
			writeError(TIMER_NULL);
			return;
		}
        stopTimer(timer);
    }
}

/**
* @private 
*/
void _internalUpdateTimerListValues(int incrementSinceLastCall) {
    if (timerList.size > 0) {
        int i = 0;
        for (i = 0; i < timerList.size; i++) {
            Timer* currentTimer = getTimerByIndex(i);
			if (currentTimer == NULL) {
				writeError(TIMER_NULL);
				return;
			}
            bool enabled = currentTimer->enabled;
            if (!enabled) {
                continue;
            }
            // increments the counter and test if it is > to the timeDiviser
            currentTimer->timeInternalCounter += incrementSinceLastCall;
            if (currentTimer->timeInternalCounter >= currentTimer->timeDiviser) {
                // block the timer if we wait for
                bool lock = currentTimer->lock;
                if (lock) {
                    continue;
                }

                // we only subtract and not clear to 0, so that, if the timer is locked, we will not forget
                // any firing
                currentTimer->timeInternalCounter -= currentTimer->timeDiviser;
                currentTimer->time++;

                // lock the timer to avoid concurrence problem
                currentTimer->working = true;
                if (currentTimer->callback) {
                    currentTimer->callback(currentTimer);
                }
                // indicates the timer is not working
                currentTimer->working = false;
            }
        }
    }
}
