#ifndef LIGHT_HOUSE_2020_CHECK_ROBOT_LAUNCHED_H
#define LIGHT_HOUSE_2020_CHECK_ROBOT_LAUNCHED_H

#include <stdbool.h>

#include "lightHouse2020.h"

#include "../../../drivers/tof/tofList.h"

/**
 * Check if the light House must be launch, and update if it is the case.
 * @param lightHouse
 */
void checkLightHouse2020ToLaunch(LightHouse2020* lightHouse);

#endif
