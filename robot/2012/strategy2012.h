#ifndef STRATEGY_2012_H
#define STRATEGY_2012_H

#include "../../robot/strategy/gameTarget.h"
#include "../../robot/match/teamColor.h"

#include "../../motion/simple/simpleMotion.h"

// #define     INCLUDE_HOMOLOGATION

// Strategies
#define STRATEGY_HOMOLOGATION    1
#define STRATEGY_TEST            3

#define     ANGLE_0                0x0000
#define     ANGLE_45            0x01C2
#define        ANGLE_80            0x0320
#define     ANGLE_90            0x0384
#define        ANGLE_100            0x03E8
#define        ANGLE_135            0x0546
#define        ANGLE_150            0x05DC
#define        ANGLE_180            0x0708
#define        ANGLE_NEG_45        0xFE3E
#define        ANGLE_NEG_65        0xFD76
#define        ANGLE_NEG_90        0xFC7C
#define        ANGLE_NEG_110        0xFBB4
#define        ANGLE_NEG_115        0xFB82
#define        ANGLE_NEG_135        0xFABA
#define     START_ANGLE            0x02A3

// LOCATIONS / TARGETS

// -> General Points
#define START_AREA                "startArea"
#define START_AREA_FRONT        "startAreaFront"
#define BULLION_1                "bullion1"
#define BOTTLE_1                "bottle1"
#define BOTTLE_2                "bottle2"
#define BOTTLE_2_FRONT            "bottle2Front"
#define CD_TAKE                    "cdTake"
#define DROP_ZONE_1                "dropZone1"
#define FRONT_OF_MAP_LOCATION    "frontOfMapLocation"

// -> Bullion1
#define BULLION_RIGHT_1            "bullionRight1"
#define BULLION_RIGHT_2            "bullionRight2"
#define BULLION_LEFT_1            "bullionLeft1"
#define BULLION_LEFT_2            "bullionLeft2"

// -> Opponent CD
#define OPPONENT_CD                "opponentCD"
#define BULLION_MIDDLE_2        "bullionMiddle2"

#define OBSTACLE_L1                "OL1"
#define OBSTACLE_L2                "OL2"
#define OBSTACLE_L3                "OL3"
#define OBSTACLE_L4                "OL4"
#define OBSTACLE_M1                "OM1"
#define OBSTACLE_M2                "OM2"
#define OBSTACLE_R1                "OR1"
#define OBSTACLE_R2                "OR2"
#define OBSTACLE_R3                "OR3"
#define OBSTACLE_R4                "OR4"


// CONSTANTS

#define     X_BOTTLE             0x0730

#define     X_LINTEL_LEFT        0x290

// Symetric
#define     X_LINTEL_RIGHT         2000 - X_LINTEL_LEFT

// COORDINATES
#define START_AREA_X                    170
#define START_AREA_Y                    170

#define START_AREA_FRONT_X                250
#define START_AREA_FRONT_Y                700

#define BULLION_1_X                        0x0370
#define BULLION_1_Y                        0x0156

#define BOTTLE_1_X                        0x0720 
#define BOTTLE_1_Y                        0x0290

#define BOTTLE_2_FRONT_X                0x05DC  
#define BOTTLE_2_FRONT_Y                0x0800

#define BOTTLE_2_X                        0x0740 
#define BOTTLE_2_Y                        0x0750

#define CD_TAKE_X                        0x05A8
#define CD_TAKE_Y                        0x02C8

#define DROP_ZONE_1_X                    GAMEBOARD_MIDDLE_WIDTH
#define DROP_ZONE_1_Y                    0x00D5

#define BULLION_LEFT_AND_RIGHT_Y        0x05A0

#define MAGIC_CONSTANT                    15
#define BULLION_RIGHT_1_X                (X_LINTEL_RIGHT + MAGIC_CONSTANT)
#define BULLION_RIGHT_1_Y                BULLION_LEFT_AND_RIGHT_Y

#define BULLION_LEFT_1_X                (X_LINTEL_LEFT + MAGIC_CONSTANT)
#define BULLION_LEFT_1_Y                BULLION_LEFT_AND_RIGHT_Y

#define FRONT_OF_MAP_LOCATION_X            0x01C2
#define FRONT_OF_MAP_LOCATION_Y            GAMEBOARD_MIDDLE_HEIGHT

