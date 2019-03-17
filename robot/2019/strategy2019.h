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
#define BIG_ROBOT_START_AREA_X                                                 750
#define BIG_ROBOT_START_AREA_Y                                                 160
#define BIG_ROBOT_START_AREA_ANGLE_DECI_DEG                      ANGLE_DECI_DEG_90

#define SMALL_ROBOT_START_AREA                                              "SSTA"
#define SMALL_ROBOT_START_AREA_X                                               450
#define SMALL_ROBOT_START_AREA_Y                                               160
#define SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG                    ANGLE_DECI_DEG_90

// Accelerator
#define ACCELERATOR_FRONT                                                     "ACC"
#define ACCELERATOR_FRONT_X                                                     160
#define ACCELERATOR_FRONT_Y                                                    1800
#define ACCELERATOR_FRONT_DECI_DEG                                ANGLE_DECI_DEG_90

// Accelerator Drop Zone
#define ACCELERATOR_DROP                                                     "DROP"
#define ACCELERATOR_DROP_X                                                     160
#define ACCELERATOR_DROP_Y                                                    2000
#define ACCELERATOR_DROP_DECI_DEG                               ANGLE_DECI_DEG_180

// Goldenium
#define GOLDENIUM_FRONT                                                     "GOLD"
#define GOLDENIUM_FRONT_X                                                     180
#define GOLDENIUM_FRONT_Y                                                    2225
#define GOLDENIUM_FRONT_ANGLE_DECI_DEG                         ANGLE_DECI_DEG_180

// Weighing Machine
#define WEIGHING_MACHINE_FRONT                                                "WM"
#define WEIGHING_MACHINE_X                                                    1500
#define WEIGHING_MACHINE_Y                                                    1350
#define WEIGHING_MACHINE_ANGLE_DECI_DEG                           ANGLE_DECI_DEG_0

// BIG DISTRIBUTOR
#define BIG_DISTRIBUTOR_LINE_1                                              "BDL1"
#define BIG_DISTRIBUTOR_LINE_1_X                                              1400
#define BIG_DISTRIBUTOR_LINE_1_Y                                               550
#define BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG                     ANGLE_DECI_DEG_0

#define BIG_DISTRIBUTOR_LINE_2                                              "BDL2"
#define BIG_DISTRIBUTOR_LINE_2_X                          BIG_DISTRIBUTOR_LINE_1_X
#define BIG_DISTRIBUTOR_LINE_2_Y                    BIG_DISTRIBUTOR_LINE_1_Y + 200
#define BIG_DISTRIBUTOR_LINE_2_ANGLE_DECI_DEG                     ANGLE_DECI_DEG_0

#define BIG_DISTRIBUTOR_LINE_3                                              "BDL2"
#define BIG_DISTRIBUTOR_LINE_3_X                          BIG_DISTRIBUTOR_LINE_1_X
#define BIG_DISTRIBUTOR_LINE_3_Y                    BIG_DISTRIBUTOR_LINE_2_Y + 200
#define BIG_DISTRIBUTOR_LINE_3_ANGLE_DECI_DEG                     ANGLE_DECI_DEG_0

// Costs
#define DEFAULT_NAVIGATION_COST                                               400

// Paths

// Strategy 1 
// -> Small Robot

#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_COST                          DEFAULT_NAVIGATION_COST
#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CP1                           100.0f
#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_CP2                           100.0f
#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_SPEED_FACTOR                  MOTION_SPEED_FACTOR_NORMAL
#define SMALL_ROBOT_STARTAREA_TO_ACCELERATOR_ACCELERATION_FACTOR           MOTION_ACCELERATION_FACTOR_NORMAL

#define ACCELERATOR_TO_GOLDENIUM_COST                                      DEFAULT_NAVIGATION_COST
#define ACCELERATOR_TO_GOLDENIUM_CP1                                       100.0f
#define ACCELERATOR_TO_GOLDENIUM_CP2                                       100.0f
#define ACCELERATOR_TO_GOLDENIUM_SPEED_FACTOR                              MOTION_SPEED_FACTOR_NORMAL
#define ACCELERATOR_TO_GOLDENIUM_ACCELERATION_FACTOR                       MOTION_ACCELERATION_FACTOR_NORMAL

