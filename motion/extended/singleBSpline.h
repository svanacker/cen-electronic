#ifndef SINGLE_B_SPLINE_H
#define SINGLE_B_SPLINE_H

#include "../../motion/extended/bspline.h"

/**
 * BSpline takes lot of memory, so we use only instance, for
 * test and other things.
 */
BSplineCurve* getSingleBSplineCurve();

#endif
