#include <stdbool.h>

#include "cenTimer.h"

#include "../../common/commons.h"

unsigned long getTime(Timer* timer) {
    return timer->time;
}

void setTime(Timer* timer, unsigned long value) {
    timer->time = value;
}

// STARTS / STOP

void startTimer(Timer* timer) {
    timer->enabled = true;
}

void stopTimer(Timer* timer) {
    timer->enabled = false;
}

// MARK

void markTimer(Timer* timer) {
    timer->markTime = timer->time;
}

unsigned long getTimeSinceLastMark(Timer* timer) {
    return (timer->time - timer->markTime);
}

bool timeout(Timer* timer, unsigned long timeToCheck) {
    unsigned long timeSinceLastMarkValue = getTimeSinceLastMark(timer);
    return timeToCheck > timeSinceLastMarkValue;
}

// LOCK / UNLOCK

void lockAndWaitForTimer(Timer* timer) {
    // we lock the timer to be sure that he will not be fired
    timer->lock = true;

    // we wait after the end of the timer callback
    // do be sure that variables are ok
    while (timer->working) {
        // do nothing
    }
}

void unlockTimer(Timer* timer) {
    timer->lock = false;
}
