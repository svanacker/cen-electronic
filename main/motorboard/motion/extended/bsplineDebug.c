#include "bsplineDebug.h"

// For debug
#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

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

void writeBSplineDefinitionPoint(OutputStream* outputStream, Point* point, char* pointName, float factor) {
	appendString(outputStream, pointName);
	appendStringAndDecf(outputStream, "(x=", point->x * factor);
	appendStringAndDecf(outputStream, ",y=", point->y * factor);
	appendString(outputStream, ")\n");
}

void writeBSplineControlPoints(OutputStream* outputStream, BSplineCurve* bSplineCurve, float factor) {
	writeBSplineDefinitionPoint(outputStream, &(bSplineCurve->p0), "p0", factor);
	writeBSplineDefinitionPoint(outputStream, &(bSplineCurve->p1), "p1", factor);
	writeBSplineDefinitionPoint(outputStream, &(bSplineCurve->p2), "p2", factor);
	writeBSplineDefinitionPoint(outputStream, &(bSplineCurve->p3), "p3", factor);
}

void writeBSplineDefinition(OutputStream* outputStream, BSplineCurve* bSplineCurve) {
	writeBSplineControlPoints(outputStream, bSplineCurve, 1.0f);

	float curveLength = bSplineCurve->curveLength;
	appendStringAndDecf(outputStream, "\ncurve.length=", curveLength);
	appendString(outputStream, " mm\n");

	/*
	appendString(outputStream, "lastPointData:\n");
	writeBSplinePointData(outputStream, &(bSplineCurve->lastPointData));

	appendString(outputStream, "tempPointData:\n");
	writeBSplinePointData(outputStream, &(bSplineCurve->tempPointData));
	*/

	appendStringAndDec(outputStream, "acc Factor:", bSplineCurve->accelerationFactor);
	println(outputStream);

	appendStringAndDec(outputStream, "Speed Factor:", bSplineCurve->speedFactor);
	println(outputStream);
}

void writeBSpline(OutputStream* outputStream, BSplineCurve* bSplineCurve) {
	writeBSplineDefinition(outputStream, bSplineCurve);

	// BSplinePointData* splinePointData = &(bSplineCurve->lastPointData);

	/*
	float curveLength = bSplineCurve->curveLength;

	// Using constant length segment
	appendString(outputStream, "Const length:\n");
	writeBSplineHeader(outputStream);
	float length;
	for (length = 0.0f; length <= curveLength; length += (curveLength / 40.0f)) {
		computeBSplineTimeAtDistance(bSplineCurve, length);

		writeBSplinePointData(outputStream, splinePointData);
	}
	*/

	// Using constant time
	appendString(outputStream, "\nConst time:\n");
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

	
	/*
	for (t = 0.0f; t <= 1.0f; t += BSPLINE_TIME_INCREMENT) {
		computeBSplinePoint(bSplineCurve, t, point);
		splinePointData->time = t;

		float angle = computeBSplineOrientationWithDerivative(bSplineCurve, t);
		splinePointData->orientation = angle;

		writeBSplinePointData(outputStream, splinePointData);
  	}
	*/
}


