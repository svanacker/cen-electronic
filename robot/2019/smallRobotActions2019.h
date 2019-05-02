#ifndef SMALL_ROBOT_ACTIONS_2019_H
#define SMALL_ROBOT_ACTIONS_2019_H

#include <stdbool.h>

bool acceleratorArmOn(int* context);

bool acceleratorArmOff(int* context);

bool goldeniumPrepareTake(int* context);

bool goldeniumTake(int* context);

bool goldeniumPrepareDrop(int* context);

bool goldeniumDrop(int* context);

#endif

