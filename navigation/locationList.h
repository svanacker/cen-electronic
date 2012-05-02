#ifndef LOCATION_LIST_H
#define LOCATION_LIST_H

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
 * Add a location to the list.
 * @param location the location to add to the list
 */
void addGameStrategy(LocationList* locationList, Location* location, char* name, int x, int y);

/**
 * Get the location at index.
 */
Location* getLocation(LocationList* locationList, int index);

/**
 * Get the count of locations.
 */
int getLocationCount(LocationList* locationList);

#endif
