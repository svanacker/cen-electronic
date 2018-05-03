#ifndef STRATEGY_2012_UTILS_H
#define STRATEGY_2012_UTILS_H

#include <stdbool.h>

#include "../../navigation/navigation.h"
#include "../../navigation/path.h"

bool isGreen();

/**
 * Change the location for color.
 */
void changeLocationsForColor(Navigation* navigation);

void changePathsForColor(Navigation* navigation);

float changeAngleForColor(float angle);

// ARM

void armLeftUp();

void armLeftDown();

void armRightUp();

void armRightDown();

#endif
