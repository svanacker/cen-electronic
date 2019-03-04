#ifndef STRATEGY_2019_H
#define STRATEGY_2019_H

#include "score2019.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/teamColor.h"

#include "../../motion/simple/simpleMotion.h"
#include "../../motion/extended/bsplineMotion.h"

#define STRATEGY_2019_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH        30
#define STRATEGY_2019_NAVIGATION_PATH_LIST_ARRAY_LENGTH            30
#define STRATEGY_2019_BIT_LIST_NAVIGATION_ARRAY_LENGTH             30

// Angles
#define     ANGLE_DECI_DEG_0             0x0000
#define     ANGLE_DECI_DEG_30            0x012C
#define     ANGLE_DECI_DEG_45            0x01C2
#define     ANGLE_DECI_DEG_60            0x0258
#define     ANGLE_DECI_DEG_90            0x0384
#define     ANGLE_DECI_DEG_180           0x0708
#define     ANGLE_DECI_DEG_300           0x0BB8
#define     ANGLE_DECI_DEG_270           0x0A8C

#define BIG_ROBOT_START_AREA                                                "BSTA"
#define BIG_ROBOT_START_AREA_X                                               160
#define BIG_ROBOT_START_AREA_Y                                               185
#define BIG_ROBOT_START_AREA_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_90

#define SMALL_ROBOT_START_AREA                                              "SSTA"
#define SMALL_ROBOT_START_AREA_X                                             160
#define SMALL_ROBOT_START_AREA_Y                                               185
#define SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_180


#define GOLDENIUM                                                           "GOLD"
#define GOLDENIUM_X                                                           180
#define GOLDENIUM_Y                                                          2225
#define BIG_DISTRIBUTOR_1_ANGLE_DECI_DEG                       ANGLE_DECI_DEG_180

// Costs
#define DEFAULT_NAVIGATION_COST                                    400

// Paths

// Strategy 1

#define STARTAREA_TO_ACCELERATOR_COST                                      DEFAULT_NAVIGATION_COST
#define STARTAREA_TO_ACCELERATOR_CP1                                       -100.0f
#define STARTAREA_TO_ACCELERATOR_CP2                                       -100.0f
#define STARTAREA_TO_ACCELERATOR_SPEED_FACTOR                              MOTION_SPEED_FACTOR_NORMAL
#define STARTAREA_TO_ACCELERATOR_ACCELERATION_FACTOR                       MOTION_ACCELERATION_FACTOR_NORMAL


/**
* Init all elements for 2019.
*/
void initStrategy2019(GameStrategyContext* gameStrategyContext);

/**
* Define the color and update strategy.
*/
void setColor2019(GameStrategyContext* gmeStrategyContext, enum TeamColor color);

#endif
