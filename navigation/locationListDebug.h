#ifndef LOCATION_LIST_DEBUG_H
#define LOCATION_LIST_DEBUG_H

#include <stdlib.h>

#include "locationList.h"

#include "../common/io/outputStream.h"

/**
 * Print the list of location as table.
 * @param outputStream the stream to show information
 * @param locationList the pointer on the struct (POO Programming)
 */
void printLocationListTable(OutputStream* outputStream, LocationList* locationList);

// TESTS DATA

void addLocationListTestsData(LocationList* locationList);

/**
 * Append the list of Name of location linked with next pointer (until the point is null).
 */
unsigned int appendLocationLinkedPath(OutputStream* outputStream, Location* startPoint);

#endif
