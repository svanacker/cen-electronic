#ifndef B_SPLINE_DEBUG_H
#define B_SPLINE_DEBUG_H

#include "bspline.h"

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"

// CSV DEBUG FUNCTION

/**
 * Write the BSpline Table Definition Header
 */
void writeBSplineDefinitionTableHeader(OutputStream* outputStream);

/**
 * Write a row with the definition of the bspline.
 * It's very useful to debug.
 */
void writeBSplineDefinitionRow(OutputStream* outputStream, unsigned int index, BSplineCurve* bSplineCurve);

#endif
