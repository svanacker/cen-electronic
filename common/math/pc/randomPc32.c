#include "../random.h"

#include <stdlib.h>

void initRandomGenerator() {
	srand((unsigned)time(NULL));
}