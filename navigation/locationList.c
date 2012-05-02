#include <stdlib.h>

#include "locationList.h"
#include "location.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

#include "../common/error/error.h"
#include "../common/string/cenString.h"

void clearLocationList(LocationList* locationList) {
	locationList->size = 0;
	locationList->count = 0;
}

BOOL isEmptyLocationList(LocationList* locationList) {
	return locationList->count == 0;
}

void addLocationList(LocationList* targetLocationList, LocationList* sourceLocationList) {
	int i;
	unsigned char size = sourceLocationList->size;
	for (i = 0; i < size; i++) {
		Location* location = sourceLocationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		addFilledLocation(targetLocationList, location);
	}	
}

void addLocation(LocationList* locationList, Location* location, char* name, int x, int y) {
	location->name = name;
	location->x = x;
	location->y = y;
	location->tmpCost = NO_COMPUTED_COST;
	addFilledLocation(locationList, location);
}

void addFilledLocation(LocationList* locationList, Location* location) {
    unsigned char size = locationList->size;
	if (size < MAX_LOCATION) {
	    locationList->locations[size] = location;
	    locationList->size++;
		locationList->count++;
	}
	else {
		writeError(TOO_MUCH_LOCATIONS);
    }
}

void removeLocation(LocationList* locationList, Location* locationToRemove) {
	int i;
    unsigned char size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		if (locationEquals(location, locationToRemove)) {
			locationList->count--;
			return;
		}
	}
}

Location* findLocationByName(LocationList* locationList, char* locationName) {
	int i;
	int size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		if (stringEquals(locationName, location->name)) {
			return location;
		}
	}
	return NULL;
}

BOOL containsLocation(LocationList* locationList, Location* locationToFind) {
	int i;
	int size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		if (locationEquals(location, locationToFind)) {
			return TRUE;
		}
	}
	return FALSE;
}

Location* getLocation(LocationList* locationList, int index) {
    return locationList->locations[index];
}

int getLocationCount(LocationList* locationList) {
    return locationList->size;
}

void printLocationList(OutputStream* outputStream, char* locationListName, LocationList* locationList) {
	int i;
	int size = locationList->size;
	appendKeyAndName(outputStream, "LocationList:", locationListName);
	appendStringAndDec(outputStream, ", size=", locationList->size);
	println(outputStream);	
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		printLocation(location, outputStream);
	}
}
