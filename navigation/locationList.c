#include <stdlib.h>

#include "locationList.h"
#include "location.h"

#include "../common/2d/2d.h"

#include "../common/error/error.h"

#include "../common/io/outputStream.h"
#include "../common/io/printWriter.h"

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
		// It it's a set, we control if there is no doublon
		if (locationList->set) {
			// if the location already exists 
			if (containsLocation(locationList, location)) {
				// do nothing
				return;
			}
		}
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
			locationList->locations[i] = NULL;
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
	if (locationToFind == NULL) {
		return FALSE;
	}	
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

Location* getNearestLocation(LocationList* locationList, int x, int y) {
	Location* result = NULL;
	int i;
	int size = locationList->size;
	int min = MAX_COST;

	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		int distance = distanceBetweenPoints2((float) location->x, (float) location->y, (float) x, (float) y);
		if (distance < min) {
			min = distance;
			result = location;
		}
	}
	return result;
}

Location* getLocation(LocationList* locationList, int index) {
	// optimisation when there is no removed object => index is the same
	if (locationList->count == locationList->size) {
    	return locationList->locations[index];
	}
	else {
		int count;
		int i;
		int size = locationList->size;
		for (i = 0; i < size; i++) {
			Location* location = locationList->locations[i];
			// We can have hole because of "remove"
			if (location == NULL) {
				continue;
			}
			if (count == index) {
				return location;
			}
			count++;
		}
	}
	return NULL;
}

void removeFirstLocation(LocationList* locationList) {
	int i;
	int size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		locationList->locations[i] = NULL;
		locationList->count--;
	}
}

int getLocationCount(LocationList* locationList) {
    return locationList->count;
}

// CLEAR


void clearLocationTmpCostsAndPrevious(LocationList* locationList) {
	int i;
	unsigned char size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		// We can have hole because of "remove"
		if (location == NULL) {
			continue;
		}
		location->tmpCost = NO_COMPUTED_COST;
		location->tmpPreviousLocation = NULL;
	}
}


// DEBUG

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
		printLocation(outputStream, location);
	}
}
