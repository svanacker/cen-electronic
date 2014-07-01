#ifndef CLOCK_CONSTANTS_30F_H
#define CLOCK_CONSTANTS_30F_H

#include "../../../common/commons.h"

/** oscillator frequency in Hz. */
#define FOSC 		CLOCK_FREQUENCY

/** PLL multiplier, x1  x4  x8  x16. */
#define FOSC_PLL 	CLOCK_PLL

/** instruction cycle frequency. */
#define FCY ((FOSC * FOSC_PLL) / 4)

#endif
