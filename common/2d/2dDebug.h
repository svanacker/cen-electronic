#ifndef _2D_DEBUG_H
#define _2D_DEBUG_H

#include "2d.h"

#include "../../common/io/outputStream.h"

// PRINT Functions

/**
 * Print a point value (x / y) with the unit.
 * @param outputStream the stream in which we write the content of a point
 * @param point the point that we want to write
 * @param unit the unit for the coordinates
 */
void printPoint(OutputStream* outputStream, Point* point, const char* unit);

/**
 * Append a string, and a value in radians converted to deg.
 * @param outputStream the stream in which we write the content of a point
 * @param valueName the name of the value
 * @param angleInRadians the angle in radians that we want to write.
 */
void appendStringAndAngleInDeg(OutputStream* outputStream, const char* valueName, float angleInRadians);

#endif
