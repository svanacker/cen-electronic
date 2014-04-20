
#include "../commons.h"

#include <timer.h>

#include "cenDelay.h"

void delayUs(void) {
    char i;

    i = 2;
    while (i > 0) {
        Nop();
        Nop();
        Nop();
        --i;
    }
}

void delay100us(char uSecond) {
#ifndef MPLAB_SIMULATION
    unsigned int i;

    while (uSecond != 0) {
	#ifdef PROG_32
        i = 164;
	#else
		i = 488;
	#endif
        while (i > 0) {
            Nop();
            Nop();
            --i;
        }
        --uSecond;
    }
#endif
}

void delaymSec(unsigned int mSecond) {
    // Simulation mode
#ifndef MPLAB_SIMULATION
    unsigned int i;

    while (mSecond != 0) {
		#ifdef PROG_32
			i = 1664;
		#else
			i = 4920;
		#endif
        while (i > 0) {
            Nop();
            Nop();
            --i;
        }
        --mSecond;
    }
#endif
}
