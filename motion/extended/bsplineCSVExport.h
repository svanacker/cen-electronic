#ifndef B_SPLINE_CSV_H
#define B_SPLINE_CSV_H

#define CSV_SEPARATOR "\t"

#include "../../common/io/outputStream.h"

#include "bspline.h"

/**
* Write into the serial port the list of point for the bezier spline.
* It's very useful to debug.
*/
void writeBSpline(OutputStream* outputStream, BSplineCurve* bSplineCurve);

#endif