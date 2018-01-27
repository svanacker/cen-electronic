#ifndef LOCATION_LIST_H
#define LOCATION_LIST_H

#include <stdlib.h>

#include "location.h"

#include "../common/io/outputStream.h"

/**
 * Tre struct defining a list of locations.
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
void initLocation(Location* location, char* name, int x, int y);

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
 * Clear the previous information of each location of the list.
 * @param locationList the pointer on the struct (POO Programming)
 */
void clearPrevious(LocationList* locationList);

/**
 * Add all location to the list.
 */
void addLocationList(LocationList* targetLocationList, LocationList* sourceLocationList);

/**
 * Returns if the list is empty.
 * @param locationList the pointer on the struct (POO Programming)
 */
bool isEmptyLocationList(LocationList* locationList);

/**
 * Add a location to the list, but with a pointer on a string
 * @param locationList the pointer on the struct (POO Programming)
 */
Location* addNamedLocation(LocationList* locationList, char* name, int x, int y);

/**
* Add a location to the list, but with a char pointer structure.
* @param locationList the pointer on the struct (POO Programming)
*/
Location* addLocation(LocationList* locationList, const FixedCharArray* s, int x, int y);

/**
 * Copy the location from the source to the target location, by copying all fields by value.
 * @param source the source location
 * @param target the target location
 */
void copyLocation(Location* sourceLocation, Location* targetLocation);

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
Location* findLocationByName(LocationList* locationList, const FixedCharArray* locationName);

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
 * Returns the nearest location of the locationList, by comparing them with x and y.
 * @param locationList the pointer on the struct (POO Programming)
 * @param x the x value to compare with each location Point
 * @param y the y value to compare with each location Point
 * @return NULL if the locationList is empty, the nearest location (distance) from the locationList.
 */
Location* getNearestLocation(LocationList* locationList, int x, int y);

// DEBUG

/**
* Print the list of location as table.
* @param outputStream the stream to show information
* @param locationList the pointer on the struct (POO Programming)
*/
void printLocationListTable(OutputStream* outputStream, LocationList* locationList);

/**
 * TODO:
 */
void printLocationLinkedPath(OutputStream* outputStream, Location* startPoint);

// TESTS DATA

void addLocationListTestsData(LocationList* locationList);

#endif
