#ifndef BIG_ROBOT_PATH_2020_H
#define BIG_ROBOT_PATH_2020_H

// -> Big Robot : Start Area -> Point 1
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_COST                         500.0f
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_CP1                          400.0f
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_CP2                          600.0f
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_SPEED_FACTOR                  0.5f
#define BIG_ROBOT_STARTAREA__TO__BIG_ROBOT_POINT_1_ACC_FACTOR                    0.5f

// -> Big Robot : Point 1 -> Small Harbor Front Middle
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_COST                   2000.0f
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_CP1                      50.0f
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_CP2                      50.0f
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_SPEED_FACTOR             0.75f
#define BIG_ROBOT_POINT_1__TO__SMALL_HARBOR_FRONT_MIDDLE_ACC_FACTOR                0.5f

// -> Big Robot : Small Harbor Front Middle -> Center Point
#define SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_COST                         800.0f
#define SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_CP1                         -100.0f
#define SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_CP2                         -100.0f
#define SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_SPEED_FACTOR                   0.5f
#define SMALL_HARBOR_FRONT_MIDDLE__TO__CENTER_POINT_ACC_FACTOR                     0.5f

// -> Big Robot : Center Point -> Left Reef Front
#define CENTER_POINT__TO__LEFT_REEF_FRONT_COST                                  1000.0f
#define CENTER_POINT__TO__LEFT_REEF_FRONT_CP1                                    200.0f
#define CENTER_POINT__TO__LEFT_REEF_FRONT_CP2                                    200.0f
#define CENTER_POINT__TO__LEFT_REEF_FRONT_SPEED_FACTOR                             1.0f
#define CENTER_POINT__TO__LEFT_REEF_FRONT_ACC_FACTOR                               1.0f

// -> Big Robot : Left Reef Front -> Drop Left
#define LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_COST                                800.0f
#define LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_CP1                                -150.0f
#define LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_CP2                                -150.0f
#define LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_SPEED_FACTOR                          1.0f
#define LEFT_REEF_FRONT__TO__DROP_LEFT_FRONT_ACC_FACTOR                            1.0f

// Big Robot : Drop Left -> Central Start Area (to adjust Y and angle)
#define DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_COST                             300.0f
#define DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_CP1                             -100.0f
#define DROP_LEFT_FRONT__TO__CENTRAL_START_AREA_CP2                              100.0f
#define DROP_LEFT_FRONT__TO__CENTRAL_START_SPEED_FACTOR                           0.75f
#define DROP_LEFT_FRONT__TO__CENTRAL_START_ACC_FACTOR                              0.5f

// Big Robot : Central Start Area -> Leef Reef Front 2
#define CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_COST                           2000.0f
#define CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_CP1                             200.0f
#define CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_CP2                             300.0f
#define CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_SPEED_FACTOR                      1.0f
#define CENTER_START_AREA__TO__LEFT_REEF_FRONT_2_ACC_FACTOR                        1.0f

// Big Robot : Leef Reef Front 2 -> Central Drop Area
#define LEFT_REEF_FRONT_2__TO__DROP_CENTER_FRONT_COST                           2000.0f
#define LEFT_REEF_FRONT_2__TO__DROP_CENTER_FRONT_CP1                            -300.0f
#define LEFT_REEF_FRONT_2__TO__DROP_CENTER_FRONT_CP2                             300.0f
#define LEFT_REEF_FRONT_2__TO__DROP_CENTER_FRONT_SPEED_FACTOR                      1.0f
#define LEFT_REEF_FRONT_2__TO__DROP_CENTER_FRONT_ACC_FACTOR                        1.0f

#endif

