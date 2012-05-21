#ifndef CEN_TIMER_H
#define CEN_TIMER_H

#include "../../common/commons.h"
#include "../../common/io/outputStream.h"


/**
 * Define the timer diviser to have a timer at 1 Hertz (every second).
 */
#define TIME_DIVISER_1_HERTZ 				28800

/**
 * Define the timer diviser to have a timer at 2 Hertz
 */
#define TIME_DIVISER_2_HERTZ 				TIME_DIVISER_1_HERTZ / 2

/**
 * Define the timer diviser to have a timer at 10 Hertz
 */
#define TIME_DIVISER_10_HERTZ 				TIME_DIVISER_1_HERTZ / 10

/**
 * Define the timer diviser to have a timer at 16 Hertz
 */
#define TIME_DIVISER_16_HERTZ 				TIME_DIVISER_1_HERTZ / 16


#define TIME_DIVISER_30_HERTZ 				TIME_DIVISER_1_HERTZ / 30

#define TIME_DIVISER_50_HERTZ 				TIME_DIVISER_1_HERTZ / 50

/**
 * Define the timer diviser to have a timer at 100 Hertz.
 */
#define TIME_DIVISER_100_HERTZ 				TIME_DIVISER_1_HERTZ / 100

/**
 * Define the timer diviser to have a timer at 1000 Hertz (every millisecond).
 * This is approximative because division is not exact.
 */
#define TIME_DIVISER_1000_HERTZ TIME_DIVISER_1_HERTZ / 1000

/**
 * Define the timer diviser to have a timer at 2000 Hertz
 * This is approximative because division is not exact.
 */
#define TIME_DIVISER_2000_HERTZ TIME_DIVISER_1_HERTZ / 2000

/**
 * Define the timer diviser to have a timer at 10000 Hertz.
 * This is approximative because division is not exact.
 */
#define TIME_DIVISER_10000_HERTZ 3

/**
 * Definition of a function for callBack of timer.
 */
typedef void interruptTimerCallbackFunc(void);

/**
 * The structure used to manage several Timers.
 */
typedef struct {
    /** The code of the timer (unique in all applications), not necessary equal to index in a timer List . */
    unsigned char timerCode;
    /** The diviser timer. */
    unsigned long timeDiviser;
    /** The internal counter to divise the timer. */
    unsigned long timeInternalCounter;
    /** The value of the timer. */
    unsigned long time;
	/** The value of the mark. */
	unsigned long markTime;
    /** The function which must be used. */
    interruptTimerCallbackFunc* callback;
    /** if the timer is enabled or not. */
    BOOL enabled;
    /** if the timer is locked or not. */
    volatile BOOL lock;
    /** if the timer is in the callback function and is working. */
    volatile BOOL working;
} Timer;

/**
 * Returns the time value.
 */
unsigned long getTime(Timer* Timer);

/**
 * Sets the time value.
 * @param time the new time value
 */
void setTime(Timer* Timer, unsigned long time);

// START - STOP

/**
 * Starts the timer given in argument.
 */
void startTimer(Timer* timer);

/**
 * Stops the timer given in arguments.
 */
void stopTimer(Timer* timer);

// MARK

/**
 * Mark the timer. Remembers the current timer value.
 */
void mark(Timer* timer);

/**
 * Check if the last mark was done after markTime + time.
 * return TRUE if (markTime + time > timer->time)
 */
BOOL timeout(Timer* timer, unsigned long time);

// LOCK

/**
 * Lock the timer to avoid that the timer fires.
 */
void lockTimer(Timer* timer);

/**
 * wait for the timer to be sure that interrupt is not in progress, and lock
 * to be sure that until unlockTimer, timer will not be enabled.
 */
void lockAndWaitForTimer(Timer* timer);

/**
 * unlock the timer. If the timer is enabled, the timer will be fired next time.
 */
void unlockTimer(Timer* timer);

#endif


