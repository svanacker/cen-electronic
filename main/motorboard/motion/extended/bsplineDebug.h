#ifndef B_SPLINE_DEBUG_H
#define B_SPLINE_DEBUG_H

#include "bspline.h"

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"

#define CSV_SEPARATOR "\t"

// DEBUG FUNCTION

/**
 * Write the content of a point to an outputStream
 */
void writePoint(OutputStream* outputStream, Point* point);

/**
 * Write into the serial port a point with the associated t value.
 * It's very useful to debug.
 */
void writeBSplinePointData(OutputStream* outputStream, BSplinePointData* splinePointData);

/**
 * Write into the serial port the list of point for the bezier spline.
 * It's very useful to debug.
 */
void writeBSpline(OutputStream* outputStream, BSplineCurve* bSplineCurve);

/**
 * Write the control points (4) of the BSpline Curve.
 */
void writeBSplineControlPoints(OutputStream* outputStream, BSplineCurve* bSplineCurve, float factor);

#endif