#define GOLDENIUM_TO_WEIGHING_MACHINE_COST                                 DEFAULT_NAVIGATION_COST
#define GOLDENIUM_TO_WEIGHING_MACHINE_CP1                                  100.0f
#define GOLDENIUM_TO_WEIGHING_MACHINE_CP2                                  100.0f
#define GOLDENIUM_TO_WEIGHING_MACHINE_SPEED_FACTOR                         MOTION_SPEED_FACTOR_NORMAL
#define GOLDENIUM_TO_WEIGHING_MACHINE_ACCELERATION_FACTOR                  MOTION_ACCELERATION_FACTOR_NORMAL

// -> Big Robot
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_COST             DEFAULT_NAVIGATION_COST
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_CP1              100.0f
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_CP2              100.0f
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_SPEED_FACTOR     MOTION_SPEED_FACTOR_NORMAL
#define BIG_ROBOT_STARTAREA_TO_BIGDISTRIBUTOR_LINE1_FRONT_ACCELERATION_FACTOR           MOTION_ACCELERATION_FACTOR_NORMAL

// Big Distributor Line 1 <-> Drop Zone
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_COST                DEFAULT_NAVIGATION_COST
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_CP1                 100.0f
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_CP2                 100.0f
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_SPEED_FACTOR        MOTION_SPEED_FACTOR_NORMAL
#define BIGDISTRIBUTOR_LINE1_FRONT_TO_ACCELERATOR_DROP_ACCELERATION_FACTOR MOTION_ACCELERATION_FACTOR_NORMAL

// Big Distributor Line 2 <-> Drop Zone
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_COST                DEFAULT_NAVIGATION_COST
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_CP1                 100.0f
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_CP2                 100.0f
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_SPEED_FACTOR        MOTION_SPEED_FACTOR_NORMAL
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE2_FRONT_ACCELERATION_FACTOR MOTION_ACCELERATION_FACTOR_NORMAL

#define BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_COST                DEFAULT_NAVIGATION_COST
#define BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_CP1                 100.0f
#define BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_CP2                 100.0f
#define BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_SPEED_FACTOR        MOTION_SPEED_FACTOR_NORMAL
#define BIGDISTRIBUTOR_LINE2_FRONT_TO_ACCELERATOR_DROP_ACCELERATION_FACTOR MOTION_ACCELERATION_FACTOR_NORMAL

// Big Distributor Line 3 <-> Drop Zone

#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_COST                DEFAULT_NAVIGATION_COST
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_CP1                 100.0f
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_CP2                 100.0f
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_SPEED_FACTOR        MOTION_SPEED_FACTOR_NORMAL
#define ACCELERATOR_DROP_TO_BIGDISTRIBUTOR_LINE3_FRONT_ACCELERATION_FACTOR MOTION_ACCELERATION_FACTOR_NORMAL

#define BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_COST                DEFAULT_NAVIGATION_COST
#define BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_CP1                 100.0f
#define BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_CP2                 100.0f
#define BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_SPEED_FACTOR        MOTION_SPEED_FACTOR_NORMAL
#define BIGDISTRIBUTOR_LINE3_FRONT_TO_ACCELERATOR_DROP_ACCELERATION_FACTOR MOTION_ACCELERATION_FACTOR_NORMAL

// TIMING
#define ACCELERATOR_ACTION_TIME_TO_ACHIEVE                                 1.0f
#define GOLDENIUM_TAKE_TIME_TO_ACHIEVE                                     3.0f
#define GOLDENIUM_DROP_TIME_TO_ACHIEVE                                     3.0f


/**
* Init all elements for 2019.
*/
void initStrategy2019(GameStrategyContext* gameStrategyContext);

/**
* Define the color and update strategy.
*/
void setColor2019(GameStrategyContext* gmeStrategyContext, enum TeamColor color);

#endif
