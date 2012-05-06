#include <stdlib.h>

#include "location.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/string/cenString.h"

#include "location.h"

BOOL locationEquals(Location* location1, Location* location2) {
	return stringEquals(location1->name, location2->name);
}

void printLocation(OutputStream* outputStream, Location* location) {
	appendKeyAndName(outputStream, "location.name=", location->name);
	// Print pointer value
	appendStringAndDec(outputStream, ", ref=", (int) location);

	appendStringAndDec(outputStream, ", x=", location->x);
	appendStringAndDec(outputStream, ", y=", location->y);
	appendStringAndDec(outputStream, ", tmpCost=", location->tmpCost);
	if (location->tmpPreviousLocation != NULL) {
		appendKeyAndName(outputStream, ", tmpPrevious.name=", location->tmpPreviousLocation->name);
	}
	else {
		appendKeyAndName(outputStream, ", tmpPrevious.name=", "NULL");
	}
	println(outputStream);
}
