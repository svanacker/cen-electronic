#include <math.h>

#include "gp2y0a02yk.h"

float gp2y0a02ykGetCentimerDistanceForTension(float milliVolt) {
    // This value are based on Excel logarithm regression!
    return -47.82f * log(milliVolt) + 352.11f;
}
