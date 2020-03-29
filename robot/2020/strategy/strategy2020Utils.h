#ifndef STRATEGY_2020_UTILS_H
#define STRATEGY_2020_UTILS_H

#include <stdbool.h>

#include "../../../navigation/navigation.h"
#include "../../../navigation/path.h"

#include "../../strategy/gameStrategyContext.h"

bool isBlue2020(GameStrategyContext* gameStrategyContext);
bool isYellow2020(GameStrategyContext* gameStrategyContext);

/**
 * Change the location for color.
 */
void changeLocationsForColor(GameStrategyContext* gameStrategyContext);

float changeAngleForColor(GameStrategyContext* gameStrategyContext, float angle);

#endif
