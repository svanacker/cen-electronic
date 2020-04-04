#ifndef GAMEBOARD_ELEMENT_2020_H
#define GAMEBOARD_ELEMENT_2020_H

#include "../../../robot/gameboard/gameboardElementList.h"

#define CUP_RADIUS                                                    3.5f

// Near Start Area

#define START_AREA_CUP_RED_LEFT_X                                      400
#define START_AREA_CUP_RED_LEFT_Y                                      300

#define START_AREA_CUP_GREEN_LEFT_X                                    510
#define START_AREA_CUP_GREEN_LEFT_Y                                    450

#define START_AREA_CUP_GREEN_RIGHT_X                                  1080
#define START_AREA_CUP_GREEN_RIGHT_Y           START_AREA_CUP_GREEN_LEFT_Y

#define START_AREA_CUP_RED_RIGHT_X                                    1200
#define START_AREA_CUP_RED_RIGHT_Y               START_AREA_CUP_RED_LEFT_Y

// Near Reef

#define LEFT_REEF_CUP_RED_LEFT_X                                       100
#define LEFT_REEF_CUP_RED_LEFT_Y                                       670

#define LEFT_REEF_CUP_GREEN_RIGHT_X                                    400
#define LEFT_REEF_CUP_GREEN_RIGHT_Y                                    950

// Central

#define CENTRAL_CUP_RED_LEFT_X                                         800
#define CENTRAL_CUP_RED_LEFT_Y                                        1100

#define CENTRAL_CUP_GREEN_RIGHT_X                                     1270
#define CENTRAL_CUP_GREEN_RIGHT_Y                                     1200

// Drop Area

// -> Cup Bottom
#define DROP_AREA_CUP_GREEN_LEFT_X                                    1650
#define DROP_AREA_CUP_GREEN_LEFT_Y                                    1665

#define DROP_AREA_CUP_RED_RIGHT_X                                     1955
#define DROP_AREA_CUP_RED_RIGHT_Y                                     1605

// -> Cup Up
#define DROP_AREA_CUP_RED_LEFT_X                DROP_AREA_CUP_GREEN_LEFT_X
#define DROP_AREA_CUP_RED_LEFT_Y                                      1935

#define DROP_AREA_CUP_GREEN_RIGHT_X              DROP_AREA_CUP_RED_RIGHT_X
#define DROP_AREA_CUP_GREEN_RIGHT_Y                                   1995

// -> Drop Protection
#define DROP_AREA_RECTANGLE_PROTECTION_LEFT_X                         1850
#define DROP_AREA_RECTANGLE_PROTECTION_LEFT_Y                          889
#define DROP_AREA_RECTANGLE_PROTECTION_LEFT_WIDTH                      150
#define DROP_AREA_RECTANGLE_PROTECTION_LEFT_HEIGHT                      22

// -> Drop Area Rectangles
#define DROP_AREA_RECTANGLE_GREEN_LEFT_X                              1700
#define DROP_AREA_RECTANGLE_GREEN_LEFT_Y                              1650
#define DROP_AREA_RECTANGLE_GREEN_WIDTH                                300
#define DROP_AREA_RECTANGLE_GREEN_HEIGHT                               100

#define DROP_AREA_RECTANGLE_RED_LEFT_X    DROP_AREA_RECTANGLE_GREEN_LEFT_X
#define DROP_AREA_RECTANGLE_RED_LEFT_Y                                1850
#define DROP_AREA_RECTANGLE_RED_WIDTH      DROP_AREA_RECTANGLE_GREEN_WIDTH
#define DROP_AREA_RECTANGLE_RED_HEIGHT     DROP_AREA_RECTANGLE_GREEN_HEIGHT

// -> Right Reef
#define RIGHT_REEF_RECTANGLE_LEFT_X                                   1390
#define RIGHT_REEF_RECTANGLE_LEFT_Y                                      0
#define RIGHT_REEF_RECTANGLE_WIDTH                                     419
#define RIGHT_REEF_RECTANGLE_HEIGHT                                     10

// -> Left Reef
#define LEFT_REEF_RECTANGLE_LEFT_X                                       0
#define LEFT_REEF_RECTANGLE_LEFT_Y                                     640
#define LEFT_REEF_RECTANGLE_WIDTH                                       30
#define LEFT_REEF_RECTANGLE_HEIGHT                                     419

// -> Start Area Rectangles
#define START_AREA_RECTANGLE_WITH                                      600

#define START_AREA_RECTANGLE_GREEN_LEFT_X                              500
#define START_AREA_RECTANGLE_GREEN_LEFT_Y                                0
#define START_AREA_RECTANGLE_GREEN_WIDTH                                30
#define START_AREA_RECTANGLE_GREEN_HEIGHT                              400

#define START_AREA_RECTANGLE_RED_LEFT_X                               1070
#define START_AREA_RECTANGLE_RED_LEFT_Y  START_AREA_RECTANGLE_GREEN_LEFT_Y
#define START_AREA_RECTANGLE_RED_WIDTH    START_AREA_RECTANGLE_GREEN_WIDTH
#define START_AREA_RECTANGLE_RED_HEIGHT  START_AREA_RECTANGLE_GREEN_HEIGHT


/**
 * Add the 2020 Gameboard elementzs.
 */
void addGameBoardElements2020(GameBoardElementList* gameBoardElementList);

#endif
