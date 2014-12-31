#include "../random.h"

#include <p30fxxxx.h>
#include <stdlib.h>

void initRandomGenerator() {
    srand(TMR1);
}
