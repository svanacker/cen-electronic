#ifndef BIG_ROBOT_ACTIONS_2020_H
#define BIG_ROBOT_ACTIONS_2020_H

#include <stdbool.h>

// LIGHT HOUSE LATERAL ARM

bool lightHouseLateralArmOn(int* context);
bool lightHouseLateralArmOff(int* context);

// HOOK

bool bigRobotPrepareFloorCups(int* context);

bool bigRobotPrepareFloorCenterCups(int* context);

bool bigRobotLockFloorCups(int* context);

bool bigRobotReleaseCups(int* context);

// REEF

bool bigRobotPrepareHook(int* context);

bool bigRobotTakeCups(int* context);

bool bigRobotDropCupsPhase1(int* context);

bool bigRobotDropCupsPhase2(int* context);


#endif

