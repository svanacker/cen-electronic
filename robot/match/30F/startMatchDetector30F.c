#include "startMatchDetector30F.h"
#include "../startMatchDetector.h"

#include <stdbool.h>
#include <plib.h>

bool isMatchStarted30F(StartMatchDetector* startMatchDetector) {
    return PORTFbits.RF6 != 0;
}

void initStartMatchDetector30F(StartMatchDetector* startMatchDetector) {
    initStartMatchDetector(startMatchDetector, isMatchStarted30F);
}