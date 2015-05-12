#include "startMatchDetectorPc.h"
#include "../startMatch.h"

#include <stdbool.h>

static bool matchStarted;

void startMatchPc(void) {
    matchStarted = true;
}

bool isMatchStartedPc(StartMatch* startMatch) {
    return matchStarted;
}
