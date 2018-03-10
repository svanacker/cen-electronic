#ifndef STRATEGY_2018_UTILS_H
#define STRATEGY_2018_UTILS_H

#include <stdbool.h>

#include "../../navigation/path.h"

bool isGreen();

/**
 * Change the location for color.
 */
void changeLocationsForColor();

void changePathsForColor(void);

float changeAngleForColor(float angle);

#endif
