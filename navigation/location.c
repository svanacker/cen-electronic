#include <stdlib.h>

#include "location.h"

#include "../common/error/error.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/2d/2d.h"

#include "../common/string/cenString.h"

#include "location.h"

bool locationEquals(Location* location1, Location* location2) {
    return (location1 == location2);
}

float distanceBetweenLocations(Location* location1, Location* location2) {
    if (location1 == NULL) {
        writeError(LOCATION_NULL);
        return 0.0f;
    }
    if (location2 == NULL) {
        writeError(LOCATION_NULL);
        return 0.0f;
    }
    return distanceBetweenPoints2(location1->x, location1->y, location2->x, location2->y);
}