#include <timer.h>

#include "delay30F.h"

#include "../commons.h"

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
        i = 488;
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
        i = 4920;
        while (i > 0) {
            Nop();
            Nop();
            --i;
        }
        --mSecond;
    }
#endif
}
