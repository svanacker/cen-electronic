#ifndef CEN_DELAY_H
#define CEN_DELAY_H

/**
 * Sleeps during 1 micro second.
 */
void delayUs(void);

/**
 * Sleeps during a multiple of 10 micro seconds.
 * @param value the value to sleep
 */
void delay10us(unsigned char value);

/**
 * Sleeps during a multiple of 100 micro seconds.
 * @param value the value to sleep
 */
void delay100us(unsigned char value);

/**
 * Sleeps during a multiple of one milli second.
 * @param msecond number of milli seconds to sleep
 */
void delaymSec(unsigned int msecond);

#endif
