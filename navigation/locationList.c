#include "locationList.h"
#include "location.h"

#include "../common/error/error.h"

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

Location* getLocation(LocationList* locationList, int index) {
    return locationList->locations[index];
}

int getLocationCount(LocationList* locationList) {
    return locationList->size;
}
