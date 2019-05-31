#ifndef COMMON_ROBOT_LOCATIONS_2019_H
#define COMMON_ROBOT_LOCATIONS_2019_H

#include <stdbool.h>

// Accelerator Drop Zone (BIG ROBOT & SMALL_ROBOT)
#define ACCELERATOR_DROP                                                     "DROP"
#define ACCELERATOR_DROP_LABEL                                               "Accelerator Drop"
#define ACCELERATOR_DROP_X                                                     100
#define ACCELERATOR_DROP_Y                                                    1990
#define ACCELERATOR_DROP_DECI_DEG                               ANGLE_DECI_DEG_180

// BIG DISTRIBUTOR
#define BIG_DISTRIBUTOR_LINE_1                                            "BDL1"
#define BIG_DISTRIBUTOR_LINE_1_LABEL                                      "Big Distributor Line 1"
#define BIG_DISTRIBUTOR_LINE_1_X                                            1480
#define BIG_DISTRIBUTOR_LINE_1_Y                                             550
#define BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG                     ANGLE_DECI_DEG_0

#define BIG_DISTRIBUTOR_LINE_2                                            "BDL2"
#define BIG_DISTRIBUTOR_LINE_2_LABEL                                      "Big Distributor Line 2"
#define BIG_DISTRIBUTOR_LINE_2_X                        BIG_DISTRIBUTOR_LINE_1_X
// We have a shift on the robot of 10 mm 
#define BIG_DISTRIBUTOR_LINE_2_Y                  BIG_DISTRIBUTOR_LINE_1_Y + 190
#define BIG_DISTRIBUTOR_LINE_2_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

#define BIG_DISTRIBUTOR_LINE_3                                            "BDL3"
#define BIG_DISTRIBUTOR_LINE_3_LABEL                                      "Big Distributor Line 3"
#define BIG_DISTRIBUTOR_LINE_3_X                        BIG_DISTRIBUTOR_LINE_1_X
#define BIG_DISTRIBUTOR_LINE_3_Y                  BIG_DISTRIBUTOR_LINE_2_Y + 200
#define BIG_DISTRIBUTOR_LINE_3_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

// Redium Greenium Front Drop
#define REDIUM_GREENIUM_FRONT_DROP                                        "RGFD"
#define REDIUM_GREENIUM_FRONT_DROP_LABEL                                  "Redium Greenium Front Drop"
#define REDIUM_GREENIUM_FRONT_DROP_X                                        600
#define REDIUM_GREENIUM_FRONT_DROP_Y                                        650
#define REDIUM_GREENIUM_FRONT_DROP_FROM_ANGLE_DECI             ANGLE_DECI_DEG_0
#define REDIUM_GREENIUM_FRONT_DROP_TO_ANGLE_DECI               -ANGLE_DECI_DEG_90

// Redium Greenium Drop Zone
#define REDIUM_GREENIUM_DROP_ZONE                                        "RGDZ"
#define REDIUM_GREENIUM_DROP_ZONE_LABEL                                  "Redium Greenium Drop Zone"
#define REDIUM_GREENIUM_DROP_X                                 REDIUM_GREENIUM_FRONT_DROP_X
#define REDIUM_GREENIUM_DROP_Y                                             450

#endif

