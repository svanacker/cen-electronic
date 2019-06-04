#include <math.h>

#include <stdbool.h>

#include "2d.h"
#include "../../common/math/cenMath.h"

float distanceBetweenPoints(Point* p0, Point* p1) {
    return distanceBetweenPoints2(p0->x, p0->y, p1->x, p1->y);
}

float distanceBetweenPoints2(float x0, float y0, float x1, float y1) {
    float diffX = (x1 - x0);
    float diffY = (y1 - y0);

    float result = sqrtf(diffX * diffX + diffY * diffY);

    return result;
}

float angleOfVector(Point* p0, Point* p1) {
    float diffX = (p1->x - p0->x);
    float diffY = (p1->y - p0->y);

    float result = atan2f(diffY, diffX);
    
    return result;    
}

float angleOfVector2(float p0x, float p0y, float p1x, float p1y) {
    float diffX = (p1x - p0x);
    float diffY = (p1y - p0y);

    float result = atan2f(diffY, diffX);

    return result;
}

// 2D TRANSFORMATIONS

void rotate(Point* resultPoint, float angle, float x, float y) {
    // Computes a rotation around point x / y
    float c = cosf(angle);
    float s = sinf(angle);
    resultPoint->x = (x * c) - (y * s);
    resultPoint->y = (x * s) + (y * c);
}

void scale(Point *point, float factor) {
    point->x /= factor;
    point->y /= factor;
}

void computeDirectionPoint(Point* ref, Point* result, float distance, float angleRadian) {
    float dca = cosf(angleRadian) * distance;
    float dsa = sinf(angleRadian) * distance;
    result->x = ref->x + dca;
    result->y = ref->y + dsa;
}

// AREA DETECTION

bool isInRectangle(float x, float y, float width, float height, float pointX, float pointY) {
    return (x <= pointX && pointX <= x + width) && (y <= pointY && pointY <= y + height);
}

bool isInCircle2(float circleCenterX, float circleCenterY, float circleRadius, float pointX, float pointY) {
    return distanceBetweenPoints2(circleCenterX, circleCenterY, pointX, pointY) <= circleRadius;
}

bool isInCircle(Point* circleCenterPoint, Point* point, float circleRadius) {
    return distanceBetweenPoints(circleCenterPoint, point) <= circleRadius;
}

// ROTATION on 3 Points

/**
 * Implementation inspired from : http://paulbourke.net/geometry/circlesphere/Circle.cpp
 * @param a
 * @param b
 * @param c
 * @param centeredPointIfAny
 * @param radius
 * @return 
 */
bool computeRotationCenteredPoint(Point* a, Point* b, Point* c, Point* centeredPointIfAny) {
    float yDelta_a = b->y - a->y;
    float xDelta_a = b->x - a->x;
    float yDelta_b = c->y - b->y;
    float xDelta_b = c->x - b->x;
    
    // If points are too closed
    if (fabs(xDelta_a) <= 0.000000001 && fabs(yDelta_b) <= 0.000000001){
		centeredPointIfAny->x = 0.5f * (b->x + c->x);
		centeredPointIfAny->y = 0.5f *(a->y + b->y);
       
		return true;
	}
	
	// IsPerpendicular() assure that xDelta(s) are not zero
	float aSlope = yDelta_a / xDelta_a; // 
    float bSlope = yDelta_b / xDelta_b;
    
    // checking whether the given points are colinear. 	
	if (fabs(aSlope - bSlope) <= 0.000000001){	
		return false;
	}

    centeredPointIfAny->x = (aSlope * bSlope * (a->y - c->y) + bSlope * (a->x + b->x)
        - aSlope*(b->x+ c->x)) / (2.0f * (bSlope - aSlope) );
    centeredPointIfAny->y = -1.0f *(centeredPointIfAny->x - (a->x + b->x) / 2.0f) / aSlope +  (a->y + b->y) / 2.0f;

    return true;
}