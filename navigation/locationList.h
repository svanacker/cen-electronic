#ifndef LOCATION_LIST_H
#define LOCATION_LIST_H

#include <stdlib.h>

#include "location.h"

#include "../common/io/outputStream.h"

/**
 * The struct defining a list of locations.
 */
typedef struct {
    /** An array of pointer on locations. */
    Location(*locations)[];
    /** the size of the list. */
    unsigned int size;
    /** the max size of the list. */
    unsigned int maxSize;
} LocationList;

/**
 * Initializes the List of location by allocating an array of location.
 */
void initLocationList(LocationList* locationList, Location(*locationListArray)[], unsigned int locationListSize);

/**
 * Initialize a Location object with name and coordinates.
 * @param name the name of the point
 * @param x the x coordinates of the location point
 * @param y the x coordinates of the location point
 */
void initLocation(Location* location, char* name, char* label, float x, float y);

/**
 * Clear the location list.
 * @param locationList the pointer on the struct (POO Programming)
 */
void clearLocationList(LocationList* locationList);

/**
 * Clear the costs and previous of each location of the list.
 * @param locationList the pointer on the struct (POO Programming)
 */
void clearLocationTmpInfo(LocationList* locationList);

/**
 * Returns if the list is empty.
 * @param locationList the pointer on the struct (POO Programming)
 */
bool isEmptyLocationList(LocationList* locationList);

/**
 * Add a location to the list, but with a pointer on a string
 * @param locationList the pointer on the struct (POO Programming)
 */
Location* addNamedLocation(LocationList* locationList, char* name, char* label, float x, float y);

/**
* Add a location to the list, but with a char pointer structure.
* @param locationList the pointer on the struct (POO Programming)
*/
Location* addLocation(LocationList* locationList, FixedCharArray* name, char* label, float x, float y);

/**
 * Copy the location from the source to the target location, by copying all fields by value.
 * @param source the source location
 * @param target the target location
 */
void copyLocation(Location* sourceLocation, Location* targetLocation);

/**
 * Remove first location of the list.
 */
void removeFirstLocation(LocationList* locationList);

/**
 * Get the location at index.
 * @param locationList the pointer on the struct (POO Programming)
 * @param index index of the location
 */
Location* getLocation(LocationList* locationList, unsigned int index);

/**
 * TODO
 */
Location* findLocationByStringName(LocationList* locationList, char* name);

/**
 * Find the location by the name.
 * @param locationList the list in which we search the location with the specified name
 * @param locationName the name of location which is searched
 */
Location* findLocationByName(LocationList* locationList, FixedCharArray* locationName);

/**
 * Returns true if the locationList contains the specified location.
 */
bool containsLocation(LocationList* locationList, Location* location, bool handled);

/**
 * Get the count of locations.
 * @param locationList the pointer on the struct (POO Programming)
 * @return the count of locations
 */
unsigned int getLocationCount(LocationList* locationList);

/**
* Get how many location in the collection which are not already handled.
*/
unsigned int getLocationNotHandledCount(LocationList* locationList);

#endif
