#include "alphaTheta.h"

// Left/Right => Theta/Alpha

float computeTheta(float left, float right) {
    return (left + right) / 2.0f;
}

float computeAlpha(float left, float right) {
    return (left - right) / 2.0f;
}

// Theta/Alpha => Left/Right

float computeLeft(float theta, float alpha) {
    return theta + alpha;
}

float computeRight(float theta, float alpha) {
    return theta - alpha;
}