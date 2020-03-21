#include "bsplinetest.h"

#include "../../../common/2d/2d.h"
#include "../../../common/io/outputStream.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../motion/extended/bspline.h"
#include "../../../motion/extended/singleBSpline.h"
#include "../../../motion/extended/bsplineDebug.h"

void testBSpline1() {
    BSplineCurve* curve = getSingleBSplineCurve();
    initBSplineCurve(curve,
            2.0f, 1.0f,
            1.0f, 3.0f,
            9.0f, 6.0f,
            11.0f, 3.0f
            );
    OutputStream* outputStream = getDebugOutputStreamLogger();

    computeBSplineArcLength(curve);

    writeBSpline(outputStream, curve);
}

void testBSpline2() {
    BSplineCurve* curve = getSingleBSplineCurve();
    initBSplineCurve(curve,
            2.0f, 1.0f,
            0.0f, 0.0f,
            9.0f, 6.0f,
            5.0f, 3.0f
            );
    OutputStream* outputStream = getDebugOutputStreamLogger();

    computeBSplineArcLength(curve);

    writeBSpline(outputStream, curve);
}

void testBSpline3() {
    BSplineCurve* curve = getSingleBSplineCurve();
    initBSplineCurve(curve,
            2.0f, 1.0f,
            0.0f, 2.0f,
            7.0f, 8.0f,
            6.0f, 3.0f
            );
    OutputStream* outputStream = getDebugOutputStreamLogger();

    computeBSplineArcLength(curve);

    writeBSpline(outputStream, curve);
}
