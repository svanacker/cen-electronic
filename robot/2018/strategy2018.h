#ifndef STRATEGY_2018_H
#define STRATEGY_2018_H

#include "../../robot/strategy/gameTarget.h"
#include "../../robot/match/teamColor.h"

#include "../../motion/simple/simpleMotion.h"

// Angles
#define     ANGLE_0             0x0000
#define     ANGLE_30            0x012C
#define     ANGLE_45            0x01C2
#define     ANGLE_60            0x0258
#define     ANGLE_90            0x0384
#define     ANGLE_180           0x0708
#define     ANGLE_300           0x0BB8
#define     ANGLE_270           0x0A8C

#define START_AREA                "startArea"
#define START_AREA_X                    170
#define START_AREA_Y                    170
#define START_AREA_ANGLE                ANGLE_180

#define DISTRIBUTOR_1                  "DIST_1"
#define DISTRIBUTOR_1_X                 800
#define DISTRIBUTOR_1_Y                 170
#define DISTRIBUTOR_1_ANGLE             ANGLE_300

#define DISTRIBUTOR_2                  "DIST_2"
#define DISTRIBUTOR_2_X                 1900
#define DISTRIBUTOR_2_Y                 2200
#define DISTRIBUTOR_2_ANGLE             ANGLE_30

#define BEE                             "BEE"
#define BEE_X                           2000
#define BEE_Y                           300

#define GARBAGE                         "GARBAGE"
#define GARBAGE_RELEASE_POINT_X         1650
#define GARBAGE_RELEASE_POINT_Y         1700
#define GARGAGE_RELEASE_POINT_ANGLE     ANGLE_0

#define SWITCH                         "SWITCH"
#define SWITCH_X                        200
#define SWITCH_Y                        1200
#define SWITCH_ANGLE                   ANGLE_180

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

#define STARTAREA_TO_SWITCH_COST                           DEFAULT_NAVIGATION_COST
#define STARTAREA_TO_SWITCH_COST_SPEED_FACTOR              MOTION_SPEED_FACTOR_NORMAL
#define STARTAREA_TO_SWITCH_COST_ACCELERATION_FACTOR       MOTION_ACCELERATION_FACTOR_NORMAL

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

/**
* Init all elements for 2018.
*/
void initStrategy2018(int strategyIndex);

/**
* Print
*/
void printStrategyAllDatas(OutputStream* outputStream);

/**
* Define the color and update strategy.
*/
void setColor(enum TeamColor color);

#endif