#define BULLION_MIDDLE_2_X                GAMEBOARD_MIDDLE_WIDTH
#define BULLION_MIDDLE_2_Y                0x08E8

#define OBSTACLE_L_X                    500
#define OBSTACLE_M_X                    GAMEBOARD_MIDDLE_WIDTH
#define OBSTACLE_R_X                    (GAMEBOARD_WIDTH - OBSTACLE_L_X)

#define OBSTACLE_1_Y                    700
#define OBSTACLE_2_Y                    1200
#define OBSTACLE_3_Y                    (GAMEBOARD_HEIGHT - OBSTACLE_2_Y)
#define OBSTACLE_4_Y                    (GAMEBOARD_HEIGHT - OBSTACLE_1_Y)


// GAINS

#define BULLION_GAIN            3
#define BOTTLE_GAIN                5
#define CD_4_GAIN                4
#define BULLION_GAIN            3
#define OPPONENT_CD_GAIN        3

// COST : between 0 and 255

// -> General
#define START_AREA_TO_BULLION_1_COST                            100
#define BULLION_1_TO_BOTTLE_1_COST                                80
#define BOTTLE_1_TO_BOTTLE_2_FRONT_COST                            80
#define BOTTLE_2_FRONT_TO_BOTTLE_2_COST                            40
#define BOTTLE_2_TO_CD_COST                                        50
#define CD_TO_DROP_ZONE_1_COST                                    100
#define START_AREA_TO_FRONT_OF_MAP_COST                            150


// -> Bullion Right 1
#define BULLION_1_TO_BULLION_RIGHT_1_COST                        100
#define DROP_ZONE_1_TO_BULLION_RIGHT_1_COST                        100

// -> Bullion Left 1
#define DROP_ZONE_1_TO_BULLION_LEFT_1_COST                        100

#define AFTER_BULLION_LEFT_1_TO_START_AREA_CENTER_COST            50
#define START_AREA_CENTER_TO_START_AREA_DROP_ZONE_COST            80

// -> Opponent CD
#define FRONT_OF_MAP_TO_BULLION_MIDDLE_2_COST                    50
#define BULLION_MIDDLE_2_TO_BOTTLE_2_FRONT_COST                    40
#define BOTTLE_2_FRONT_TO_DROP_ZONE_1_COST                        150

// Navigation costs
#define DEFAULT_NAVIGATION_COST                                    400
#define OBSTACLE_L1_TO_L2_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_L2_TO_L3_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_L3_TO_L4_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_L4_TO_M2_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_M2_TO_R4_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_R4_TO_R3_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_R3_TO_R2_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_R2_TO_R1_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_R1_TO_M1_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_M1_TO_L1_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_L1_TO_L4_COST                                    (DEFAULT_NAVIGATION_COST * 2)
#define OBSTACLE_L4_TO_R4_COST                                    DEFAULT_NAVIGATION_COST
#define OBSTACLE_R4_TO_R1_COST                                    (DEFAULT_NAVIGATION_COST * 2)
#define OBSTACLE_R1_TO_L1_COST                                    DEFAULT_NAVIGATION_COST

#define BOTTLE1_TO_OR1_COST                                        DEFAULT_NAVIGATION_COST
#define BOTTLE2_TO_OR3_COST                                        DEFAULT_NAVIGATION_COST
#define DROPZONE1_TO_OL1_COST                                    DEFAULT_NAVIGATION_COST
#define DROPZONE1_TO_OM1_COST                                    DEFAULT_NAVIGATION_COST
#define DROPZONE1_TO_OR1_COST                                    DEFAULT_NAVIGATION_COST
#define BULLION1_TO_OL1_COST                                    DEFAULT_NAVIGATION_COST
#define BULLION1_TO_OM1_COST                                    DEFAULT_NAVIGATION_COST
#define BULLION1_TO_OR1_COST                                    DEFAULT_NAVIGATION_COST
#define BOTTLE2FRONT_TO_CD_COST                                    DEFAULT_NAVIGATION_COST
#define BOTTLE2FRONT_TO_CD_COST                                    DEFAULT_NAVIGATION_COST
#define STARTAREA_TO_L1_COST                                    DEFAULT_NAVIGATION_COST
#define OR3_TO_BULLIONRIGHT1_COST                                DEFAULT_NAVIGATION_COST
#define OL3_TO_BULLIONRIGHT1_COST                                DEFAULT_NAVIGATION_COST
// small cost for homologation
#define STARTAREA_TO_STARTAREA_FRONT_COST                        5
#define STARTAREA_FRONT_TO_OM1_COST                                5

