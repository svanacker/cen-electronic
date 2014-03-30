#ifndef TWOD_H
#define TWOD_H

#include "../../common/io/printWriter.h"

/**
 * Define a Point structure.
 */
typedef struct Point {
    float x;
    float y;
} Point;

/**
 * Structures to define the position with angle.
 */
typedef struct {
    /** The position of the robot. */
    Point pos;
    /** The orientation of the robot. */
    float orientation;
    /** The initial orientation of the robot. */
    float initialOrientation;
} Position;


/**
 * Computes the distance between 2 points.
 * @param p0 the first point
 * @param p1 the second point
 */
float distanceBetweenPoints(Point* p0, Point* p1);

/**
 * Computes the distance between 2 points.
 */
float distanceBetweenPoints2(float x0, float y0, float x1, float y1);

/**
 * Computes the angle of the vector defined by P0->P1
 * @param p0 the first point
 * @param p1 the second point
 */
float angleOfVector(Point* p0, Point* p1);

/**
* Scale a coordinates system by applying a factor for x and y
*/
void scale(Point *point, float factor);

/**
* Computes a rotation around point (x, y).
*/
void rotate(Point* point, float angle, float x, float y);

// PRINT Functions

/**
 * Print a point value (x / y) with the unit.
 */
void printPoint(OutputStream* outputStream, Point* point, const char* unit);

/**
 * Append a string, and a value in radians converted to deg.
 */
void appendStringAndAngleInDeg(OutputStream* outputStream, const char* valueName, float angleInRadians);

#endif
