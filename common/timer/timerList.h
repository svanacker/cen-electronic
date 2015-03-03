#ifndef TIMERLIST_H
#define TIMERLIST_H

#include "cenTimer.h"

/**
 * The struct defining a list of timer.
 */
typedef struct {
    /** An array of pointer on timer pointer. */
    Timer (*timers)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list.*/
    unsigned char maxSize;
} TimerList;

// INTERFACES

/**
 * Initialize the timer list.
 * @param timerListArray on pointer on a array of timer
 * @param timerListSize the size of the timerListArray param.
 */
void initTimerList(Timer (*timerListArray)[], unsigned char timerListSize);

/**
 * Creates a timer and adds it to list with a frequency given by timeDiviser.
 * @param timerCode a unique code used to identify timer
 * @param timerDiviser Ex : if timeDiviser = 100, time frequency is 100 times slower than the main interruption
 * @param callback the function which must be used by the interruption
 * @param timerName the name of the timer
 * @return the  a pointer on the timer Struct (POO simulation)
 */
Timer* addTimer(int timerCode,
                unsigned long timeDiviser,
                interruptTimerCallbackFunc* callback,
                char* timerName);

/**
 * Get the device descriptor of index.
 * @param index the index of the timer (0..n)
 * @return a pointer on the found timer (POO simulation).
 */
Timer* getTimerByIndex(int index);

/**
 * Get a timer by his code.
 * @param timerCode the code of the timer that we search.
 * @return a pointer on the found timer (POO simulation).
 */
Timer* getTimerByCode(int timerCode);

/**
 * Get the count of timer.
 * @return timer count.
 */
int getTimerCount();

/**
 * Starts the timer to handle software interruption.
 * startTimerList() must be called when all registerInterrupt call are done.
 */
void startTimerList();

/**
 * Returns the unique Timer List (singleton).
 * @return a pointer on TimerList struct.
 */
TimerList* getTimerList();

/**
 * TODO : See to remove it
 */
void _internalUpdateTimerListValues(int incrementSinceLastCall);

#endif

