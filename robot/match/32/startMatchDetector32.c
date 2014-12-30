#include "startMatchDetector32.h"
#include "../startMatchDetector.h"

#include <stdbool.h>
#include <plib.h>

bool isMatchStarted32(StartMatchDetector* startMatchDetector) {
    return PORTGbits.RG3 != 0;
}

void initStartMatchDetector32(StartMatchDetector* startMatchDetector) {
    initStartMatchDetector(startMatchDetector, isMatchStarted32);
}