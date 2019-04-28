#include <math.h>

#include "../../common/error/error.h"
#include "../../common/math/cenMath.h"

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/bsplineDebug.h"
#include "../../motion/extended/bsplineMotion.h"
#include "../../motion/motionConstants.h"

void initBSplineCurveData(BSplinePointData* pointData, float x, float y) {
    pointData->time = 0.0f;
    pointData->length = 0.0f;
    pointData->orientation = 0.0f;
    pointData->point.x = x;
    pointData->point.y = y;
}

void resetBSplineCurve(BSplineCurve* bSplineCurve, 
                      float p0x, float p0y, bool backward) {
    bSplineCurve->p0.x = p0x;
    bSplineCurve->p0.y = p0y;

    bSplineCurve->p1.x = 0.0f;
    bSplineCurve->p1.y = 0.0f;

    bSplineCurve->p2.x = 0.0f;
    bSplineCurve->p2.y = 0.0f;

    bSplineCurve->p3.x = 0.0f;
    bSplineCurve->p3.y = 0.0f;

//    initBSplineCurveData(&(bSplineCurve->lastPointData), p0x, p0y);
//    initBSplineCurveData(&(bSplineCurve->tempPointData), p0x, p0y);

    bSplineCurve->curveLength = 0.0f;
    
    bSplineCurve->speedFactor = MOTION_SPEED_FACTOR_0;
    bSplineCurve->accelerationFactor = MOTION_ACCELERATION_FACTOR_0;

    bSplineCurve->backward = backward;
}

void initFirstTimeBSplineCurve(BSplineCurve* bSplineCurve) {
    resetBSplineCurve(bSplineCurve, 0.0f, 0.0f, false);
}

void computeBSplinePoint(BSplineCurve* bSplineCurve, float t, Point* resultPoint) {
    float t2 = t * t;
    float t3 = t2 * t;
    float l_t = (1 - t);
    float l_t2 = l_t * l_t;
    float l_t3 = l_t2 * l_t;
    float _3_t_l_t2 = 3.0f * t * l_t2;
    float _3_t2_l_t = 3.0f * t2 * l_t;

    Point* p0 = &(bSplineCurve->p0);
    Point* p1 = &(bSplineCurve->p1);
    Point* p2 = &(bSplineCurve->p2);
    Point* p3 = &(bSplineCurve->p3);

    // http://en.wikipedia.org/wiki/B%C3%A9zier_curve
    // P(t) = P0 (1 - t)^3 + 3*P1*t(1-t)^2 + 3*P2*t^2(1-t) + P3*t^3

    resultPoint->x = (p0->x * l_t3) + (_3_t_l_t2 * p1->x) + (_3_t2_l_t * p2->x) + (p3->x * t3);
    resultPoint->y = (p0->y * l_t3) + (_3_t_l_t2 * p1->y) + (_3_t2_l_t * p2->y) + (p3->y * t3);
}

float computeBSplineOrientationWithDerivative(BSplineCurve* bSplineCurve, float t) {
    float t2 = t * t;
    float l_t = (1.0f - t);
    float l_t2 = l_t * l_t;
    float _3t = 3.0f * t;
    float _3t_1 = _3t - 1.0f;
    float _3t_2 = _3t - 2.0f;

    // derivative of bezier function is 
    // - 3 * P0 * (t-1)^2   +    3 * P1 * (t - 1) * (3*t - 1) - 3 * P2 * t (3 * t - 2)    + 3 * P3 * t * t
    // d'ou
    // - 3 * (P0 * (t-1)^2  -    P1 * (1 - t) * (3*t - 1)        - P2 * t (3 * t - 2)    +   P3 * t * t)

    Point* p0 = &(bSplineCurve->p0);
    Point* p1 = &(bSplineCurve->p1);
    Point* p2 = &(bSplineCurve->p2);
    Point* p3 = &(bSplineCurve->p3);

    // Warning about orientation
    float diffX = 3.0f * ( (- p0->x * l_t2) - (p1->x * l_t * _3t_1) - (p2->x * t * _3t_2) + (p3->x * t2) );
    float diffY = 3.0f * ( (- p0->y * l_t2) - (p1->y * l_t * _3t_1) - (p2->y * t * _3t_2) + (p3->y * t2) );

    // note that the atan2 is atan2(y, x) and not atan2(x, y)
    float result = atan2f(diffY, diffX);
    
    // TODO : There is a big problem if diffY = 0 and diffX = 0 because it is undefined !

    // There is another method to compute the tangent of a bezier curve
    // see http://www.planetclegg.com/projects/WarpingTextToSplines.html

    return result;
}

