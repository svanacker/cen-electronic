#ifndef LOCATION_LIST_H
#define LOCATION_LIST_H

#include "../common/commons.h"
#include "../common/io/outputStream.h"

#include "location.h"

/** The max limit of location count. */
#define MAX_LOCATION 	 	20

/**
 * Tre struct defining a list of locations.
 */
typedef struct {
    /** An array of pointer on locations. */
    Location* locations[MAX_LOCATION];
    /** the size of the list. */
    unsigned char size;
} LocationList;

/**
 * Clear the location list.
 */
void clearLocationList(LocationList* locationList);

/**
 * Clear the costs and previous of each location of the list.
 */
void clearLocationTmpInfo(LocationList* locationList);

/**
 * Clear the previous information of each location of the list.
 */
void clearPrevious(LocationList* locationList);

/**
 * Add all location to the list.
 */
void addLocationList(LocationList* targetLocationList, LocationList* sourceLocationList);

/** 
 * Reverse the location list. 
 */
void reverseLocationList(LocationList* locationList);

/**
 * Returns if the list is empty.
 */
BOOL isEmptyLocationList(LocationList* locationList);


/**
 * Add a location to the list.
 * @param location the location to add to the list
 */
void addLocation(LocationList* locationList, Location* location, char* name, int x, int y);

/**
 * Add an already filled location (name, x, y).
 */
void addFilledLocation(LocationList* locationList, Location* location);

/**
 * Remove a location to the list.
 * @param locationList the list in which we remove
 * @param locationToRemove the location to remove
 */
void removeLocation(LocationList* locationList, Location* locationToRemove);

/**
 * Remove first location of the list.
 */
void removeFirstLocation(LocationList* locationList);

/**
 * Get the location at index.
 */
Location* getLocation(LocationList* locationList, int index);

/**
 * Find the location by the name.
 * @param locationList the list in which we search the location with the specified name
 * @param locationName the name of location which is searched
 */
Location* findLocationByName(LocationList* locationList, char* locationName);

/**
 * Returns TRUE if the locationList contains the specified location.
 */
BOOL containsLocation(LocationList* locationList, Location* location, BOOL handled);

/**
 * Get the count of locations.
 */
int getLocationCount(LocationList* locationList);

Location* getNearestLocation(LocationList* locationList, int x, int y);

// DEBUG

/**
 * Print on the outputStream the location.
 */
void printLocationList(OutputStream* outputStream, char* locationListName, LocationList* locationList);

#endif
