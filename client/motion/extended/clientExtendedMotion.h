#ifndef CLIENT_EXTENDED_MOTION_H
#define CLIENT_EXTENDED_MOTION_H

#include <stdbool.h>

// BSPLINE 

/**
 * Do a bspline curve using relative coordinates (x, y, angle)
 */
bool clientExtendedMotionBSplineRelative(float x, float y, float angle, float dist0, float dist1, float accelerationFactor, float speedFactor);

/**
 * Do a bspline curve using absolute coordinates (x, y, angle)
 */
bool clientExtendedMotionBSplineAbsolute(float x, float y, float angle, float dist0, float dist1, float accelerationFactor, float speedFactor);

#endif
