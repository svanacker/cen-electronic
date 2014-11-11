#include <math.h>

#include "2d.h"
#include "../../common/math/cenMath.h"

float distanceBetweenPoints(Point* p0, Point* p1) {
    return distanceBetweenPoints2(p0->x, p0->y, p1->x, p1->y);
}

float distanceBetweenPoints2(float x0, float y0, float x1, float y1) {
    float diffX = (x1 - x0);
    float diffY = (y1 - y0);

    float result = sqrt(diffX * diffX + diffY * diffY);

    return result;
}

float angleOfVector(Point* p0, Point* p1) {
    float diffX = (p1->x - p0->x);
    float diffY = (p1->y - p0->y);

    float result = atan2f(diffY, diffX);
    
    return result;    
}

// 2D TRANSFORMATIONS

void rotate(Point* point, float angle, float x, float y) {
    // Computes a rotation around point x / y
    float c = cosf(angle);
    float s = sinf(angle);
    point->x = (x * c) - (y * s);
    point->y = (x * s) + (y * c);
}

void scale(Point *point, float factor) {
    point->x /= factor;
    point->y /= factor;
}

// PRINT Functions

void printPoint(OutputStream* outputStream, Point* point, const char* unit) {
    appendStringAndDecf(outputStream, "x=", point->x);
    appendString(outputStream, unit);
    appendStringAndDecf(outputStream, ",y=", point->y);
    appendString(outputStream, unit);
    println(outputStream);
}

void appendStringAndAngleInDeg(OutputStream* outputStream, const char* valueName, float angleInRadians) {
    appendStringAndDecf(outputStream, valueName, angleInRadians / PI_DIVIDE_180);
    appendString(outputStream, " deg");
}
