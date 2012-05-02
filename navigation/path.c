#include <stdlib.h>

#include "path.h"
#include "location.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

BOOL pathContainsLocation(Path* path, Location* location) {
	return path->location1 == location || path->location2 == location;
}

Location* getOtherEnd(Path* path, Location* location) {
	if (path->location1 == location) {
		return path->location2;
	}
	if (path->location2 == location) {
		return path->location1;
	}
	return NULL;
}

void printPath(OutputStream* outputStream, Path* path) {
	Location* location1 = path->location1;
	appendStringAndDec(outputStream, "L1(", location1->x);
	appendStringAndDec(outputStream, ",", location1->y);
	appendString(outputStream, ") => ");

	Location* location2 = path->location2;
	appendStringAndDec(outputStream, "L2(", location2->x);
	appendStringAndDec(outputStream, ",", location2->y);
	append(outputStream, ')');
	appendStringAndDec(outputStream, ", cost=", path->cost);

	appendStringAndDec(outputStream, ", cp1=", path->controlPointDistance1);
	appendStringAndDec(outputStream, ", cp2=", path->controlPointDistance2);

	appendStringAndDec(outputStream, ", angle1=", path->angle1);
	appendStringAndDec(outputStream, ", angle2=", path->angle2);

	appendStringAndDec(outputStream, ", speedFactor=", path->speedFactor);

	println(outputStream);
}
