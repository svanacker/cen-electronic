#include <stdlib.h>
#include <string.h>

#include "locationList.h"
#include "location.h"

#include "../common/2d/2d.h"

#include "../common/error/error.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/string/cenString.h"

void initLocationList(LocationList* locationList, Location(*locationListArray)[], unsigned int locationListSize) {
    if (locationList == NULL) {
        writeError(LOCATION_LIST_NULL);
        return;
    }
    locationList->locations = locationListArray;
    locationList->maxSize = locationListSize;
}

void clearLocationList(LocationList* locationList) {
    locationList->size = 0;
}

bool isEmptyLocationList(LocationList* locationList) {
    return locationList->size == 0;
}

Location* getLocation(LocationList* locationList, unsigned int index) {
    if (locationList == NULL || locationList->maxSize == 0) {
        writeError(LOCATION_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= locationList->maxSize) {
        writeError(LOCATION_LIST_INDEX_OUT_OF_BOUNDS);
        return NULL;
    }
    Location* result = (Location*)locationList->locations;
    // we don't need use sizeof because our pointer is a Location* pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

void copyLocation(Location* sourceLocation, Location* targetLocation) {
    copyFixedCharArray(&(sourceLocation->name), &(targetLocation->name));
    targetLocation->label = sourceLocation->label;
    targetLocation->computedCost = sourceLocation->computedCost;
    targetLocation->computedHandled = sourceLocation->computedHandled;
    targetLocation->computedNextLocation = sourceLocation->computedNextLocation;
    targetLocation->computedPreviousLocation = sourceLocation->computedPreviousLocation;
    targetLocation->x = sourceLocation->x;
    targetLocation->y = sourceLocation->y;
}

void initLocation(Location* location, char* name, char* label, float x, float y) {
    FixedCharArray* existingLocationName = &(location->name);
    stringToFixedCharArray(name, existingLocationName);
    location->x = x;
    location->y = y;
    location->label = label;
    location->computedCost = NO_COMPUTED_COST;
    location->computedHandled = false;
    location->computedNextLocation = NULL;
    location->computedPreviousLocation = NULL;
}

Location* addNamedLocation(LocationList* locationList, char* name, char* label, float x, float y) {
    if (locationList == NULL || locationList->maxSize == 0) {
        writeError(LOCATION_LIST_NOT_INITIALIZED);
        return NULL;
    }

    unsigned int size = locationList->size;
    if (size < locationList->maxSize) {
        Location* location = getLocation(locationList, size);
        initLocation(location, name, label, x, y);
        locationList->size++;
        return location;
    }
    else {
        writeError(TOO_MUCH_LOCATIONS);
        return NULL;
    }
}

Location* addLocation(LocationList* locationList, FixedCharArray* name, char* label, float x, float y) {
    Location* result = addNamedLocation(locationList, NULL, label, x, y);
    if (result != NULL) {
        FixedCharArray* target = &(result->name);
        copyFixedCharArray(name, target);
    }
    return NULL;
}

Location* findLocationByStringName(LocationList* locationList, char* name) {
    FixedCharArray tempFixedCharArray;
    stringToFixedCharArray(name, &tempFixedCharArray);
    Location* result = findLocationByName(locationList, &tempFixedCharArray);
    return result;
}

Location* findLocationByName(LocationList* locationList, FixedCharArray* locationName) {
    unsigned int i;
    unsigned int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        FixedCharArray* locationName2 = &(location->name);
        if (fixedCharArrayEquals(locationName, locationName2)) {
            return location;
        }
    }
    return NULL;
}

bool containsLocation(LocationList* locationList, Location* locationToFind, bool handled) {
    if (locationToFind == NULL) {
        return false;
    }    
    int i;
    int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        if (location->computedHandled != handled) {
            continue;
        }
        if (locationEquals(location, locationToFind)) {
            return true;
        }
    }
    return false;
}

void removeFirstLocation(LocationList* locationList) {
    // TODO : Implementation is not Optimized ! Use linked list ?
    int size = locationList->size;
    if (size == 0) {
        return;
    }
    int i;
    for (i = 1; i < size; i++) {
        Location* location1 = getLocation(locationList, i - 1);
        Location* location2 = getLocation(locationList, i);
        copyLocation(location2, location1);
    }
    size--;
    locationList->size = size;
}

unsigned int getLocationCount(LocationList* locationList) {
    return locationList->size;
}

unsigned int getLocationNotHandledCount(LocationList* locationList) {
    unsigned int result = 0;
    unsigned int i;
    unsigned int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        if (location->computedHandled) {
            result++;
        }
    }
    return result;
}

// CLEAR

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
void clearLocationTmpInfo(LocationList* locationList) {
    unsigned int i;
    unsigned int size = locationList->size;
    for (i = 0; i < size; i++) {
        Location* location = getLocation(locationList, i);
        location->computedCost = MAX_COST;
        location->computedNextLocation = NULL;
        location->computedPreviousLocation = NULL;
        location->computedHandled = false;
    }
}
