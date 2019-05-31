#ifndef GOLDENIUM_2019_H
#define GOLDENIUM_2019_H

#include <stdbool.h>

#include "../../../common/pwm/servo/servoList.h"
#include "../../../drivers/tof/tofList.h"

#define GOLDENIUM_2019_SCAN_RETRY_COUNT                2

bool fork2019PrepareTakeGoldenium(ServoList* servoList, unsigned int leftRight);

/**
 * All actions to take a Goldenium.
 * @param servoList
 */
bool fork2019TakeGoldenium(ServoList* servoList, TofSensorList* tofSensorList, unsigned int leftRight);

/**
 * All actions to release a Goldenium.
 */
bool fork2019DropGoldenium(ServoList* servoList, unsigned int leftRight);

#endif