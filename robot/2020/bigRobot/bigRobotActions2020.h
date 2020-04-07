#ifndef BIG_ROBOT_ACTIONS_2020_H
#define BIG_ROBOT_ACTIONS_2020_H

#include <stdbool.h>

// HOOK

bool bigRobotPrepareFloorCups(int* context);

bool bigRobotLockFloorCups(int* context);

bool bigRobotReleaseCups(int* context);

// HOOK

bool bigRobotPrepareHook(int* context);

bool bigRobotTakeCups(int* context);

bool bigRobotDropCups(int* context);

#endif

