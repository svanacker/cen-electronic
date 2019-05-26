#include "../../../common/commons.h"

#include "../../../common/delay/cenDelay.h"

#ifdef PROG_32
#define _SUPPRESS_PLIB_WARNING
#include <plib.h>
#include "32/cenDelay32.h"
#endif

void delayMicroSecs(unsigned int microSeconds) {
    uint32_t start = ReadCoreTimer();
    // TODO : ReadCoreTimer increments by 40 000 000 by seconds on the 
    // Configuration
    uint32_t cycleToWait = microSeconds * 40;
    //arithmetic modulo 32bit. It works :)
    while ((ReadCoreTimer() - start) < cycleToWait) {
        continue;
    }
}

void delayMilliSecs(unsigned int milliSeconds) {
    uint32_t start = ReadCoreTimer();
    uint32_t cycleToWait = milliSeconds * 40000;
    //arithmetic modulo 32bit. It works :)
    while ((ReadCoreTimer() - start) < cycleToWait) {
        continue;
    }
}
