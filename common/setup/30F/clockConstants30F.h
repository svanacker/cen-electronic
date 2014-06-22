#ifndef CLOCK_CONSTANTS_30F_H
#define CLOCK_CONSTANTS_30F_H

/** oscillator frequency in Hz. */
#define FOSC 7372800

/** PLL multiplier, x1  x4  x8  x16. */
#define FOSC_PLL 16

/** instruction cycle frequency. */
#define FCY ((FOSC * FOSC_PLL) / 4)

#endif
