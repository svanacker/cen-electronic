#ifndef SMALL_ROBOT_ACTIONS_2020_H
#define SMALL_ROBOT_ACTIONS_2020_H

#include <stdbool.h>

// FLAG

bool lateralArmOn(int* context);

bool lateralArmOff(int* context);

// HOOK

bool prepareHook(int* context);

bool takeCups(int* context);

bool dropCups(int* context);

#endif

