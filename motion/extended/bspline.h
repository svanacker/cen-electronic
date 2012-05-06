#ifndef B_SPLINE_H
#define B_SPLINE_H

#include "../../common/2d/2d.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

/**
 * Extended motion to generate more complexe trajectory like
 * Bezier / B-Spline curve, cycloid, and not only rotation, and translation move.
 * @author svanacker
 * @version 19/05/2010
 */

/**
 * The order in term of x^n of the B Spline curve.
 */
#define BSPLINE_POINT_COUNT 4

/**
 * Increment to compute in the time segment [0.1].
 * We use 2000 points to interpolate the curve.
 */
#define BSPLINE_TIME_INCREMENT 0.005f

/**
 * Store distance length at certain time.
 */
typedef struct BSplinePointData {
    // time in [0..1].
    float time;
    // distance in terms of curve length at this point
    // since the origin of the curve
    float length;
    // the stored Point
    Point* point;
    // the orientation
    float orientation;
} BSplinePointData;

/** Use distance decomposition to reach method. */
#define BSPLINE_COMPUTE_METHOD_DISTANCE		0

/** Use time decomposition to reach method. */
#define BSPLINE_COMPUTE_METHOD_TIME			1

/**
 * Define a bezierCurve, with 4 points.
 */
typedef struct BSplineCurve {
    Point* p0;
    Point* p1;
    Point* p2;
    Point* p3;
	BOOL backward;
    // The length of the curve.
    float curveLength;
    // Store the last computed information for a point of the curve
    // (the nearest previous point of the curve for the robot.
    BSplinePointData* lastPointData;
    // Useful structure for compute
    BSplinePointData* tempPointData;
	// Method computation
	unsigned char method;
	// accelerationFactor
	unsigned char accelerationFactor;
	// speedFactor
	unsigned char speedFactor;
} BSplineCurve;

/**
 * Init a bSpline Curve with values, and all structures necessary to allocate memory.
 */
void initFirstTimeBSplineCurve(BSplineCurve* bSplineCurve,
        Point* p0, Point* p1, Point* p2, Point* p3,
        BSplinePointData* lastPointData, Point* lastPoint,
        BSplinePointData* tempPointData, Point* tempPoint);

/**
 * Init a bSpline Curve with values, when the structures is already initialized.
 */
void resetBSplineCurve(BSplineCurve* bSplineCurve, float p0x, float p0y, BOOL backward);

// Low Level Point Computation

/**
 * Compute the value of bezier points, with the parametric value t.
 * @param bSplineCurve the curve we want to compute
 * @param t value in [0..1]
 */
void computeBSplinePoint(BSplineCurve* bSplineCurve, float time, Point* resultPoint);

/**
 * Compute the orientation of bezier points at the parametric value t.
 * @param bSplineCurve the curve we want to compute
 * @param t value in [0..1]
 */
float computeBSplineOrientationWithDerivative(BSplineCurve* bSplineCurve, float t);

/**
* Compute the max derivative from the bSplineCurve. It's necessary to determine
* best acceleration value to avoid 
*/
float computeBSplineMaxDerivative(BSplineCurve* bSplineCurve);

// BSPlinePointData

/**
 * Fill a splinePointData and compute his curveLength and the point by using previous computed point curve
 * stored in the BSplineCurve.
 */
void computeBSplinePointData(BSplineCurve* bSplineCurve, float time, BSplinePointData* splinePointData);

/**
 * Copy the content of B-SplineData.
 * @param source the source of content which will be copy to target
 * @param target the target in which we copy source data
 */
void copyBSplineData(BSplinePointData* source, BSplinePointData* target);

/**
 * Compute the length of a bezier arc curve.
 * @param bezierPoints the point which define the bezier curve
 */
float computeBSplineArcLength(BSplineCurve* bSplineCurve, float timeIncrement);

/**
 * Compute the interpolation when the length is between two points corresponding to
 * 2 length.
 * @param beforePoint the previous Point which was computed
 * @param nextPoint the next computed Point
 * @param length a length which must be in the segment [lengthBefore..lengthAfter]
 */
float computeTimeWithInterpolation(BSplinePointData* beforePointData,
        BSplinePointData* afterPointData,
        float length);

/**
 * Computes the time at the distance.
 * @param distance the distance from which we must know the time
 * @return a value between 0 and 1 corresponding to the t parameter
 */
float computeBSplineTimeAtDistance(BSplineCurve* bSplineCurve, float distance);


#endif
