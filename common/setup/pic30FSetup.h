#ifndef PIC_30F_SETUP_H
#define PIC_30F_SETUP_H

#include <p30Fxxxx.h>

_FOSC(CSW_FSCM_OFF & XT_PLL16);  //7Mhz3728 * 16  = 117,9648 MHz /4 = 29,4912 MIPS maxi pour ce pic
_FWDT(WDT_OFF);					//Watchdog OFF
_FBORPOR(PBOR_ON & PWRT_64 & MCLR_EN);

_FGS(CODE_PROT_OFF);			//Codeprotect OFF

#endif
