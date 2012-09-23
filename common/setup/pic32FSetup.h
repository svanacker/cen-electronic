#ifndef PIC_32F_SETUP_H
#define PIC_32F_SETUP_H

#include <p32xxxx.h>

// definition des bits de configuration.
// external Quartz, PLL x 10 (20 / 2)
// Watchdog OFF

// Oscillator Selection Bit
#pragma config FNOSC = PRIPLL
// Primary Oscillator Configuration
#pragma config POSCMOD = HS

// Frequency
// -> Multiplication factor
#pragma config FPLLMUL = MUL_20
// -> PLL Input Divider
#pragma config FPLLIDIV = DIV_2
// ->Peripheral Clock Dividor
#pragma config FPBDIV = DIV_2
// -> System PLL Output Clock Divier
#pragma config FPLLODIV = DIV_1

// Watchdog Timer
#pragma config FWDTEN = OFF

#define SYS_FREQ 				(80000000L)

#endif
