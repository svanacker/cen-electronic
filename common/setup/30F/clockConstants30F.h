#ifndef CLOCK_CONSTANTS_30F_H
#define CLOCK_CONSTANTS_30F_H

#include "../../../common/commons.h"

// COMMON SYMBOLS

#define QUARTZ_FREQUENCY    7372800L
#define CLOCK_PLL           16
#define CLOCK_FREQUENCY     QUARTZ_FREQUENCY * CLOCK_PLL
#define CYCLE_FREQUENCY     (QUARTZ_FREQUENCY * CLOCK_PLL / 4)

// REQUIRED SYMBOLS

/** oscillator frequency in Hz. */
#define FOSC         QUARTZ_FREQUENCY

/** PLL multiplier, x1  x4  x8  x16. */
#define FOSC_PLL     CLOCK_PLL

/** instruction cycle frequency. */
#define FCY         CYCLE_FREQUENCY

#endif
