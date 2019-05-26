#ifndef CEN_DELAY_H
#define CEN_DELAY_H

/**
 * Sleeps for x microSeconds.
 */
void delayMicroSecs(unsigned int microSeconds);

/**
 * Sleeps during a multiple of one milli second.
 * @param msecond number of milli seconds to sleep
 */
void delayMilliSecs(unsigned int msecond);

#endif