// SPEED FACTOR : between 0 and 15
#define START_AREA_TO_BULLION_1_SPEED_FACTOR                    MOTION_SPEED_FACTOR_MAX
#define BULLION_1_TO_BOTTLE_1_SPEED_FACTOR                        MOTION_SPEED_FACTOR_MAX
#define BOTTLE_1_TO_BOTTLE_2_SPEED_FACTOR                        MOTION_SPEED_FACTOR_HIGH        
#define BOTTLE_2_TO_CD_SPEED_FACTOR                                MOTION_SPEED_FACTOR_NORMAL
#define CD_TO_DROP_ZONE_1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_HIGH
#define    START_AREA_TO_FRONT_OF_MAP_SPEED_FACTOR                    MOTION_SPEED_FACTOR_MAX

// -> Bullion Right 1
#define BULLION_1_TO_BULLION_RIGHT_1_SPEED_FACTOR                MOTION_SPEED_FACTOR_NORMAL
#define DROP_ZONE_1_TO_BULLION_RIGHT_1_SPEED_FACTOR                MOTION_SPEED_FACTOR_NORMAL

// -> Bullion Left 1
#define DROP_ZONE_1_TO_BULLION_LEFT_1_SPEED_FACTOR                MOTION_SPEED_FACTOR_NORMAL

// -> Opponent CD
#define FRONT_OF_MAP_TO_BULLION_MIDDLE_2_SPEED_FACTOR            MOTION_SPEED_FACTOR_NORMAL
#define BULLION_MIDDLE_2_TO_BOTTLE_2_FRONT_SPEED_FACTOR            MOTION_SPEED_FACTOR_NORMAL
#define BOTTLE_2_FRONT_TO_DROP_ZONE_1_SPEED_FACTOR                MOTION_SPEED_FACTOR_MAX

// Navigation speed factor
#define OBSTACLE_L1_TO_L2_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_L2_TO_L3_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_L3_TO_L4_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_L4_TO_M2_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_M2_TO_R4_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_R4_TO_R3_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_R3_TO_R2_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_R2_TO_R1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_R1_TO_M1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_M1_TO_L1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_L1_TO_L4_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_L4_TO_R4_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_R4_TO_R1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define OBSTACLE_R1_TO_L1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL

#define BOTTLE1_TO_OR1_SPEED_FACTOR                                MOTION_SPEED_FACTOR_NORMAL
#define BOTTLE2_TO_OR3_SPEED_FACTOR                                MOTION_SPEED_FACTOR_NORMAL
#define DROPZONE1_TO_OL1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define DROPZONE1_TO_OM1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define DROPZONE1_TO_OR1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define BULLION1_TO_OL1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define BULLION1_TO_OM1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define BULLION1_TO_OR1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define BOTTLE2FRONT_TO_CD_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define BOTTLE2FRONT_TO_CD_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define STARTAREA_TO_L1_SPEED_FACTOR                            MOTION_SPEED_FACTOR_NORMAL
#define STARTAREA_TO_STARTAREA_FRONT_SPEED_FACTOR                 MOTION_SPEED_FACTOR_NORMAL
#define STARTAREA_FRONT_TO_OM1_SPEED_FACTOR                     MOTION_SPEED_FACTOR_NORMAL
#define OR3_TO_BULLIONRIGHT1_SPEED_FACTOR                         MOTION_SPEED_FACTOR_NORMAL
#define OL3_TO_BULLIONRIGHT1_SPEED_FACTOR                         MOTION_SPEED_FACTOR_NORMAL

