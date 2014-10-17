#ifndef CLOCK_H
#define	CLOCK_H

/**
 * Universal clock definition.
 */
typedef struct {
    int year;
    int month;
    int dayofweek;
    int day;
    int hour;
    int minute;
    int second;
} Clock;

/**
 * Returns the singleton for Clock.
 * @returns the singleton for Clock.
 */
Clock* getGlobalClock();

/**
 * Update the specific clock hardware with value from the struct.
 * @param clock the pointer on clock object
 */
void updateClockToHardware(Clock* clock);

/**
 * Update the software clock structure from the hardware.
 * @param clock the pointer on clock object.
 */
void updateClockFromHardware(Clock* clock);

#endif
