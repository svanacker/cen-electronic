#ifndef GAMEBOARD_ELEMENT_2018_H
#define GAMEBOARD_ELEMENT_2018_H

#include "../../robot/gameboard/gameboardElementList.h"

// StartArea
#define START_AREA_2018_WIDTH        650
#define START_AREA_2018_HEIGHT       360
#define START_AREA_2018_GREEN_Y        0
#define START_AREA_2018_ORANGE_Y    2640

// Garbage
#define GARBAGE_2018_X              1750
#define GARBAGE_2018_WIDTH           250
#define GARBAGE_2018_HEIGHT          606
#define GARBAGE_2018_ORANGE_Y        894
#define GARBAGE_2018_GREEN_Y        1500

// Switch
#define SWITCH_2018_X                 0
#define SWITCH_GREEN_2018_Y         1130
#define SWITCH_ORANGE_2018_Y        GAMEBOARD_HEIGHT_INTEGER - SWITCH_GREEN_2018_Y

// Cubes
#define CUBE_WIDTH                    50
#define CUBE_HEIGHT                   50
#define CUBE_LEFT_X                  540
#define CUBE_MIDDLE_X               1190
#define CUBE_RIGHT_X                1500
#define CUBE_LEFT_Y1                 850
#define CUBE_MIDDLE_Y1               300
#define CUBE_RIGHT_Y1               1100
#define CUBE_LEFT_Y2                GAMEBOARD_HEIGHT_INTEGER - CUBE_LEFT_Y1 
#define CUBE_MIDDLE_Y2              GAMEBOARD_HEIGHT_INTEGER - CUBE_MIDDLE_Y1
#define CUBE_RIGHT_Y2               GAMEBOARD_HEIGHT_INTEGER - CUBE_RIGHT_Y1

// BUILDING ZONE
#define BUILDING_AREA_WIDTH          180
#define BUILDING_GREEN_AREA_Y        400
#define BUILDING_AREA_HEIGHT         560
#define BUILDING_ORANGE_AREA_Y      2040

// BEE LAUNCHING_AREA
#define BEE_LAUNCHING_AREA_X        2000
#define BEE_LAUNCHING_GREEN_AREA_Y   200
#define BEE_LAUNCHING_ORANGE_AREA_Y   GAMEBOARD_HEIGHT_INTEGER - BEE_LAUNCHING_GREEN_AREA_Y

// DISTRIBUTORS
#define GAME_BOARD_DISTRIBUTOR_1_X              840
#define GAME_BOARD_DISTRIBUTOR_1_GREEN_Y          0
#define GAME_BOARD_DISTRIBUTOR_1_ORANGE_Y       GAMEBOARD_HEIGHT_INTEGER - GAME_BOARD_DISTRIBUTOR_1_GREEN_Y
#define GAME_BOARD_DISTRIBUTOR_2_X              GAMEBOARD_WIDTH_INTEGER
#define GAME_BOARD_DISTRIBUTOR_2_GREEN_Y        610
#define GAME_BOARD_DISTRIBUTOR_2_ORANGE_Y       GAMEBOARD_HEIGHT_INTEGER - GAME_BOARD_DISTRIBUTOR_2_GREEN_Y

/**
 * Add the 2018 Gameboard elementzs.
 */
void addGameBoardElements2018(GameBoardElementList* gameBoardElementList);

#endif
