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
    Timer (*timers)[];
    /** the size of the list. */
    unsigned char size;
	/** the max size of the list.*/
	unsigned char maxSize;
} TimerList;

/**
 * Initialize the timer list.
 */
void initTimerList(Timer (*timerListArray)[], unsigned char timerListSize);

/**
 * Creates a timer and add it to list with a frequency gived by timeDiviser.
 * @param timer a pointer on the timer Struct
 * @param timerCode a unique code used to identify timer
 * @param timerDiviser Ex : if timeDiviser = 100, time2 frequency is 100 times slower than the main interruption
 * @param callback the function which must be used by the interruption
 */
Timer* addTimer(int timerCode,
        		unsigned long timeDiviser,
        		interruptTimerCallbackFunc* callback);

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

TimerList* getTimerList();

#endif

