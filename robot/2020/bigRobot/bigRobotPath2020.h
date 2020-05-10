#ifndef BIG_ROBOT_PATH_2020_H
#define BIG_ROBOT_PATH_2020_H

// -> Big Robot : Start Area -> Point 1
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_COST                          500.0f
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_CP1                           400.0f
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_CP2                           600.0f
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_SPEED_FACTOR                    0.5f
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_ACC_FACTOR                      0.5f

// -> Big Robot : Point 1 -> Small Harbor Front Middle
/*
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_COST                   2000.0f
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_CP1                      50.0f
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_CP2                      50.0f
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_SPEED_FACTOR             0.75f
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_ACC_FACTOR                0.5f
*/

#define BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT_COST                        200.0f
#define BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT_CP1                        -100.0f
#define BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT_CP2                        -100.0f
#define BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT_SPEED_FACTOR                 0.75f
#define BIG_ROBOT_POINT_1__TO__LIGHT_HOUSE_DROP_FRONT__ACC_FACTOR                   0.5f

#define LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_COST               2000.0f
#define LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_CP1                 200.0f
#define LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_CP2                  50.0f
#define LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_SPEED_FACTOR         0.75f
#define LIGHT_HOUSE_DROP_FRONT__TO__SMALL_HARBOR_FRONT_MIDDLE_ACC_FACTOR            0.5f

// -> Big Robot : Small Harbor Front Middle -> Left Reef Front
#define SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_COST                     800.0f
#define SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_CP1                         -200.0f
#define SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_CP2                         -600.0f
#define SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_SPEED_FACTOR                  1.0f
#define SMALL_HARBOR_FRONT_MIDDLE__TO__LEFT_REEF_FRONT_ACC_FACTOR                    1.0f

// -> Big Robot : Left Reef Front -> Left Reef Take
#define LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_COST                                  1000.0f
#define LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_CP1                                    100.0f
#define LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_CP2                                    100.0f
#define LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_SPEED_FACTOR                            0.5f
#define LEFT_REEF_FRONT__TO__LEFT_REEF_TAKE_ACC_FACTOR                              0.5f

// -> Big Robot : Left Reef Take -> Front Left
#define LEFT_REEF_TAKE__TO__FRONT_LEFT_COST                                        800.0f
#define LEFT_REEF_TAKE__TO__FRONT_LEFT_CP1                                        -350.0f
#define LEFT_REEF_TAKE__TO__FRONT_LEFT_CP2                                        -350.0f
#define LEFT_REEF_TAKE__TO__FRONT_LEFT_SPEED_FACTOR                                 0.75f
#define LEFT_REEF_TAKE__TO__FRONT_LEFT_ACC_FACTOR                                   0.75f

// Front Left -> Drop Left
#define FRONT_LEFT__TO__DROP_LEFT_COST                                             300.0f
#define FRONT_LEFT__TO__DROP_LEFT_CP1                                              100.0f
#define FRONT_LEFT__TO__DROP_LEFT_CP2                                              100.0f
#define FRONT_LEFT__TO__DROP_LEFT_SPEED_FACTOR                                      0.75f
#define FRONT_LEFT__TO__DROP_LEFT_ACC_FACTOR                                        0.75f

// Big Robot : Drop Left -> Central Start Area (to adjust Y and angle)
#define DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_COST                             300.0f
#define DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_CP1                             -100.0f
#define DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_CP2                             -100.0f
#define DROP_LEFT_FRONT__TO__CENTRAL_START_SPEED_FACTOR                           0.75f
#define DROP_LEFT_FRONT__TO__CENTRAL_START_ACC_FACTOR                              0.5f

#endif

