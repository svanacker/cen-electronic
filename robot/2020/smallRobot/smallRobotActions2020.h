#ifndef SMALL_ROBOT_ACTIONS_2020_H
#define SMALL_ROBOT_ACTIONS_2020_H

#include <stdbool.h>

// PREPARE

bool smallRobotHookUpAll(int* context);

// FLAG

bool lateralArmOn(int* context);

bool lateralArmOff(int* context);

// HOOK

bool smallRobotPrepareHook(int* context);

bool smallRobotTakeCups(int* context);

bool smallRobotDropCups(int* context);

#endif

