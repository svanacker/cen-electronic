#include <stdlib.h>

#include "location.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/string/cenString.h"

#include "location.h"

BOOL locationEquals(Location* location1, Location* location2) {
	return stringEquals(location1->name, location2->name);
}

void printLocation(Location* location, OutputStream* outputStream) {
	appendKeyAndName(outputStream, "location.name=", location->name);
	appendStringAndDec(outputStream, ", x=", location->x);
	appendStringAndDec(outputStream, ", y=", location->y);
	appendStringAndDec(outputStream, ", tmpCost=", location->tmpCost);
	println(outputStream);
}
