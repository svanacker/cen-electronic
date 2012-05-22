#include "singleBSpline.h"

#include "bspline.h"

#include "../../common/commons.h"

#include "../../common/2d/2d.h"

// Definition of the curve when using bspline
static BSplineCurve curve;

static BOOL initialized = FALSE;

BSplineCurve* getSingleBSplineCurve() {
	if (!initialized) {
		initFirstTimeBSplineCurve(&curve);
		initialized = TRUE;
	}
	return &curve;
}
