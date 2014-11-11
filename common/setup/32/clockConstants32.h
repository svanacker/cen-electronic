#ifndef CLOCK_CONSTANTS_32_H
#define CLOCK_CONSTANTS_32_H

#include "../../../common/commons.h"

#define QUARTZ_FREQUENCY    8000000L
#define CLOCK_PLL           20
#define FOSC                (QUARTZ_FREQUENCY * CLOCK_PLL / 2)

// Compute Bus Frequency
#define    GetSystemClock()         (FOSC)
#define    GetPeripheralClock()     (GetSystemClock() /(1 << OSCCONbits.PBDIV))
#define    GetInstructionClock()    (GetSystemClock())

#endif
