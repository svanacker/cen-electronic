#ifndef PIC_32F_SETUP_H
#define PIC_32F_SETUP_H

#include <p32xxxx.h>

// Oscillator Selection Bit
#pragma config FNOSC = PRIPLL
// Primary Oscillator Configuration
#pragma config POSCMOD = HS

//// Frequency ////

// -> Multiplication factor
#pragma config FPLLMUL = MUL_20
// -> PLL Input Divider
#pragma config FPLLIDIV = DIV_2
// ->Peripheral Clock Dividor
#pragma config FPBDIV = DIV_2
// -> System PLL Output Clock Divier
#pragma config FPLLODIV = DIV_1

#define SYS_FREQ 				(80000000L)

//// Watchdog Timer ////

#pragma config FWDTEN = OFF
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale

//// MISC ////

// Clock Switching & Fail Safe Clock Monitor
#pragma config FCKSM    = CSDCMD        
// CLKO Enable
#pragma config OSCIOFNC = OFF           
// Primary Oscillator
#pragma config POSCMOD  = XT            
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
