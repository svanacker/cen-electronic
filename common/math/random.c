#include "random.h"

#include <stdlib.h>

#define RANDOM_RANGE_MAX 35535

int randomInRange(int range_min, int range_max) {
    int result = (int) ((double) rand() / (RANDOM_RANGE_MAX + 1) * (range_max - range_min)
            + range_min);
    return result;
}