void copyBSplineData(BSplinePointData* source, BSplinePointData* target) {
    target->time = source->time;
    target->length = source->length;
    target->orientation = source->orientation;
    target->point.x = source->point.x;
    target->point.y = source->point.y;
}

float computeBSplineArcLength(BSplineCurve* bSplineCurve, float timeIncrement) {
    float result = 0;

    float t;
    Point point;
    Point previousPoint;
    previousPoint.x = bSplineCurve->p0.x;
    previousPoint.y = bSplineCurve->p0.y;
    for (t = timeIncrement; t <= 1.0f; t += timeIncrement) {
        computeBSplinePoint(bSplineCurve, t, &point);
        float distance = distanceBetweenPoints(&previousPoint, &point);
        result += distance;
        previousPoint.x = point.x;
        previousPoint.y = point.y;
    }
    bSplineCurve->curveLength = result;

    return result;
}

float computeTimeWithInterpolation(BSplinePointData* beforePointData,
                                   BSplinePointData* afterPointData,
                                   float length) {
    // the length of curve between the origin of the curve and the previous computed Point
    float lengthBefore = beforePointData->length;
    float lengthAfter = afterPointData->length;
    float segmentLength = lengthAfter - lengthBefore;

    // determine where we are between the 'before' and 'after' points in terms of "fraction".
    float segmentFraction = (length - lengthBefore) / segmentLength;

    // add that fractional amount to the result
    float splineXTimeBefore = beforePointData->time;
    float splineXTimeAfter = afterPointData->time;

    float diffTime = splineXTimeAfter - splineXTimeBefore;
    float result = splineXTimeAfter + diffTime * segmentFraction;

    return result;
}

float computeBSplineTimeAtDistance(BSplineCurve* bSplineCurve, float distance) {
    if (isFloatNegative(distance)) {
        writeError(MOTION_BSPLINE_DISTANCE_MUST_BE_POSITIVE);
        return 1.0f;
    }
    float length = bSplineCurve->curveLength;
    if (!floatEqualsZero(length)) {
        return distance / length;
    }
    // TODO : Check if we must return 1.0f
    return 1.0f;
}


void parameterBSplineWithDistanceAndAngle(BSplineCurve* curve,
    float sourceX, float sourceY, float sourceAngleRadian,
    float destX, float destY, float destAngleRadian,
    float distance1, float distance2,
    float accelerationFactor, float speedFactor,
    bool relative) {

    // If the distance of the control point is negative, we considerer that we go
    // back
    bool backward = distance1 < 0.0f;

    // For P0-P1
    float c1 = cosf(sourceAngleRadian);
    float s1 = sinf(sourceAngleRadian);

    float dca1 = (distance1 * c1);
    float dsa1 = (distance1 * s1);

    // For P2-P3
    float c2 = cosf(destAngleRadian);
    float s2 = sinf(destAngleRadian);

    float dca2 = (distance2 * c2);
    float dsa2 = (distance2 * s2);

    // Update the bspline curve
    // P0
    resetBSplineCurve(curve, sourceX, sourceY, backward);
    curve->accelerationFactor = accelerationFactor;
    curve->speedFactor = speedFactor;

    // P1
    Point* point = &(curve->p1);
    // P1 along x axis
    point->x = (sourceX + dca1);
    point->y = (sourceY + dsa1);

    if (relative) {

        // P2
        point = &(curve->p2);
        rotate(point, sourceAngleRadian, (destX - dca2), (destY - dsa2));
        point->x += sourceX;
        point->y += sourceY;

        // P3
        point = &(curve->p3);
        rotate(point, sourceAngleRadian, (destX), (destY));
        point->x += sourceX;
        point->y += sourceY;
    }
    else {
        // P2
        point = &(curve->p2);
        point->x = (destX - dca2);
        point->y = (destY - dsa2);

        // P3
        point = &(curve->p3);
        point->x = destX;
        point->y = destY;
    }
    computeBSplineArcLength(curve, BSPLINE_TIME_INCREMENT);
}
