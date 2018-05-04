#ifndef SCORE_2018_H
#define SCORE_2018_H

// Unicolor Distributor
#define POINT_2018_DISTRIBUTOR_UNLOADED_POINT             10
#define POINT_2018_CLEAN_BALL_POINT                        5


#define POINT_2018_DISTRIBUTOR_UNICOLOR_BALL_COUNT         8

#define POINT_2018_DISTRIBUTOR_UNICOLOR_COMPLETE_POINT (POINT_2018_DISTRIBUTOR_UNLOADED_POINT + POINT_2018_CLEAN_BALL_POINT * POINT_2018_DISTRIBUTOR_UNICOLOR_BALL_COUNT)

// Dirty balls
#define POINT_2018_DIRTY_BALL_POINT                      10
#define POINT_2018_DISTRIBUTOR_MIXEDCOLOR_BALL_COUNT      4
#define POINT_2018_GARBAGE_RELEASE_POINT                 (POINT_2018_DIRTY_BALL_POINT * POINT_2018_DISTRIBUTOR_MIXEDCOLOR_BALL_COUNT)

// Cubes
#define POINT_2018_CUBE_FLOOR_1_POINT                     1
#define POINT_2018_CUBE_FLOOR_2_POINT                     2
#define POINT_2018_CUBE_FLOOR_3_POINT                     3
#define POINT_2018_CUBE_FLOOR_4_POINT                     4
#define POINT_2018_CUBE_FLOOR_5_POINT                     5

// Panel
#define POINT_2018_PANEL_INSTALLED_POINT                  5
#define POINT_2018_PANEL_ON_POINT                        25

// Flower
#define POINT_2018_BEE_INSTALLED_POINT                    5
#define POINT_2018_BEE_DESTROYED_POINT                   50

// BONUS
#define POINT_2018_OUTSIDE_START_AREA                    10

#endif
