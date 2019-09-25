#ifndef STRATEGY_2019_UTILS_H
#define STRATEGY_2019_UTILS_H

#include <stdbool.h>

#include "../../../navigation/navigation.h"
#include "../../../navigation/path.h"

#include "../../strategy/gameStrategyContext.h"

bool isViolet2019(GameStrategyContext* gameStrategyContext);

/**
 * Change the location for color.
 */
void changeLocationsForColor2019(GameStrategyContext* gameStrategyContext);

void changePathsForColor2019(GameStrategyContext* gameStrategyContext);

float changeAngleForColor2019(GameStrategyContext* gameStrategyContext, float angle);

#endif
