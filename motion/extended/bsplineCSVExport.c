#include "bsplineCSVExport.h"
#include "bsplineDebug.h"

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "bspline.h"

void writePoint(OutputStream* outputStream, Point* point) {
    appendDecf(outputStream, point->x);
    appendString(outputStream, CSV_SEPARATOR);

    appendDecf(outputStream, point->y);
    appendString(outputStream, CSV_SEPARATOR);
}

void writeBSplinePointData(OutputStream* outputStream, BSplinePointData* splinePointData) {
    float t = splinePointData->time;
    appendDecf(outputStream, t);
    appendString(outputStream, CSV_SEPARATOR);

    Point point = splinePointData->point;
    writePoint(outputStream, &point);

    float distance = splinePointData->length;
    appendDecf(outputStream, distance);
    appendString(outputStream, CSV_SEPARATOR);

    float orientation = splinePointData->orientation;
    appendDecf(outputStream, orientation);

    println(outputStream);
}

void writeBSplineHeader(OutputStream* outputStream) {
    appendCRLF(outputStream);
    appendKeyAndName(outputStream, "t", CSV_SEPARATOR);

    appendKeyAndName(outputStream, "p.x", CSV_SEPARATOR);
    appendKeyAndName(outputStream, "p.y", CSV_SEPARATOR);

    appendKeyAndName(outputStream, "length", CSV_SEPARATOR);

    appendKeyAndName(outputStream, "orientation", CSV_SEPARATOR);

    appendCRLF(outputStream);
}

void writeBSpline(OutputStream* outputStream, BSplineCurve* bSplineCurve) {
    writeBSplineDefinitionTableHeader(outputStream);
    writeBSplineDefinitionRow(outputStream, 0, bSplineCurve);

    // Using constant time
    println(outputStream);
    appendStringLN(outputStream, "Const time:");
    writeBSplineHeader(outputStream);
    float t;
    BSplinePointData splinePointData;
    for (t = 0.0f; t <= 1.0f; t += 0.025f) {
        computeBSplinePoint(bSplineCurve, t, &(splinePointData.point));
        float angle = computeBSplineOrientationWithDerivative(bSplineCurve, t);
        splinePointData.orientation = angle;
        splinePointData.time = t;
        writeBSplinePointData(outputStream, &(splinePointData));
    }
}