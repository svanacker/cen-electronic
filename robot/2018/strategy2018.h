#ifndef STRATEGY_2018_H
#define STRATEGY_2018_H

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/match/teamColor.h"

#include "../../motion/simple/simpleMotion.h"

#define STRATEGY_2018_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH        30
#define STRATEGY_2018_NAVIGATION_PATH_LIST_ARRAY_LENGTH            30
#define STRATEGY_2018_BIT_LIST_NAVIGATION_ARRAY_LENGTH             30

// Angles
#define     ANGLE_0             0x0000
#define     ANGLE_30            0x012C
#define     ANGLE_45            0x01C2
#define     ANGLE_60            0x0258
#define     ANGLE_90            0x0384
#define     ANGLE_180           0x0708
#define     ANGLE_300           0x0BB8
#define     ANGLE_270           0x0A8C

#define START_AREA                     "START"
#define START_AREA_X                    160
#define START_AREA_Y                    225
#define START_AREA_ANGLE                ANGLE_180

#define SWITCH                         "SWITCH"
#define SWITCH_X                        195
#define SWITCH_Y                        848
#define SWITCH_ANGLE                   ANGLE_180

#define DISTRIBUTOR_1                  "DIST_1"
#define DISTRIBUTOR_1_X                 800
#define DISTRIBUTOR_1_Y                 170
#define DISTRIBUTOR_1_ANGLE             ANGLE_300

#define BEE_BORDER_Y_ALIGN              "BEE_Y"
#define BEE_BORDER_Y_ALIGN_Y            1700
#define BEE_BORDER_Y_ALIGN_X            154
#define BEE_BORDER_Y_ALIGN_ANGLE        ANGLE_90

#define BEE                             "BEE"
#define BEE_X                           1920
#define BEE_Y                           200
#define BEE_ANGLE                       ANGLE_0

#define DISTRIBUTOR_2_FRONT             "DIST_2_F"
#define DISTRIBUTOR_2_FRONT_X           1500
#define DISTRIBUTOR_2_FRONT_Y           2300
#define DISTRIBUTOR_2_FRONT_ANGLE       ANGLE_0

#define DISTRIBUTOR_2                  "DIST_2"
#define DISTRIBUTOR_2_X                 1900
#define DISTRIBUTOR_2_Y                 2200
#define DISTRIBUTOR_2_ANGLE             ANGLE_30

#define GARBAGE_FRONT                  "GARB_FRONT"
#define GARBAGE_FRONT_POINT_X          1450
#define GARBAGE_FRONT_POINT_Y          1750
#define GARGAGE_FRONT_POINT_ANGLE     ANGLE_0

#define GARBAGE_RELEASE                "GARBAGE"
#define GARBAGE_RELEASE_POINT_X         1700
#define GARBAGE_RELEASE_POINT_Y         1750
#define GARGAGE_RELEASE_POINT_ANGLE     ANGLE_0

/*
#define BUILDING_AREA                  "BUILDING_AREA"
#define BUILDING_AREA_X                100
#define BUILDING_AREA_Y                600

#define BUILDING_LEFT_1                 "BUILDING_LEFT_1"
#define BUILDING_LEFT_1_X               500
#define BUILDING_LEFT_1_Y               800

#define BUILDING_LEFT_2                 "BUILDING_LEFT_2"
#define BUILDING_LEFT_2_X               BUILDING_LEFT_1_X
#define BUILDING_LEFT_2_Y               GAMEBOARD_HEIGHT - BUILDING_LEFT_1_Y

#define BUILDING_MIDDLE_1               "BUILDING_MIDDLE_1"
#define BUILDING_MIDDLE_1_X             1200
#define BUILDING_MIDDLE_1_Y             200

#define BUILDING_MIDDLE_2               "BUILDING_MIDDLE_2"
#define BUILDING_MIDDLE_2_X             1200
#define BUILDING_MIDDLE_2_Y             GAMEBOARD_HEIGHT - BUILDING_MIDDLE_1_Y

#define BUILDING_RIGHT_1                 "BUILDING_RIGHT_1"
#define BUILDING_RIGHT_1_X              1500
#define BUILDING_RIGHT_1_Y              800

#define BUILDING_RIGHT_2                 "BUILDING_RIGHT_2"
#define BUILDING_RIGHT_2_X              1500
#define BUILDING_RIGHT_2_Y              GAMEBOARD_HEIGHT - BUILDING_MIDDLE_2_Y
*/

// Costs
#define DEFAULT_NAVIGATION_COST         400

// Paths

// Strategy 1

#define STARTAREA_TO_SWITCH_COST                                      DEFAULT_NAVIGATION_COST
#define STARTAREA_TO_SWITCH_CP1                                       0xFFF0
#define STARTAREA_TO_SWITCH_CP2                                       0xFFF0
#define STARTAREA_TO_SWITCH_SPEED_FACTOR                              MOTION_SPEED_FACTOR_NORMAL
#define STARTAREA_TO_SWITCH_ACCELERATION_FACTOR                       MOTION_ACCELERATION_FACTOR_NORMAL

#define SWITCH_TO_DISTRIBUTOR_1_COST                                  DEFAULT_NAVIGATION_COST
#define SWITCH_TO_DISTRIBUTOR_1_CP1                                   0x0258
#define SWITCH_TO_DISTRIBUTOR_1_CP2                                   0x0190
#define SWITCH_TO_DISTRIBUTOR_1_SPEED_FACTOR                          MOTION_SPEED_FACTOR_NORMAL
#define SWITCH_TO_DISTRIBUTOR_1_ACCELERATION_FACTOR                   MOTION_ACCELERATION_FACTOR_NORMAL

