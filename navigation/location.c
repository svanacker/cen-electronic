#include <stdlib.h>
#include <string.h>

#include "location.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/string/cenString.h"

#include "location.h"

bool locationEquals(Location* location1, Location* location2) {
    return (strcmp(location1->name, location2->name) == 0);
}

void printLocation(OutputStream* outputStream, Location* location) {
    appendKeyAndName(outputStream, "location.name=", location->name);
    // Print pointer value
    appendStringAndDec(outputStream, ", ref=", (int) location);

    appendStringAndDecf(outputStream, ", x=", location->x);
    appendStringAndDecf(outputStream, ", y=", location->y);
    appendStringAndDecf(outputStream, ", tmpCost=", location->tmpCost);
    if (location->tmpPreviousLocation != NULL) {
        appendKeyAndName(outputStream, ", tmpPrevious.name=", location->tmpPreviousLocation->name);
    }
    else {
        appendKeyAndName(outputStream, ", tmpPrevious.name=", "NULL");
    }
    if (location->resultNextLocation != NULL) {
        appendKeyAndName(outputStream, ", resultNext.name=", location->resultNextLocation->name);
    }
    else {
        appendKeyAndName(outputStream, ", resultNext.name=", "NULL");
    }
    println(outputStream);
}
