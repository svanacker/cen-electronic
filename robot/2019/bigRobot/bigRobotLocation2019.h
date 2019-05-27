#ifndef BIG_ROBOT_LOCATION_2019_H
#define BIG_ROBOT_LOCATION_2019_H

// Start Area
#define BIG_ROBOT_START_AREA                                                "BSTA"
#define BIG_ROBOT_START_AREA_LABEL                                          "Big Robot Start"
#define BIG_ROBOT_START_AREA_X                                                 800
#define BIG_ROBOT_START_AREA_Y                                                 152
#define BIG_ROBOT_START_AREA_ANGLE_DECI_DEG                                      0


// Accelerator Drop Zone (BIG ROBOT)
#define ACCELERATOR_DROP                                                     "DROP"
#define ACCELERATOR_DROP_LABEL                                               "Accelerator Drop"
#define ACCELERATOR_DROP_X                                                     140
#define ACCELERATOR_DROP_Y                                                    2000
#define ACCELERATOR_DROP_DECI_DEG                               ANGLE_DECI_DEG_180

// Chaos Zone Front
#define CHAOS_ZONE_FRONT                                                   "CZFR"
#define CHAOS_ZONE_FRONT_LABEL                                             "Chaos Zone Front"
#define CHAOS_ZONE_FRONT_X                                                  1250
#define CHAOS_ZONE_FRONT_Y                                                  1150
#define CHAOS_ZONE_FRONT_ANGLE_DECI_DEG                        ANGLE_DECI_DEG_135

// Redium Drop Zone
#define REDIUM_DROP_ZONE                                                   "RDRZ"
#define REDIUM_DROP_ZONE_LABEL                                             "Redium Drop Zone"
#define REDIUM_DROP_ZONE_X                                                   550
#define REDIUM_DROP_ZONE_Y                                                   350
#define REDIUM_DROP_ZONE_ANGLE_DECI_DEG                       ANGLE_DECI_DEG_225


// Key Point to be able to go from BigDistributor to Accelerator Drop Zone
#define KEY_POINT_1                                                        "KEP1"
#define KEY_POINT_1_LABEL                                                  "Key Point 1"
#define KEY_POINT_1_X                                                       800
#define KEY_POINT_1_Y                                                       1500
#define KEY_POINT_1_FROM_ACCERATOR_ANGLE_DECI_DEG                           ANGLE_DECI_DEG_180
#define KEY_POINT_1_FROM_REDIUM_DROP_ZONE_ANGLE_DECI_DEG                    ANGLE_DECI_DEG_270
#define KEY_POINT_1_FROM_DISTRIBUTOR_ANGLE_DECI_DEG                         ANGLE_DECI_DEG_0
#define KEY_POINT_1_TO_ACCERATOR_ANGLE_DECI_DEG                             ANGLE_DECI_DEG_180
#define KEY_POINT_1_TO_REDIUM_DROP_ZONE_ANGLE_DECI_DEG                      ANGLE_DECI_DEG_270
#define KEY_POINT_1_TO_DISTRIBUTOR_ANGLE_DECI_DEG                           ANGLE_DECI_DEG_0

// Key point to be able to do a transition from REDIUM_DROP_ZONE then to
// go on BIG_DISTRIBUTOR_LINE_1
#define KEY_POINT_2                                                        "KEP2"
#define KEY_POINT_2_LABEL                                                  "Key Point 2"
#define KEY_POINT_2_X                                                        800
#define KEY_POINT_2_Y                                                        600
#define KEY_POINT_2_ANGLE_DECI_DEG                            -ANGLE_DECI_DEG_135
#define KEY_POINT_2_FROM_REDIUM_ZONE_ANGLE_DECI_DEG           -ANGLE_DECI_DEG_135
#define KEY_POINT_2_TO_DISTRIBUTOR_ANGLE_DECI_DEG               ANGLE_DECI_DEG_0


// BIG DISTRIBUTOR
#define BIG_DISTRIBUTOR_LINE_1                                            "BDL1"
#define BIG_DISTRIBUTOR_LINE_1_LABEL                                      "Big Distributor Line 1"
#define BIG_DISTRIBUTOR_LINE_1_X                                            1465
#define BIG_DISTRIBUTOR_LINE_1_Y                                             650
#define BIG_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG                     ANGLE_DECI_DEG_0

#define BIG_DISTRIBUTOR_LINE_2                                            "BDL2"
#define BIG_DISTRIBUTOR_LINE_2_LABEL                                      "Big Distributor Line 1"
#define BIG_DISTRIBUTOR_LINE_2_X                        BIG_DISTRIBUTOR_LINE_1_X
#define BIG_DISTRIBUTOR_LINE_2_Y                  BIG_DISTRIBUTOR_LINE_1_Y + 200
#define BIG_DISTRIBUTOR_LINE_2_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

#define BIG_DISTRIBUTOR_LINE_3                                            "BDL3"
#define BIG_DISTRIBUTOR_LINE_3_LABEL                                      "Big Distributor Line 3"
#define BIG_DISTRIBUTOR_LINE_3_X                        BIG_DISTRIBUTOR_LINE_1_X
#define BIG_DISTRIBUTOR_LINE_3_Y                  BIG_DISTRIBUTOR_LINE_2_Y + 200
#define BIG_DISTRIBUTOR_LINE_3_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

#endif
