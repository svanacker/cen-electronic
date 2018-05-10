#ifndef STRATEGY_ACTION_2018_H
#define STRATEGY_ACTION_2018_H

#include <stdbool.h>

// ACTION TIME TO ACHIEVE

#define ACTION_TIME_NO_ACTION                                         0.0f

#define ACTION_SWITCH_TIME_TO_ACHIEVE                                 5.0f

#define ACTION_DISTRIBUTOR_1_TIME_TO_ACHIEVE                          30.0f

#define ACTION_BEE_TIME_TO_ACHIEVE                                    5.0f

#define ACTION_DISTRIBUTOR_2_TIME_TO_ACHIEVE                          30.0f

// SWITCH

bool switch2018On(int* context);

// DISTRIBUTORS

bool distributor1_2018(int* context);

bool distributor2_2018(int* context);

bool garbageRelease_2018(int* context);

// BEE

bool bee2018(int* context);

#endif

