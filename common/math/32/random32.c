#include "../random.h"

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING 
#include <plib.h>
#include <stdlib.h>

void initRandomGenerator() {
    srand(TMR1);
}
