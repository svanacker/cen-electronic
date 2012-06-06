#ifndef PIC_32F_SETUP_H
#define PIC_32F_SETUP_H

#include <p32xxxx.h>

// definition des bits de configuration.
// external Quartz, PLL x 10 (20 / 2)
// Watchdog OFF
#pragma config FNOSC = PRIPLL, POSCMOD = HS, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPBDIV = DIV_2, FPLLODIV = DIV_1
#pragma config FWDTEN = OFF
#define SYS_FREQ 				(80000000L)

#endif
