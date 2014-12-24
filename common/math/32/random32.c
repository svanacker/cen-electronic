#include "../random.h"

#include <plib.h>

#include <stdlib.h>

void initRandomGenerator() {
	srand(TMR1);
}
