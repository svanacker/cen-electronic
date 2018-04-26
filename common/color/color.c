#include "color.h"

bool isColorInRange(Color* color,
    unsigned int rLowThreshold, unsigned int rHighThreshold,
    unsigned int gLowThreshold, unsigned int gHighThreshold,
    unsigned int bLowThreshold, unsigned int bHighThreshold) {
    return (color->R >= rLowThreshold && color->R <= rHighThreshold &&
        color->G >= gLowThreshold && color->G <= gHighThreshold &&
        color->B >= bLowThreshold && color->B <= bHighThreshold);
}