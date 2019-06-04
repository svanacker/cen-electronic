#include <math.h>

#include "../../common/2d/2d.h"

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

void computeBSplineDerivativeComponents(BSplineCurve* bSplineCurve, float t, Point* derivativeResult) {
    float t2 = t * t;
    float l_t = (1.0f - t);
    float l_t2 = l_t * l_t;
    float _3t = 3.0f * t;
    float _3t_1 = _3t - 1.0f;
    float _3t_2 = _3t - 2.0f;

    // derivative of bezier function is 
    // - 3 * P0 * (t-1)^2   +    3 * P1 * (t - 1) * (3*t - 1) - 3 * P2 * t (3 * t - 2)    + 3 * P3 * t * t
    // d'ou
    // 3 * (-P0 * (t-1)^2  -    P1 * (1 - t) * (3*t - 1)        - P2 * t (3 * t - 2)    +   P3 * t * t)

    Point* p0 = &(bSplineCurve->p0);
    Point* p1 = &(bSplineCurve->p1);
    Point* p2 = &(bSplineCurve->p2);
    Point* p3 = &(bSplineCurve->p3);

    derivativeResult->x = 3.0f * ( (- p0->x * l_t2) - (p1->x * l_t * _3t_1) - (p2->x * t * _3t_2) + (p3->x * t2) );
    derivativeResult->y = 3.0f * ( (- p0->y * l_t2) - (p1->y * l_t * _3t_1) - (p2->y * t * _3t_2) + (p3->y * t2) );
}

void computeBSplineAccelerationComponent(BSplineCurve* bSplineCurve, float t, Point* accelerationResult) {
    Point* p0 = &(bSplineCurve->p0);
    Point* p1 = &(bSplineCurve->p1);
    Point* p2 = &(bSplineCurve->p2);
    Point* p3 = &(bSplineCurve->p3);
    
    // Formula of acceleration for cubic curve is available here :
    // https://en.wikipedia.org/wiki/B%C3%A9zier_curve
    accelerationResult->x = 6.0f * (1.0f - t) * (p2->x - 2.0f * p1->x + p0->x) + 6.0f * t * (p3->x - 2.0f * p2->x + p1->x);
    accelerationResult->y = 6.0f * (1.0f - t) * (p2->y - 2.0f * p1->y + p0->y) + 6.0f * t * (p3->y - 2.0f * p2->y + p1->y);
}

float computeBSplineSpeed(BSplineCurve* bSplineCurve, float t) {
    Point derivativeResult;

    computeBSplineDerivativeComponents(bSplineCurve, t, &derivativeResult);

    // https://brilliant.org/wiki/parametric-equations-velocity-and-acceleration/
    return sqrtf(derivativeResult.x * derivativeResult.x + derivativeResult.y + derivativeResult.y);
}

float computeBSplineOrientationWithDerivative(BSplineCurve* bSplineCurve, float t) {
    Point derivativeResult;

    computeBSplineDerivativeComponents(bSplineCurve, t, &derivativeResult);

    // note that the atan2 is atan2(y, x) and not atan2(x, y)
    float result = atan2f(derivativeResult.y, derivativeResult.x);
    
    // TODO : There is a big problem if diffY = 0 and diffX = 0 because it is undefined !

    // There is another method to compute the tangent of a bezier curve
    // see http://www.planetclegg.com/projects/WarpingTextToSplines.html

    return result;
}

float computeBSplineAccelerationNormalVector(BSplineCurve* bSplineCurve, float t) {
    Point accelerationResult;

    computeBSplineAccelerationComponent(bSplineCurve, t, &accelerationResult);
    
    // TODO

    return 0.0f;
}

float computeBSplineCurvature(BSplineCurve* bSplineCurve, float t) {
    Point p;
    computeBSplinePoint(bSplineCurve, t, &p);
    Point d;
    computeBSplineDerivativeComponents(bSplineCurve, t, &d);
    Point a;
    computeBSplineAccelerationComponent(bSplineCurve, t, &a);

    float dx = p.x;
    float dy = p.y;
    
    float ddx = a.x;
    float ddy = a.y;
    
    float numerator = dx * ddy - ddx * dy;
    float denominator = powf(dx*dx + dy*dy, 1.5);
    
    return numerator / denominator;
}

float computeNormalAccelerationAtCenter(BSplineCurve* bSplineCurve, float t) {
    float speed = computeBSplineSpeed(bSplineCurve, t);
    float radius = computeBSplineCurveRadius(bSplineCurve, t);
    
    if (radius == 0.0f) {
        return 0.0f;
    }
    
    return speed * speed / radius;
}

float computeTangentialAccelerationAtCenter(BSplineCurve* bSplineCurve, float t) {

}

void copyBSplineData(BSplinePointData* source, BSplinePointData* target) {
    target->time = source->time;
    target->length = source->length;
    target->orientation = source->orientation;
    target->point.x = source->point.x;
    target->point.y = source->point.y;
}

float computeBSplineArcApproximativeLength(BSplineCurve* bSplineCurve, float t) {
    // Implementation from : https://pomax.github.io/bezierinfo/#arclength
    // We take z = 1.0
    return 0.0f;
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

float computeBSplineCurveRadius(BSplineCurve* curve, float time) {
    float incrementTime = BSPLINE_TIME_INCREMENT;
    Point p1, p2, p3, centerPointOfRotation;
    computeBSplinePoint(curve, time - incrementTime, &p1);
    computeBSplinePoint(curve, time, &p2);
    computeBSplinePoint(curve, time + incrementTime, &p3);
    
    bool isCurve = computeRotationCenteredPoint(&p1, &p2, &p3, &centerPointOfRotation);
    if (!isCurve) {
        // We go forward, so no difference between the wheels
        return 0.0f;
    }
    
    return distanceBetweenPoints(&p2, &centerPointOfRotation);
}

float computeSpeedFactorToCenterDueToCurve(BSplineCurve* curve, float time, float distanceToCurve) {
    float radius = computeBSplineCurveRadius(curve, time);
    if (fabs(radius) < 0.001f) {
        // No radius => the speed factor is the same
        return 1.0f;
    } 
    
    // The speed of a point on a circle is 2 * PI * R / T
    // The radius for one on the point (the most excentric point compared to the 
    // center of the point is (radius + distanceToCurve) and the other is (radius - distanceToCurve).
    // So the speed
    // The real speed of the most excentric is (distanceToCurve + R) * 2 * PI
    // So the speed Factor due to the curve is  : 2 * PI * (R + distanceToCurve)  / 2 * PI * R
    // = 1 + distanceToCurve / radius
    return 1 + (distanceToCurve / radius); 
}

float computeAccelerationFactorToCenterDueToCurve(BSplineCurve* curve, float time, float speedFactor) {
    // The acceleration Factor is the speedFactor^2
    
    return speedFactor * speedFactor;
}