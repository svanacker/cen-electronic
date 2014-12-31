#ifndef PIC_SETUP_30F_H
#define PIC_SETUP_30F_H

#include <p30Fxxxx.h>

// 7Mhz3728 * 16  = 117,9648 MHz / 4 = 29,4912 MIPS max for this pic
_FOSC(CSW_FSCM_OFF & XT_PLL16);  

// Watchdog OFF
_FWDT(WDT_OFF);  

// Power On Reset                  
_FBORPOR(PBOR_ON & PWRT_64 & MCLR_EN);

// Code protect OFF
_FGS(CODE_PROT_OFF);            

#endif
