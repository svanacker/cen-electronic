#ifndef LOCATION_2019_H
#define LOCATION_2019_H

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

// Blueium Right (to go to small Distributor)
#define BLUEIUM_RIGHT                                                     "BLUR"
#define BLUEIUM_RIGHT_X                                                    1500
#define BLUEIUM_RIGHT_Y                                                     225
#define BLUEIUM_RIGHT_ANGLE_FROM_DECI_DEG                     ANGLE_DECI_DEG_90
#define BLUEIUM_RIGHT_ANGLE_TO_DECI_DEG                        ANGLE_DECI_DEG_0

// Small Distributor 1
#define SMALL_DISTRIBUTOR_LINE_1                                           "SDL1"
#define SMALL_DISTRIBUTOR_LINE_1_X                                          1950
#define SMALL_DISTRIBUTOR_LINE_1_Y                                           225
#define SMALL_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG                 ANGLE_DECI_DEG_0


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

#endif