// ACCELERATION FACTOR : between 0 and 15
// -> General
#define START_AREA_TO_BULLION_1_ACCELERATION_FACTOR                MOTION_ACCELERATION_FACTOR_MAX
#define BULLION_1_TO_BOTTLE_1_ACCELERATION_FACTOR                MOTION_ACCELERATION_FACTOR_MAX
#define BOTTLE_1_TO_BOTTLE_2_ACCELERATION_FACTOR                MOTION_ACCELERATION_FACTOR_HIGH        
#define BOTTLE_2_TO_CD_ACCELERATION_FACTOR                        MOTION_ACCELERATION_FACTOR_LOW
#define CD_TO_DROP_ZONE_1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_HIGH
#define START_AREA_TO_FRONT_OF_MAP_ACCELERATION_FACTOR            MOTION_ACCELERATION_FACTOR_MAX

// -> Bullion Right 1
#define BULLION_1_TO_BULLION_RIGHT_1_ACCELERATION_FACTOR        MOTION_ACCELERATION_FACTOR_HIGH
#define DROP_ZONE_1_TO_BULLION_RIGHT_1_ACCELERATION_FACTOR        MOTION_ACCELERATION_FACTOR_HIGH

// -> Bullion Left 1
#define DROP_ZONE_1_TO_BULLION_LEFT_1_ACCELERATION_FACTOR        MOTION_ACCELERATION_FACTOR_HIGH

// -> Opponent CD
#define FRONT_OF_MAP_TO_BULLION_MIDDLE_2_ACCELERATION_FACTOR    MOTION_ACCELERATION_FACTOR_NORMAL
#define BULLION_MIDDLE_2_TO_BOTTLE_2_FRONT_ACCELERATION_FACTOR    MOTION_ACCELERATION_FACTOR_NORMAL
#define BOTTLE_2_FRONT_TO_DROP_ZONE_1_ACCELERATION_FACTOR        MOTION_ACCELERATION_FACTOR_MAX

// Navigation acceleration factor
#define OBSTACLE_L1_TO_L2_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_L2_TO_L3_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_L3_TO_L4_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_L4_TO_M2_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_M2_TO_R4_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_R4_TO_R3_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_R3_TO_R2_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_R2_TO_R1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_R1_TO_M1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_M1_TO_L1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_L1_TO_L4_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_L4_TO_R4_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_R4_TO_R1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define OBSTACLE_R1_TO_L1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL

#define BOTTLE1_TO_OR1_ACCELERATION_FACTOR                        MOTION_ACCELERATION_FACTOR_NORMAL
#define BOTTLE2_TO_OR3_ACCELERATION_FACTOR                        MOTION_ACCELERATION_FACTOR_NORMAL
#define DROPZONE1_TO_OL1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define DROPZONE1_TO_OM1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define DROPZONE1_TO_OR1_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define BULLION1_TO_OL1_ACCELERATION_FACTOR                        MOTION_ACCELERATION_FACTOR_NORMAL
#define BULLION1_TO_OM1_ACCELERATION_FACTOR                        MOTION_ACCELERATION_FACTOR_NORMAL
#define BULLION1_TO_OR1_ACCELERATION_FACTOR                        MOTION_ACCELERATION_FACTOR_NORMAL
#define BOTTLE2FRONT_TO_CD_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define BOTTLE2FRONT_TO_CD_ACCELERATION_FACTOR                    MOTION_ACCELERATION_FACTOR_NORMAL
#define STARTAREA_TO_L1_ACCELERATION_FACTOR                        MOTION_ACCELERATION_FACTOR_NORMAL
#define STARTAREA_TO_STARTAREA_FRONT_ACCELERATION_FACTOR         MOTION_ACCELERATION_FACTOR_NORMAL
#define STARTAREA_FRONT_TO_OM1_ACCELERATION_FACTOR                 MOTION_ACCELERATION_FACTOR_NORMAL
#define OR3_TO_BULLIONRIGHT1_ACCELERATION_FACTOR                 MOTION_ACCELERATION_FACTOR_NORMAL
#define OL3_TO_BULLIONRIGHT1_ACCELERATION_FACTOR                 MOTION_ACCELERATION_FACTOR_NORMAL

/**
 * Init all elements for 2012.
 */
void initStrategy2012(int strategyIndex);

/**
 * Print 
 */
void printStrategyAllDatas(OutputStream* outputStream);

/**
 * Define the color and update strategy.
 */
void setColor(TEAM_COLOR color);

#endif
