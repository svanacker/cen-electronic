#include "alphaTheta.h"

float computeTheta(float left, float right) {
    return (left + right) / 2.0f;
}

float computeAlpha(float left, float right) {
    return (left - right) / 2.0f;
}
