#ifndef TIMERLIST_H
#define TIMERLIST_H

#include "cenTimer.h"

/** The max limit of timer list. */
#define MAX_TIMER 5

/**
 * Tre struct defining a list of timer
 */
typedef struct {
    /** An array of pointer on device Descriptor. */
    Timer * timers[MAX_TIMER];
    /** the size of the list. */
    unsigned char size;
} TimerList;

/**
 * Add a timer to the list.
 * @param timer the timer struct to add
 */
void addTimer(Timer* timer);

/**
 * Get the device descriptor of index + 1;
 */
Timer* getTimerByIndex(int index);

/**
 * Get a timer by his code.
 * @param timerCode the code of the timer that we search.
 */
Timer* getTimerByCode(int timerCode);

/**
 * Get the count of timer.
 */
int getTimerCount();

/**
 * Starts the timer to handle software interruption.
 * startTimerList() must be called when all registerInterrupt call are done.
 */
void startTimerList();


#endif

