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

// Angles
#define     ANGLE_DECI_DEG_0             0x0000
#define     ANGLE_DECI_DEG_30            0x012C
#define     ANGLE_DECI_DEG_45            0x01C2
#define     ANGLE_DECI_DEG_60            0x0258
#define     ANGLE_DECI_DEG_90            0x0384
#define     ANGLE_DECI_DEG_180           0x0708
#define     ANGLE_DECI_DEG_225           0x08CA

#define     ANGLE_DECI_DEG_300           0x0BB8
#define     ANGLE_DECI_DEG_270           0x0A8C

#define BIG_ROBOT_START_AREA                                                "BSTA"
#define BIG_ROBOT_START_AREA_X                                                 800
#define BIG_ROBOT_START_AREA_Y                                                 152
#define BIG_ROBOT_START_AREA_ANGLE_DECI_DEG                                      0

#define SMALL_ROBOT_START_AREA                                              "SSTA"
#define SMALL_ROBOT_START_AREA_X                                               600
#define SMALL_ROBOT_START_AREA_Y                                               370
#define SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG                    ANGLE_DECI_DEG_90

// Accelerator (SMALL ROBOT)
#define ACCELERATOR_FRONT                                                     "ACCE"
#define ACCELERATOR_FRONT_X                                                     200
#define ACCELERATOR_FRONT_Y                                                    1700
#define ACCELERATOR_FRONT_DECI_DEG                                ANGLE_DECI_DEG_90

// Accelerator Drop Zone (BIG ROBOT)
#define ACCELERATOR_DROP                                                     "DROP"
#define ACCELERATOR_DROP_X                                                     140
#define ACCELERATOR_DROP_Y                                                    1850
#define ACCELERATOR_DROP_DECI_DEG                               ANGLE_DECI_DEG_180

// Goldenium (SMALL ROBOT)
#define GOLDENIUM_FRONT                                                     "GOLD"
#define GOLDENIUM_FRONT_X                                                     130
#define GOLDENIUM_FRONT_Y                                                    2275
#define GOLDENIUM_FRONT_ANGLE_DECI_DEG                         ANGLE_DECI_DEG_180

// Weighing Machine FRONT
#define WEIGHING_MACHINE_FRONT                                              "WMF"
#define WEIGHING_MACHINE_FRONT_X                                            1200
#define WEIGHING_MACHINE_FRONT_Y                                            1300
#define WEIGHING_MACHINE_FRONT_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

// Weighing Machine DROP
#define WEIGHING_MACHINE_DROP                                              "WMD"
#define WEIGHING_MACHINE_DROP_X                                            1500
#define WEIGHING_MACHINE_DROP_Y                                            1300
#define WEIGHING_MACHINE_DROP_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

// Chaos Zone Front
#define CHAOS_ZONE_FRONT                                                   "CZFR"
#define CHAOS_ZONE_FRONT_X                                                  1250
#define CHAOS_ZONE_FRONT_Y                                                  1200
#define CHAOS_ZONE_FRONT_ANGLE_DECI_DEG                       ANGLE_DECI_DEG_225

// Redium Drop Zone
#define REDIUM_DROP_ZONE                                                   "RDRZ"
#define REDIUM_DROP_ZONE_X                                                   550
#define REDIUM_DROP_ZONE_Y                                                   350
#define REDIUM_DROP_ZONE_ANGLE_DECI_DEG                       ANGLE_DECI_DEG_225


// Key Point to be able to go from BigDistributor to Accelerator Drop Zone
#define KEY_POINT_1                                                        "KEP1"
#define KEY_POINT_1_X                                                       800
#define KEY_POINT_1_Y                                                       1500
#define KEY_POINT_1_ANGLE_DECI_DEG                            ANGLE_DECI_DEG_180

#define KEY_POINT_2                                                        "KEP2"
#define KEY_POINT_2_X                                                        800
#define KEY_POINT_2_Y                                                        600
#define KEY_POINT_2_ANGLE_DECI_DEG                              ANGLE_DECI_DEG_0

// BIG DISTRIBUTOR
#define BIG_DISTRIBUTOR_LINE_1                                            "BDL1"
#define BIG_DISTRIBUTOR_LINE_1_X                                            1450
#define BIG_DISTRIBUTOR_LINE_1_Y                                             525
#define BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG                     ANGLE_DECI_DEG_0

