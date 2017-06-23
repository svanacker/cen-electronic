#include "../random.h"

#define _SUPPRESS_PLIB_WARNING
#include <plib.h>
#include <stdlib.h>

void initRandomGenerator() {
    srand(TMR1);
}
