#ifndef LIGHT_HOUSE_2020_CHECK_ROBOT_PLACED_H
#define LIGHT_HOUSE_2020_CHECK_ROBOT_PLACED_H

#include <stdbool.h>

#include "lightHouse2020.h"

#include "../../../drivers/tof/tofList.h"

// DISTANCE
#define LIGHT_HOUSE_2020_ROBOT_PLACED_DISTANCE_MIN                      10
#define LIGHT_HOUSE_2020_ROBOT_PLACED_DISTANCE_MAX                      30

// CHECK / THRESHOLD
#define LIGHT_HOUSE_2020_ROBOT_PLACED_THRESHOLD_COUNT                    5
#define LIGHT_HOUSE_2020_ROBOT_PLACED_MISSED_DECREMENT_VALUE             2

// RELEASE TRY COUNT 
#define LIGHT_HOUSE_2020_RELEASE_TRY_COUNT                                 2

void checkLightHouse2020RobotPlaced(LightHouse2020* lightHouse);

#endif
