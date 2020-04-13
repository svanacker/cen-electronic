#ifndef LIGHT_HOUSE_2020_CHECK_ROBOT_TOUCHED_H
#define LIGHT_HOUSE_2020_CHECK_ROBOT_TOUCHED_H

#include <stdbool.h>

#include "lightHouse2020.h"

#include "../../../drivers/tof/tofList.h"

// DISTANCE
#define LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MIN                         45
#define LIGHT_HOUSE_2020_ROBOT_TOUCH_DISTANCE_MAX                        100

// CHECK / THRESHOLD
#define LIGHT_HOUSE_2020_ROBOT_TOUCH_THRESHOLD_COUNT                      5
#define LIGHT_HOUSE_2020_ROBOT_TOUCH_MISSED_DECREMENT_VALUE               2

/**
 * Check if the robot was touched, and update the state if it was the case.
 * @param lightHouse
 */
void checkLightHouse2020RobotTouched(LightHouse2020* lightHouse);

#endif
