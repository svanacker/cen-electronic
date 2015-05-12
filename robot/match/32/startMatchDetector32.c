#include "startMatchDetector32.h"
#include "../startMatch.h"

#include <stdbool.h>
#include <plib.h>

bool isMatchStarted32(StartMatch* startMatch) {
    return PORTGbits.RG3 != 0;
}
