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
Location* getNearestLocation(LocationList* locationList, float x, float y, float maxDistance);

/**
 * Extract in the list the location with the min cost (tmp value). 
 * @param locationList the pointer on the struct (POO Programming)
 */
Location* extractMinCostLocation(LocationList* locationList);

/**
 * Extract the tmp Cost in Location (used to find the best path)
 */
float getComputedCost(Location* location);

/**
 * In lots of situation, the linked list of location does not end after the end Location, and it could raises some problem, so 
 * cutLocationLinkedList(A->D->E->F, E) => A->D->E
 */
void cutLocationLinkedList(Location* location, Location* endLocation);

#endif

