#ifndef LOCATION_LIST_COMPUTER_H
#define LOCATION_LIST_COMPUTER_H

#include "locationList.h"


/**
 * Returns the nearest location of the locationList, by comparing them with x and y.
 * @param locationList the pointer on the struct (POO Programming)
 * @param x the x value to compare with each location Point
 * @param y the y value to compare with each location Point
 * @return NULL if the locationList is empty, the nearest location (distance) from the locationList.
 */
Location* getNearestLocation(LocationList* locationList, float x, float y);

/**
 * Extract in the list the location with the min cost (tmp value). 
 * @param locationList the pointer on the struct (POO Programming)
 */
Location* extractMinCostLocation(LocationList* locationList);

/**
 * TODO
 */
float getTmpCost(Location* location);

#endif

