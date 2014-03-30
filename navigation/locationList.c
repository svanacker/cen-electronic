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
}

bool isEmptyLocationList(LocationList* locationList) {
	return locationList->size == 0;
}

void reverseLocationList(LocationList* locationList) {
	int i;
	unsigned char size = locationList->size;
	for (i = 0; i < size / 2; i++) {
		int index1 = i;
		int index2 = size - i - 1;
		Location* locationTmp = locationList->locations[index1];
		
		locationList->locations[index1] = locationList->locations[index2];
		locationList->locations[index2] = locationTmp;
	}
}

void addLocation(LocationList* locationList, Location* location, char* name, int x, int y) {
	location->name = name;
	location->x = x;
	location->y = y;
	location->tmpCost = NO_COMPUTED_COST;
	location->tmpHandled = FALSE;
	addFilledLocation(locationList, location);
}

void addFilledLocation(LocationList* locationList, Location* location) {
    unsigned char size = locationList->size;
	if (size < MAX_LOCATION) {
	    locationList->locations[size] = location;
	    locationList->size++;
	}
	else {
		writeError(TOO_MUCH_LOCATIONS);
    }
}

Location* findLocationByName(LocationList* locationList, char* locationName) {
	int i;
	int size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		if (stringEquals(locationName, location->name)) {
			return location;
		}
	}
	return NULL;
}

bool containsLocation(LocationList* locationList, Location* locationToFind, bool handled) {
	if (locationToFind == NULL) {
		return FALSE;
	}	
	int i;
	int size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		if (location->tmpHandled != handled) {
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
   	return locationList->locations[index];
}

void removeFirstLocation(LocationList* locationList) {
	int size = locationList->size;
	if (size == 0) {
		return;
	}
	int i;
	for (i = 1; i < size; i++) {
		locationList->locations[i - 1] = locationList->locations[i];
	}
	size--;
	locationList->size = size;
}

int getLocationCount(LocationList* locationList) {
    return locationList->size;
}

// CLEAR


void clearLocationTmpInfo(LocationList* locationList) {
	int i;
	unsigned char size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		location->tmpCost = NO_COMPUTED_COST;
		location->tmpPreviousLocation = NULL;
		location->tmpHandled = FALSE;
	}
}


// DEBUG

void printLocationList(OutputStream* outputStream, char* locationListName, LocationList* locationList) {
	int i;
	int size = locationList->size;
	appendString(outputStream, locationListName);
	appendStringAndDec(outputStream, ", size=", locationList->size);
	println(outputStream);	
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];
		printLocation(outputStream, location);
	}
}
