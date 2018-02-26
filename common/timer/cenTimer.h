#ifndef CEN_TIMER_H
#define CEN_TIMER_H

#include <stdbool.h>

/**
 * Define the timer divider to have a timer at 1 Hertz (every second).
 */
#define TIME_DIVIDER_1_HERTZ                 31250

/**
 * Define the timer divider to have a timer at 2 Hertz.
 */
#define TIME_DIVIDER_2_HERTZ                 TIME_DIVIDER_1_HERTZ / 2

/**
 * Define the timer divider to have a timer at 10 Hertz.
 */
#define TIME_DIVIDER_10_HERTZ                 TIME_DIVIDER_1_HERTZ / 10

/**
 * Define the timer divider to have a timer at 16 Hertz.
 */
#define TIME_DIVIDER_16_HERTZ                 TIME_DIVIDER_1_HERTZ / 16

/**
 * Define the timer divider to have a timer at 30 Hertz.
 */
#define TIME_DIVIDER_30_HERTZ                 TIME_DIVIDER_1_HERTZ / 30

/**
 * Define the timer divider to have a timer at 50 Hertz.
 */
#define TIME_DIVIDER_50_HERTZ                 TIME_DIVIDER_1_HERTZ / 50

/**
 * Define the timer divider to have a timer at 100 Hertz.
 */
#define TIME_DIVIDER_100_HERTZ                 TIME_DIVIDER_1_HERTZ / 100

/**
 * Define the timer divider to have a timer at 1000 Hertz (every millisecond).
 * This is approximative because division is not exact.
 */
#define TIME_DIVIDER_1000_HERTZ TIME_DIVIDER_1_HERTZ / 1000

/**
 * Define the timer divider to have a timer at 2000 Hertz
 * This is approximative because division is not exact.
 */
#define TIME_DIVIDER_2000_HERTZ TIME_DIVIDER_1_HERTZ / 2000

/**
 * Define the timer divider to have a timer at 10000 Hertz.
 * This is approximative because division is not exact.
 */
#define TIME_DIVIDER_10000_HERTZ 3

// forward declaration
struct Timer;
typedef struct Timer Timer;

/**
 * Definition of a function for callBack of timer.
 * @param timer the pointer on timer object (POO simulation)
 */
typedef void interruptTimerCallbackFunc(Timer* timer);

/**
 * The structure used to manage several Timers.
 */
struct Timer {
    /** The code of the timer (unique in all applications), not necessary equal to index in a timer List . */
    unsigned char timerCode;
    /** The divider timer. */
    unsigned long timeDiviser;
    /** The internal counter to divide the timer. */
    unsigned long timeInternalCounter;
    /** The value of the timer. */
    unsigned long time;
    /** The value of the mark. */
    unsigned long markTime;
    /** The function which must be used. */
    interruptTimerCallbackFunc* callback;
    /** if the timer is enabled or not. */
    bool enabled;
    /** if the timer is locked or not. */
    volatile bool lock;
    /** if the timer is in the callback function and is working. */
    volatile bool working;
    /** name of the timer (to have a better way to debug) */
    char* name;
    /** A generic object so that we could something external to the timer when firing timer. */
    int* object;
};

/**
 * Returns the time value.
 * @param timer a pointer on the timer object for which we want the time value (POO simulation).
 * @return the time value.
 */
unsigned long getTime(Timer* Timer);

/**
 * Sets the time value.
 * @param timer a pointer on the timer object for which we want the set timer  (POO simulation).
 * @param time the new time value
 */
void setTime(Timer* Timer, unsigned long time);

// START - STOP

/**
 * Starts the timer given in argument.
 * @param timer a pointer on the timer object that we want to start  (POO simulation).
 */
void startTimer(Timer* timer);

/**
 * Stops the timer given in arguments.
 * @param timer a pointer on the timer object that we want to stop  (POO simulation).
 */
void stopTimer(Timer* timer);

// MARK

/**
 * Mark the timer. Remembers the current timer value  (POO simulation).
 * @return the markTime
 */
unsigned long markTimer(Timer* timer);

/**
 * Get the time difference since the last mark.
 * @param timer the pointer on timer object (POO simulation)
 */
unsigned long getTimeSinceLastMark(Timer* timer);

/**
 * Check if the last mark was done after markTime + time.
 * @param timer the pointer on timer object (POO simulation)
 * @param timeToCheck the time to compare if we are in timeout or not 
 * return true if (markTime + time > timer->time)
 */
bool timeout(Timer* timer, unsigned long timeToCheck);

// LOCK

/**
 * Lock the timer to avoid that the timer fires.
 * @param timer a pointer on the timer object that we want to lock (POO simulation).
 */
void lockTimer(Timer* timer);

/**
 * wait for the timer to be sure that interrupt is not in progress, and lock
 * to be sure that until unlockTimer, timer will not be enabled.
 * @param timer a pointer on timer object to lock and wait (POO simulation).
 */
void lockAndWaitForTimer(Timer* timer);

/**
 * unlock the timer. If the timer is enabled, the timer will be fired next time.
 * @param timer a pointer on timer object to unlock (POO simulation).
 */
void unlockTimer(Timer* timer);

#endif


