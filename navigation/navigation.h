#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "location.h"
#include "locationList.h"
#include "path.h"

/**
 * Computes the path.
 * @param outLocationList the out parameter which is filled
 * @param start startPoint
 * @param end endPoint
 */
int getPath(LocationList* outLocationList, Location start, Location end);

#endif
