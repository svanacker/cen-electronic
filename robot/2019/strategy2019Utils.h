#ifndef STRATEGY_2019_UTILS_H
#define STRATEGY_2019_UTILS_H

#include <stdbool.h>

#include "../../navigation/navigation.h"
#include "../../navigation/path.h"

#include "../strategy/gameStrategyContext.h"

bool isViolet(GameStrategyContext* gameStrategyContext);

/**
 * Change the location for color.
 */
void changeLocationsForColor(GameStrategyContext* gameStrategyContext);

void changePathsForColor(GameStrategyContext* gameStrategyContext);

float changeAngleForColor(GameStrategyContext* gameStrategyContext, float angle);

#endif
