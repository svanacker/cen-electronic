#ifndef PCF8573P_H
#define PCF8573P_H

#include "../../common/i2c/i2cConstants.h"
#include "../../common/io/outputStream.h"

#define PCF8573P_READ_ADDRESS       PCF8573P_WRITE_ADDRESS + 1

/**
 * Define the structure used to store the clock of a pcf8573.
 */
typedef struct {
    int sec;
    int min;
    int hour;
    int day;
    int month;
    int year;
} Pcf8573Clock;


/**
 * Read the hour and the date from the Pcf8573, and store in the structure.
 * @param clock the clock
 */
void getPcf8573Clock(Pcf8573Clock* clock);

/**
 * Set the Clock into the Pcf8573.
 * @param clock the new value of clock
 */
void setPcf8573Clock(Pcf8573Clock* clock);

/**
 * Write the hour and the date to the device from the clock structure given in parameters.
 * @param outputStream the stream in which we want to write the content of the clock
 * @param clock the clock value
 */
void writePcf8573ClockToOutputStream(OutputStream* outputStream, Pcf8573Clock* clock);

#endif
