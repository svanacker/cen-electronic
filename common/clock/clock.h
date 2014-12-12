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
} ClockData;

// forward declaration
struct Clock;
typedef struct Clock Clock;

/**
 * Update the specific clock hardware with value from the struct.
 * @param clockParam the pointer on clock object
 */
typedef void WriteClockFunction(Clock* clock);

/**
 * Update the software clock structure from the hardware.
 * @param clockParam the pointer on clock object.
 * @return the pointer on ClockData with refresh data (from hardware)
 */
typedef ClockData* ReadClockFunction(Clock* clock);

/**
 * Defines the contract for a clock object.
 */
struct Clock {
    /** The function which must be used to write the content of data to the hardware. */
    WriteClockFunction* writeClock;
    /** The function which must be used to read the content in the hardware to store in the clockData */
    ReadClockFunction* readClock;
    /** The content with all values. */
    ClockData clockData;
};

/**
 * Initializes (Constructor in POO).
 * @param clockParam a pointer on clock structure to initialize it.
 * @param writeClockFunction a pointer on the writeClockFunction
 * @param readClockFunction a pointer on the readClockFunction
 */
void initClock(Clock* clock, WriteClockFunction* writeClockFunction, ReadClockFunction* readClockFunction);

#endif
