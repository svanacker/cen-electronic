#ifndef STRATEGY_2018_H
#define STRATEGY_2018_H

#include "score2018.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/teamColor.h"

#include "../../motion/simple/simpleMotion.h"
#include "../../motion/extended/bsplineMotion.h"

#define STRATEGY_2018_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH        30
#define STRATEGY_2018_NAVIGATION_PATH_LIST_ARRAY_LENGTH            30
#define STRATEGY_2018_BIT_LIST_NAVIGATION_ARRAY_LENGTH             30

// Angles
#define     ANGLE_DECI_DEG_0             0x0000
#define     ANGLE_DECI_DEG_30            0x012C
#define     ANGLE_DECI_DEG_45            0x01C2
#define     ANGLE_DECI_DEG_60            0x0258
#define     ANGLE_DECI_DEG_90            0x0384
#define     ANGLE_DECI_DEG_180           0x0708
#define     ANGLE_DECI_DEG_300           0x0BB8
#define     ANGLE_DECI_DEG_270           0x0A8C

#define START_AREA                                                "STA"
#define START_AREA_X                                               160
#define START_AREA_Y                                               185
#define START_AREA_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_270

#define SWITCH                                                    "SW"
#define SWITCH_X                                          START_AREA_X
#define SWITCH_Y                                                  1225
#define SWITCH_ANGLE_DECI_DEG                       ANGLE_DECI_DEG_270

#define DISTRIBUTOR_1                                            "D_1"
#define DISTRIBUTOR_1_X                                            830
#define DISTRIBUTOR_1_Y                                            210
#define DISTRIBUTOR_1_ANGLE_DECI_DEG                ANGLE_DECI_DEG_300

#define BEE_BORDER_Y_ALIGN                                       "B_Y"
#define BEE_BORDER_Y_ALIGN_X                                      1600
#define BEE_BORDER_Y_ALIGN_Y                                       154
#define BEE_BORDER_Y_ALIGN_ANGLE_DECI_DEG            ANGLE_DECI_DEG_90

#define BEE                                                        "B"
#define BEE_X                                                     1925
#define BEE_Y                                                      250
// We stop before to do an "action" of move !
// #define BEE_FRONT_X                                         BEE_X - 25
// #define BEE_FRONT_Y                                              BEE_Y

#define BEE_ANGLE_DECI_DEG                            ANGLE_DECI_DEG_0

#define DISTRIBUTOR_2_FRONT                                     "D2_F"
#define DISTRIBUTOR_2_FRONT_X                                     1500
#define DISTRIBUTOR_2_FRONT_Y                                     2300
#define DISTRIBUTOR_2_FRONT_ANGLE_DECI_DEG            ANGLE_DECI_DEG_0

#define DISTRIBUTOR_2                                             "D2"
#define DISTRIBUTOR_2_X                                           1810
#define DISTRIBUTOR_2_Y                                           2420
#define DISTRIBUTOR_2_ANGLE_DECI_DEG                 ANGLE_DECI_DEG_30

#define GARBAGE_FRONT                                             "GF"
#define GARBAGE_FRONT_POINT_X                                     1450
#define GARBAGE_FRONT_POINT_Y                                     1750
#define GARGAGE_FRONT_POINT_ANGLE_DECI_DEG            ANGLE_DECI_DEG_0

#define GARBAGE_RELEASE                                            "G"
#define GARBAGE_RELEASE_POINT_X                                   1700
#define GARBAGE_RELEASE_POINT_Y                                   1750
#define GARGAGE_RELEASE_POINT_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

// Costs
#define DEFAULT_NAVIGATION_COST                                    400

// Paths

// Strategy 1

#define STARTAREA_TO_SWITCH_COST                                      DEFAULT_NAVIGATION_COST
#define STARTAREA_TO_SWITCH_CP1                                       -100.0f
#define STARTAREA_TO_SWITCH_CP2                                       -100.0f
#define STARTAREA_TO_SWITCH_SPEED_FACTOR                              MOTION_SPEED_FACTOR_NORMAL
#define STARTAREA_TO_SWITCH_ACCELERATION_FACTOR                       MOTION_ACCELERATION_FACTOR_NORMAL

#define SWITCH_TO_DISTRIBUTOR_1_COST                                  DEFAULT_NAVIGATION_COST
#define SWITCH_TO_DISTRIBUTOR_1_CP1                                   600.0f
#define SWITCH_TO_DISTRIBUTOR_1_CP2                                   400.0f
#define SWITCH_TO_DISTRIBUTOR_1_SPEED_FACTOR                          MOTION_SPEED_FACTOR_NORMAL
#define SWITCH_TO_DISTRIBUTOR_1_ACCELERATION_FACTOR                   MOTION_ACCELERATION_FACTOR_NORMAL

#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST                      DEFAULT_NAVIGATION_COST
#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_CP1                       -1000.0f
#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_CP2                       -512.0f
#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST_SPEED_FACTOR         MOTION_SPEED_FACTOR_NORMAL
#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST_ACCELERATION_FACTOR  MOTION_ACCELERATION_FACTOR_NORMAL

#define BEE_BORDER_ALIGN_Y_TO_BEE_COST                                DEFAULT_NAVIGATION_COST
#define BEE_BORDER_ALIGN_Y_TO_BEE_CP1                                 80.0f
#define BEE_BORDER_ALIGN_Y_TO_BEE_CP2                                 16.0f
#define BEE_BORDER_ALIGN_Y_TO_BEE_SPEED_FACTOR                        MOTION_SPEED_FACTOR_LOW
#define BEE_BORDER_ALIGN_Y_TO_BEE_ACCELERATION_FACTOR                 MOTION_ACCELERATION_FACTOR_LOW

#define BEE_TO_DISTRIBUTOR_2_FRONT_COST                               DEFAULT_NAVIGATION_COST
#define BEE_TO_DISTRIBUTOR_2_FRONT_CP1                                -768.0f
#define BEE_TO_DISTRIBUTOR_2_FRONT_CP2                                -128.0f
#define BEE_TO_DISTRIBUTOR_2_FRONT_SPEED_FACTOR                       MOTION_SPEED_FACTOR_NORMAL
#define BEE_TO_DISTRIBUTOR_2_FRONT_ACCELERATION_FACTOR                MOTION_ACCELERATION_FACTOR_NORMAL

#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_COST                     DEFAULT_NAVIGATION_COST
#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_CP1                      128.0f
#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_CP2                      128.0f
#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_SPEED_FACTOR             MOTION_SPEED_FACTOR_NORMAL
#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_ACCELERATION_FACTOR      MOTION_ACCELERATION_FACTOR_NORMAL

#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_COST                           DEFAULT_NAVIGATION_COST
#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_CP1                            -512.0f
#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_CP2                            -128.0f
#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_SPEED_FACTOR                   MOTION_SPEED_FACTOR_NORMAL
#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_ACCELERATION_FACTOR            MOTION_ACCELERATION_FACTOR_NORMAL

#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_COST                         DEFAULT_NAVIGATION_COST
#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_CP1                          128.0f
#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_CP2                          128.0f
#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_SPEED_FACTOR                 MOTION_SPEED_FACTOR_NORMAL
#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_ACCELERATION_FACTOR          MOTION_ACCELERATION_FACTOR_NORMAL
/**
* Init all elements for 2018.
*/
void initStrategy2018(GameStrategyContext* gameStrategyContext);

/**
* Define the color and update strategy.
*/
void setColor2018(GameStrategyContext* gmeStrategyContext, enum TeamColor color);

#endif
