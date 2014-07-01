#ifndef CLOCK_CONSTANTS_32_H
#define CLOCK_CONSTANTS_32_H

#include "../../../common/commons.h"

// Compute Bus Frequency
#define    GetSystemClock()         (FOSC)
#define    GetPeripheralClock()     (GetSystemClock() /(1 << OSCCONbits.PBDIV))
#define    GetInstructionClock()    (GetSystemClock())

#endif
