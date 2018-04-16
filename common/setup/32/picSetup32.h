#ifndef PIC_32F_SETUP_H
#define PIC_32F_SETUP_H

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <plib.h>

// Oscillator Selection Bit
#pragma config FNOSC = PRIPLL
// Primary Oscillator Configuration
#pragma config POSCMOD = XT

//// Frequency ////

// -> Multiplication factor
#pragma config FPLLMUL  = MUL_20
// -> PLL Input Divider
#pragma config FPLLIDIV = DIV_2
// ->Peripheral Clock Divisor
#pragma config FPBDIV   = DIV_2
// -> System PLL Output Clock Divider
#pragma config FPLLODIV = DIV_1

#define SYS_FREQ        (QUARTZ_FREQUENCY * CLOCK_PLL / 2)

//// Watchdog Timer ////

#pragma config FWDTEN   = OFF
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale

//// MISC ////

// Clock Switching & Fail Safe Clock Monitor
#pragma config FCKSM    = CSDCMD        
// CLKO Enable
#pragma config OSCIOFNC = OFF           
// Internal/External Switch-over
#pragma config IESO     = OFF           
// Secondary Oscillator Enable
#pragma config FSOSCEN  = OFF           
// Code Protect
#pragma config CP       = OFF           
// Boot Flash Write Protect
#pragma config BWP      = OFF           
// Program Flash Write Protect
#pragma config PWP      = OFF           
// ICE/ICD Comm Channel Select
#pragma config ICESEL   = ICS_PGx1

#endif
