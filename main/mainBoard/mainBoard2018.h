#ifndef MAIN_BOARD_2018_H
#define MAIN_BOARD_2018_H

#include "../meca1/mechanicalMainBoard1Common.h"

#include "../../navigation/navigation.h"

#include "../../drivers/colorSensor/colorSensor.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/match/teamColor.h"

#include "../../robot/gameboard/gameboard.h"

/**
 * This unit is done to isolate specific Functions to 2018 Editions & common to PC and PIC Implementation
 */

 // 2018
#define MAIN_BOARD_2018_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH    30

Navigation* initNavigation2018(void);

GameStrategyContext* initGameStrategyContext2018(void);

GameBoard* initGameBoard2018(GameStrategyContext* gameStrategyContext);

void initDistributor2018(ColorSensor* colorSensor, enum TeamColor teamColor);

#endif
