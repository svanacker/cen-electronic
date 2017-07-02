#ifndef EXTENDED_MOTION_DRIVER_H
#define EXTENDED_MOTION_DRIVER_H

#include <stdbool.h>

// BSPLINE 

/**
 * Do a bspline curve using relative coordinates (x, y, angle)
 */
bool motionDriverBSplineRelative(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor);

/**
 * Do a bspline curve using absolute coordinates (x, y, angle)
 */
bool motionDriverBSplineAbsolute(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor);

#endif