#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST                      DEFAULT_NAVIGATION_COST
#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_CP1                       0xFB80
#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_CP2                       0xFE00
#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST_SPEED_FACTOR         MOTION_SPEED_FACTOR_NORMAL
#define DISTRIBUTOR_1_TO_BEE_BORDER_ALIGN_Y_COST_ACCELERATION_FACTOR  MOTION_ACCELERATION_FACTOR_NORMAL

#define BEE_BORDER_ALIGN_Y_TO_BEE_COST                                DEFAULT_NAVIGATION_COST
#define BEE_BORDER_ALIGN_Y_TO_BEE_CP1                                 0x0050
#define BEE_BORDER_ALIGN_Y_TO_BEE_CP2                                 0x0010
#define BEE_BORDER_ALIGN_Y_TO_BEE_SPEED_FACTOR                        MOTION_SPEED_FACTOR_NORMAL
#define BEE_BORDER_ALIGN_Y_TO_BEE_ACCELERATION_FACTOR                 MOTION_ACCELERATION_FACTOR_NORMAL

#define BEE_TO_DISTRIBUTOR_2_FRONT_COST                               DEFAULT_NAVIGATION_COST
#define BEE_TO_DISTRIBUTOR_2_FRONT_CP1                                0xFFD0
#define BEE_TO_DISTRIBUTOR_2_FRONT_CP2                                0xFF80
#define BEE_TO_DISTRIBUTOR_2_FRONT_SPEED_FACTOR                       MOTION_SPEED_FACTOR_NORMAL
#define BEE_TO_DISTRIBUTOR_2_FRONT_ACCELERATION_FACTOR                MOTION_ACCELERATION_FACTOR_NORMAL

#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_COST                     DEFAULT_NAVIGATION_COST
#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_CP1                      0x0080
#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_CP2                      0x0080
#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_SPEED_FACTOR             MOTION_SPEED_FACTOR_NORMAL
#define DISTRIBUTOR_2_FRONT_TO_DISTRIBUTOR_2_ACCELERATION_FACTOR      MOTION_ACCELERATION_FACTOR_NORMAL

#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_COST                           DEFAULT_NAVIGATION_COST
#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_CP1                            0xFE00
#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_CP2                            0xFF80
#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_SPEED_FACTOR                   MOTION_SPEED_FACTOR_NORMAL
#define DISTRIBUTOR_2_TO_GARBAGE_FRONT_ACCELERATION_FACTOR            MOTION_ACCELERATION_FACTOR_NORMAL

#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_COST                         DEFAULT_NAVIGATION_COST
#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_CP1                          0x0080
#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_CP2                          0x0080
#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_SPEED_FACTOR                 MOTION_SPEED_FACTOR_NORMAL
#define GARBAGE_FRONT_TO_GARBAGE_RELEASE_ACCELERATION_FACTOR          MOTION_ACCELERATION_FACTOR_NORMAL


/*
#define STARTAREA_TO_DISTRIBUTOR_1_COST                    5 
#define STARTAREA_TO_DISTRIBUTOR_1_SPEED_FACTOR            MOTION_SPEED_FACTOR_NORMAL
#define STARTAREA_TO_DISTRIBUTOR_1_ACCELERATION_FACTOR     MOTION_ACCELERATION_FACTOR_NORMAL

#define DISTRIBUTOR_1_TO_BEE_COST                          DEFAULT_NAVIGATION_COST 
#define DISTRIBUTOR_1_TO_BEE_SPEED_FACTOR                  MOTION_SPEED_FACTOR_NORMAL
#define DISTRIBUTOR_1_TO_BEE__ACCELERATION_FACTOR          MOTION_ACCELERATION_FACTOR_NORMAL

#define BEE_TO_DISTRIBUTOR_2_COST                          DEFAULT_NAVIGATION_COST 
#define BEE_TO_DISTRIBUTOR_2_SPEED_FACTOR                  MOTION_SPEED_FACTOR_NORMAL
#define BEE_TO_DISTRIBUTOR_2__ACCELERATION_FACTOR          MOTION_ACCELERATION_FACTOR_NORMAL

#define BEE_TO_BUILDING_AREA_COST                          DEFAULT_NAVIGATION_COST 
#define BEE_TO_BUILDING_AREA_SPEED_FACTOR                  MOTION_SPEED_FACTOR_NORMAL
#define BEE_TO_BUILDING_AREA_ACCELERATION_FACTOR           MOTION_ACCELERATION_FACTOR_NORMAL

#define BUILDING_AREA_TO_SWITCH_COST                       DEFAULT_NAVIGATION_COST 
#define BUILDING_AREA_TO_SWITCH_SPEED_FACTOR               MOTION_SPEED_FACTOR_NORMAL
#define BUILDING_AREA_TO_SWITCH_ACCELERATION_FACTOR        MOTION_ACCELERATION_FACTOR_NORMAL

#define SWITCH_TO_DISTRIBUTOR_2_COST                       DEFAULT_NAVIGATION_COST 
#define SWITCH_TO_DISTRIBUTOR_2_SPEED_FACTOR               MOTION_SPEED_FACTOR_NORMAL
#define SWITCH_TO_DISTRIBUTOR_2_ACCELERATION_FACTOR        MOTION_ACCELERATION_FACTOR_NORMAL
*/

/**
* Init all elements for 2018.
*/
void initStrategy2018(GameStrategyContext* gmeStrategyContext, int strategyIndex);

/**
* Print
*/
void printStrategyAllDatas(GameStrategyContext* gmeStrategyContext, OutputStream* outputStream);

/**
* Define the color and update strategy.
*/
void setColor(GameStrategyContext* gmeStrategyContext, enum TeamColor color);

#endif
