#ifndef STRATEGY_2012_UTILS_H
#define STRATEGY_2012_UTILS_H

#include <stdbool.h>

#include "../../navigation/path.h"

bool isGreen();

/**
 * Change the location for color.
 */
void changeLocationsForColor();

void changePathsForColor();

int changeAngleForColor(int angle);

// ARM

void armLeftUp();

void armLeftDown();

void armRightUp();

void armRightDown();

#endif