#define BIG_DISTRIBUTOR_LINE_2                                            "BDL2"
#define BIG_DISTRIBUTOR_LINE_2_X                        BIG_DISTRIBUTOR_LINE_1_X
#define BIG_DISTRIBUTOR_LINE_2_Y                  BIG_DISTRIBUTOR_LINE_1_Y + 200
#define BIG_DISTRIBUTOR_LINE_2_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

#define BIG_DISTRIBUTOR_LINE_3                                            "BDL3"
#define BIG_DISTRIBUTOR_LINE_3_X                        BIG_DISTRIBUTOR_LINE_1_X
#define BIG_DISTRIBUTOR_LINE_3_Y                  BIG_DISTRIBUTOR_LINE_2_Y + 200
#define BIG_DISTRIBUTOR_LINE_3_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

// Costs, base 1000.0f is about the cost for one meter in forward direction
#define DEFAULT_NAVIGATION_COST                                               400

// Paths

// Strategy 1 
// -> Small Robot

#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_COST                          1800.0f
#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CP1                           300.0f
#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CP2                           500.0f
#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_SPEED_FACTOR                  1.0f
#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_ACCELERATION_FACTOR           1.0f

#define ACCELERATOR_TO_GOLDENIUM_COST                                      500.0f
#define ACCELERATOR_TO_GOLDENIUM_CP1                                       50.0f
#define ACCELERATOR_TO_GOLDENIUM_CP2                                       300.0f
#define ACCELERATOR_TO_GOLDENIUM_SPEED_FACTOR                              0.5f
#define ACCELERATOR_TO_GOLDENIUM_ACCELERATION_FACTOR                       0.5f

#define GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_COST                           1500.0f
#define GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_CP1                            -400.0f
#define GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_CP2                            -200.0f
#define GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_SPEED_FACTOR                   1.0f
#define GOLDENIUM_TO_WEIGHING_MACHINE_FRONT_ACCELERATION_FACTOR            1.0f

#define WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_COST                200.0f
#define WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_CP1                 100.0f
#define WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_CP2                 100.0f
#define WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_SPEED_FACTOR        0.5f
#define WEIGHING_MACHINE_FRONT_TO_WEIGHING_MACHINE_DROP_ACCELERATION_FACTOR 0.5f

// -> Big Robot : Start Area -> Big Distributor Line 1
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_COST             1200.0f
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_CP1              250.0f
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_CP2              250.0f
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_SPEED_FACTOR     0.8f
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE_1_FRONT_ACCELERATION_FACTOR  0.8f

// -> Big Robot : Start Area -> Chaos Zone Front
#define BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_COST             1500.0f
#define BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_CP1              720.0f
#define BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_CP2              250.0f
#define BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_SPEED_FACTOR     1.0f
#define BIG_ROBOT_STARTAREA_TO_CHAOS_ZONE_FRONT_ACCELERATION_FACTOR 1.0f

// Chaos Zone Front -> Redium Drop Zone
#define CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_COST             900.0f
#define CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_CP1              200.0f
#define CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_CP2              200.0f
#define CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_SPEED_FACTOR          1.0f
#define CHAOS_ZONE_FRONT_TO_REDIUM_DROP_ZONE_ACCELERATION_FACTOR   1.0f

// Redium Drop Zone -> Key Point 1
#define REDIUM_DROP_ZONE_TO_KEY_POINT_1_COST                  1000.0f
#define REDIUM_DROP_ZONE_TO_KEY_POINT_1_CP1                   -200.0f
#define REDIUM_DROP_ZONE_TO_KEY_POINT_1_CP2                   -200.0f
#define REDIUM_DROP_ZONE_TO_KEY_POINT_1_SPEED_FACTOR          1.0f
#define REDIUM_DROP_ZONE_TO_KEY_POINT_1_ACCELERATION_FACTOR   1.0f

// Redium Drop Zone -> Key Point 2
#define REDIUM_DROP_ZONE_TO_KEY_POINT_2_COST                   400.0f
#define REDIUM_DROP_ZONE_TO_KEY_POINT_2_CP1                   -200.0f
#define REDIUM_DROP_ZONE_TO_KEY_POINT_2_CP2                   -300.0f
#define REDIUM_DROP_ZONE_TO_KEY_POINT_2_SPEED_FACTOR          1.0f
#define REDIUM_DROP_ZONE_TO_KEY_POINT_2_ACCELERATION_FACTOR   1.0f

// Key Point 2 -> BigDistributor Line 1
#define KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_COST                800.0f
#define KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_CP1                 250.0f
#define KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_CP2                 250.0f
#define KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_SPEED_FACTOR        1.0f
#define KEY_POINT_2_TO_BIGDISTRIBUTOR_LINE_1_FRONT_ACCELERATION_FACTOR 1.0f

