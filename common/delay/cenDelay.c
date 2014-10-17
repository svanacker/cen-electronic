
#include "../commons.h"

#include "cenDelay.h"

#ifdef PROG_32
    #include "32/cenDelay32.h"
#else
    #include "30F/cenDelay30F.h"
#endif

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
        i = VALUE_FOR_100_MICRO_SECOND;
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
        i = VALUE_FOR_1000_MICRO_SECOND;
        while (i > 0) {
            Nop();
            Nop();
            --i;
        }
        --mSecond;
    }
#endif
}
