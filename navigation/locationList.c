#include <stdlib.h>

#include "locationList.h"
#include "location.h"

#include "../common/error/error.h"
#include "../common/string/cenString.h"

void clearLocationList(LocationList* locationList) {
	locationList->size = 0;
}

BOOL isEmptyLocationList(LocationList* locationList) {
	return locationList->size == 0;
}

void addLocation(LocationList* locationList, Location* location, char* name, int x, int y) {
    unsigned char size = locationList->size;
	if (size < MAX_LOCATION) {
		location->name = name;
	    locationList->locations[size] = location;
	    locationList->size++;
	}
	else {
		writeError(TOO_MUCH_LOCATIONS);
    }
}

Location* findLocationByName(LocationList* locationList, char* locationName) {
	int i;
	for (i = 0; i < locationList->size; i++) {
		Location* location = locationList->locations[i];
		if (stringEquals(locationName, location->name)) {
			return location;
		}
	}
	return NULL;
}

Location* getLocation(LocationList* locationList, int index) {
    return locationList->locations[index];
}

int getLocationCount(LocationList* locationList) {
    return locationList->size;
}
