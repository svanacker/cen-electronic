#ifndef SCORE_2020_H
#define SCORE_2020_H

#define SCORE_POINT_2020_NO_POINT                                         0


// LIGHTHOUSE
#define SCORE_POINT_2020_LIGHTHOUSE_READY                                2
#define SCORE_POINT_2020_LIGHTHOUSE_ACTIVATED                            3
#define SCORE_POINT_2020_LIGHTHOUSE_OK                                   5
#define SCORE_POINT_2020_LIGHTHOUSE_ACTIVATED_AND_OK   (SCORE_POINT_2020_LIGHTHOUSE_ACTIVATED + SCORE_POINT_2020_LIGHTHOUSE_READY)

// BONUS
#define SCORE_POINT_2020_OUTSIDE_START_AREA                             5

// FLAG
#define SCORE_POINT_2020_FLAG_1                                          5
#define SCORE_POINT_2020_FLAG_2                                         15

// CUP
#define SCORE_POINT_2020_CUP_OK                                          1
#define SCORE_POINT_2020_CUP_BONUS_RIGHT_COLOR                           1
#define SCORE_POINT_2020_CUP_BONUS_2_CUP_DIFFERENT_COLORS                2
#define SCORE_POINT_2020_CUP_WITH_ALL_BONUS                              

// CUP - MAXIMAL TARGET
#define SCORE_POINT_2020_ALL_RIGHT_CUPS  (SCORE_POINT_2020_CUP_OK * 5 + SCORE_POINT_2020_CUP_BONUS_RIGHT_COLOR * 5 + SCORE_POINT_2020_CUP_BONUS_2_CUP_DIFFERENT_COLORS * 4) 
 
// HARBOR 

// TODO




#endif
