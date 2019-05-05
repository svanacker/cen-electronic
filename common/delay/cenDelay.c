#include "../commons.h"

#include "cenDelay.h"

#ifdef PROG_32
    #define _SUPPRESS_PLIB_WARNING
    #include <plib.h>
#include "32/cenDelay32.h"
#endif

void delayUs(void) {
}

void delay10us(unsigned char uSecond) {
    unsigned int i;

    while (uSecond > 0) {
        i = VALUE_FOR_10_MICRO_SECOND;
        while (i > 0) {
            Nop();
            Nop();
            --i;
        }
        --uSecond;
    }
}

void delay100us(unsigned char uSecond) {
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
}

void delaymSec(unsigned int mSecond) {
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
}
