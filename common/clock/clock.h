#ifndef CLOCK_H
#define CLOCK_H

#include <stdbool.h>

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
typedef void WriteClockFunction(Clock* clockParam);

/**
 * Update the software clock structure from the hardware.
 * @param clockParam the pointer on clock object.
 * @return the pointer on ClockData with refresh data (from hardware)
 */
typedef ClockData* ReadClockFunction(Clock* clockParam);

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
    /** A pointer on generic object (for example to store I2cBus, timer ...). */
    int* object;
};

/**
 * Returns true if the clock is initialized (if the fields of callbacks are NOT NULL), false else.
 * @param clock a pointer on the Clock object (Simulates POO programming) 
 * @return true if the clock is initialized (if the fields of callbacks are NOT NULL), false else.
 */
bool isClockInitialized(Clock* clock);

/**
 * Initializes (Constructor in POO).
 * @param clockParam a pointer on clock structure to initialize it.
 * @param writeClockFunction a pointer on the writeClockFunction
 * @param readClockFunction a pointer on the readClockFunction
 * @param object A pointer on generic object (for example to store I2cBus ...).
 */
void initClock(Clock* clockParam, WriteClockFunction* writeClockFunction, ReadClockFunction* readClockFunction, int* object);

#endif
