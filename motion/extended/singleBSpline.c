#include "singleBSpline.h"

#include "bspline.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"

// Definition of the curve when using bspline
static BSplineCurve curve;
static Point p0;
static Point p1;
static Point p2;
static Point p3;
static BSplinePointData lastPointData;
static BSplinePointData tempPointData;
static Point lastPoint;
static Point tempPoint;

static BOOL initialized = FALSE;

BSplineCurve* getSingleBSplineCurve() {
	if (!initialized) {
		initFirstTimeBSplineCurve(&curve, &p0, &p1, &p2, &p3,
						 &lastPointData, &lastPoint,
						&tempPointData, &tempPoint
						);
		initialized = TRUE;
	}
	return &curve;
}
