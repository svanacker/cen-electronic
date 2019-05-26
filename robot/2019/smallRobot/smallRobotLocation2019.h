#ifndef SMALL_ROBOT_LOCATION_2019_H
#define SMALL_ROBOT_LOCATION_2019_H

#define SMALL_ROBOT_START_AREA                                              "SSTA"
#define SMALL_ROBOT_START_AREA_LABEL                           "Small Robot Start"
#define SMALL_ROBOT_START_AREA_X                                               600
#define SMALL_ROBOT_START_AREA_Y                                               380
#define SMALL_ROBOT_START_AREA_ANGLE_DECI_DEG                    ANGLE_DECI_DEG_90

// Accelerator (SMALL ROBOT)
#define ACCELERATOR_FRONT                                                     "ACCE"
#define ACCELERATOR_FRONT_LABEL                                  "Accelerator Front"
#define ACCELERATOR_FRONT_X                                                     200
#define ACCELERATOR_FRONT_Y                                                    1700
#define ACCELERATOR_FRONT_DECI_DEG                                ANGLE_DECI_DEG_90

// Accelerator centered (SMALL ROBOT)
#define ACCELERATOR_CENTER                                                    "ACCC"
#define ACCELERATOR_CENTER_LABEL                               "Accelerator Center 2"
#define ACCELERATOR_CENTER_X                                                    1000
#define ACCELERATOR_CENTER_Y                                                    1500
#define ACCELERATOR_CENTER_START_DECI_DEG                          ANGLE_DECI_DEG_90
#define ACCELERATOR_CENTER_END_DECI_DEG                           ANGLE_DECI_DEG_180


// Goldenium (SMALL ROBOT)
#define GOLDENIUM_FRONT                                                     "GOLD"
#define GOLDENIUM_FRONT_LABEL                                         "Gold Front"
#define GOLDENIUM_FRONT_X                                                     120
#define GOLDENIUM_FRONT_Y                                                    2260
#define GOLDENIUM_FRONT_ANGLE_DECI_DEG                         ANGLE_DECI_DEG_180

// Weighing Machine FRONT
#define WEIGHING_MACHINE_FRONT                                              "WMF"
#define WEIGHING_MACHINE_FRONT_LABEL                     "Weighing Machine Front"
#define WEIGHING_MACHINE_FRONT_X                                            1200
#define WEIGHING_MACHINE_FRONT_Y                                            1300
#define WEIGHING_MACHINE_FRONT_FROM_GOLDENIUM_ANGLE_DECI_DEG  ANGLE_DECI_DEG_135
#define WEIGHING_MACHINE_FRONT_TO_DROP_ANGLE_DECI_DEG           ANGLE_DECI_DEG_0

// Weighing Machine DROP
#define WEIGHING_MACHINE_DROP                                              "WMD"
#define WEIGHING_MACHINE_DROP_LABEL                      "Weighing Machine Drop"
#define WEIGHING_MACHINE_DROP_X                                            1500
#define WEIGHING_MACHINE_DROP_Y                                            1300
#define WEIGHING_MACHINE_DROP_ANGLE_DECI_DEG                   ANGLE_DECI_DEG_0

// Blueium Right (to go to small Distributor)
#define BLUEIUM_RIGHT                                                     "BLUR"
#define BLUEIUM_RIGHT_LABEL                                      "Blueium Right"
#define BLUEIUM_RIGHT_X                                                    1300
#define BLUEIUM_RIGHT_Y                                                     260
#define BLUEIUM_RIGHT_ANGLE_FROM_DECI_DEG                     ANGLE_DECI_DEG_90
#define BLUEIUM_RIGHT_ANGLE_TO_DECI_DEG                        ANGLE_DECI_DEG_0

// Small Distributor 1
#define SMALL_DISTRIBUTOR_LINE_1                                           "SDL1"
#define SMALL_DISTRIBUTOR_LINE_1_LABEL                 "Small Distributor Line 1"
#define SMALL_DISTRIBUTOR_LINE_1_X                                          1950
#define SMALL_DISTRIBUTOR_LINE_1_Y                               BLUEIUM_RIGHT_Y
#define SMALL_DISTRIBUTOR_LINE_1_ANGLE_DECI_DEG                 ANGLE_DECI_DEG_0

#endif