// Big Distributor Line 1 <-> Key Point 1
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_COST                1000.0f
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_CP1                 -600.0f
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_CP2                 -250.0f
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_SPEED_FACTOR        1.0f
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR 1.0f

// Key Point 1 <-> Drop Zone
#define KEY_POINT_1_TO_ACCELERATOR_DROP_COST                1000.0f
#define KEY_POINT_1_TO_ACCELERATOR_DROP_CP1                 250.0f
#define KEY_POINT_1_TO_ACCELERATOR_DROP_CP2                 350.0f
#define KEY_POINT_1_TO_ACCELERATOR_DROP_SPEED_FACTOR        1.0f
#define KEY_POINT_1_TO_ACCELERATOR_DROP_ACCELERATION_FACTOR 1.0f

// Drop Zone <-> Key Point 1
#define ACCELERATOR_DROP_TO_KEY_POINT_1_COST                KEY_POINT_1_TO_ACCELERATOR_DROP_COST
#define ACCELERATOR_DROP_TO_KEY_POINT_1_CP1                 -350.0f
#define ACCELERATOR_DROP_TO_KEY_POINT_1_CP2                 -250.0f
#define ACCELERATOR_DROP_TO_KEY_POINT_1_SPEED_FACTOR        1.0f
#define ACCELERATOR_DROP_TO_KEY_POINT_1_ACCELERATION_FACTOR 1.0f

// Key Point 1 <-> BigDistributor Line 2
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_COST                1000.0f
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_CP1                 250.0f
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_CP2                 800.0f
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_SPEED_FACTOR        1.0f
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_ACCELERATION_FACTOR 1.0f

#define BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_COST                KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_2_FRONT_COST
#define BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_CP1                 -900.0f
#define BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_CP2                 -250.0f
#define BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_SPEED_FACTOR        1.0f
#define BIGDISTRIBUTOR_LINE2_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR 1.0f

// Key Point 1 <-> BigDistributor Line 3
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_COST                1000.0f
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_CP1                 250.0f
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_CP2                 200.0f
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_SPEED_FACTOR        1.0f
#define KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_ACCELERATION_FACTOR 1.0f

#define BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_COST                KEY_POINT_1_TO_BIGDISTRIBUTOR_LINE_3_FRONT_COST
#define BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_CP1                 -200.0f
#define BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_CP2                 -250.0f
#define BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_SPEED_FACTOR        1.0f
#define BIGDISTRIBUTOR_LINE_3_FRONT_TO_KEY_POINT_1_ACCELERATION_FACTOR 1.0f

// TIMING
#define ACCELERATOR_ARM_OFF_ACTION_TIME_TO_ACHIEVE                         0.0f
#define ACCELERATOR_ARM_ON_ACTION_TIME_TO_ACHIEVE                          0.0f

#define GOLDENIUM_TAKE_TIME_TO_ACHIEVE                                     3.0f
#define GOLDENIUM_DROP_TIME_TO_ACHIEVE                                     3.0f

#define CHAOS_TAKE_TIME_TO_ACHIEVE                                         0.0f
#define CHAOS_DROP_TIME_TO_ACHIEVE                                         0.0f

#define BIG_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE                        1.0f
#define BIG_DISTRIBUTOR_LINE_2_TAKE_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE
#define BIG_DISTRIBUTOR_LINE_3_TAKE_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_TAKE_TIME_TO_ACHIEVE

#define BIG_DISTRIBUTOR_LINE_1_MOVE_TIME_TO_ACHIEVE                        2.0f
#define BIG_DISTRIBUTOR_LINE_2_MOVE_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_MOVE_TIME_TO_ACHIEVE
#define BIG_DISTRIBUTOR_LINE_3_MOVE_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_MOVE_TIME_TO_ACHIEVE


#define BIG_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE                        1.0f
#define BIG_DISTRIBUTOR_LINE_2_DROP_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE
#define BIG_DISTRIBUTOR_LINE_3_DROP_TIME_TO_ACHIEVE                        BIG_DISTRIBUTOR_LINE_1_DROP_TIME_TO_ACHIEVE

/**
* Init all elements for 2019.
*/
void initStrategy2019(GameStrategyContext* gameStrategyContext);

/**
* Define the color and update strategy.
*/
void setColor2019(GameStrategyContext* gmeStrategyContext, enum TeamColor color);

#endif
