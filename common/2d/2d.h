#ifndef _2D_H
#define _2D_H

#include <stdbool.h>

/**
 * Define a Point structure.
 */
typedef struct Point {
    float x;
    float y;
} Point;

// We store (not for compute) a precision of position to the millimeter
#define POSITION_DIGIT_MM_PRECISION      0

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

// We store or interact via outputStream/inputStream an angle with a precision of 0,1 degree
#define ANGLE_DIGIT_DEGREE_PRECISION  1

/**
 * Computes the distance between 2 points.
 * @param p0 the first point
 * @param p1 the second point
 * @return the distance between 2 points
 */
float distanceBetweenPoints(Point* p0, Point* p1);

/**
 * Computes the distance between 2 points.
 * @param x0 the value of Point 0 along Axis x
 * @param y0 the value of Point 0 along Axis y
 * @param x1 the value of Point 1 along Axis x
 * @param y1 the value of Point 1 along Axis y
 * @return the distance between 2 points
 */
float distanceBetweenPoints2(float x0, float y0, float x1, float y1);

/**
 * Computes the angle in radian of the vector defined by P0->P1 (between -PI and PI)
 * @param p0 the first point
 * @param p1 the second point
 * @return the angle in radian of the vector defined by P0->P1
 */
float angleOfVector(Point* p0, Point* p1);

/**
* Scale a coordinates system by applying a factor for x and y.
* @param point the point that we want to transform
* @param factor the scale factor
*/
void scale(Point *point, float factor);

/**
* Computes a rotation around point (x, y).
* @param point the result point
* @param angleInRadians the angle of the rotation
* @param x the coordinates along x axis of the center of the rotation
* @param y the coordinates along y axis of the center of the rotation
*/
void rotate(Point* resultPoint, float angleInRadians, float x, float y);

/**
 * Do the projection of a point along a distance and an angle
 */
void computeDirectionPoint(Point* ref, Point* result, float distance, float angleRadian);

// MANAGEMENT OF AREA

/**
* Is the point in the rectangle ?
* @param x the upper left coordinates of the rectangle
* @param y the upper left coordinates of the rectangle
* @param width the width of the rectangle
* @param height the height of the rectangle
* @param pointX the X coordinate of the point that we want to test if it's inside the rectangle
* @param pointX the X coordinate of the point that we want to test if it's inside the rectangle
* @return true if the point is inside the rectangle, false else
*/
bool isInRectangle(float x, float y, float width, float height, float pointX, float pointY);

#endif
