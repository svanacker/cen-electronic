#ifndef CLOCK_CONSTANTS_32_H
#define CLOCK_CONSTANTS_32_H

/** oscillator frequency in Hz. */
#define FOSC 80000000L

/** PLL multiplier, x1  x4  x8  x16, x20. */
#define FPLLMUL 20

/** PLL diviser */
#define FPLLIDIV 2

/** instruction cycle frequency. */
#define FCY ((FOSC * FPLLMUL) / FPLLIDIV  / 4)

// Compute Bus Frequency
#define    GetSystemClock()         (FOSC)
#define    GetPeripheralClock()     (GetSystemClock() /(1 << OSCCONbits.PBDIV))
#define    GetInstructionClock()    (GetSystemClock())

#endif
