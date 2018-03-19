#include "2dDebug.h"

#include <math.h>
#include "../../common/math/cenMath.h"

#include "../../common/io/printWriter.h"

void printPoint(OutputStream* outputStream, Point* point, const char* unit) {
    appendStringAndDecf(outputStream, "x=", point->x);
    appendString(outputStream, unit);
    appendStringAndDecf(outputStream, ", y=", point->y);
    appendString(outputStream, unit);
    println(outputStream);
}

void appendStringAndAngleInDeg(OutputStream* outputStream, const char* valueName, float angleInRadians) {
    appendStringAndDecf(outputStream, valueName, radToDeg(angleInRadians));
    appendString(outputStream, " deg");
}
