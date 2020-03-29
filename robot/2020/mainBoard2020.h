#ifndef MAIN_BOARD_2020_H
#define MAIN_BOARD_2020_H

#include "../../main/meca1/mechanicalMainBoard1Common.h"

#include "../../common/pwm/servo/servoList.h"

#include "../../navigation/navigation.h"

#include "../../drivers/colorSensor/colorSensor.h"
#include "../../drivers/ioExpander/ioExpander.h"
#include "../../drivers/tof/tofList.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/teamColor.h"

#include "../../robot/gameboard/gameboard.h"

#include "../../robot/match/startMatch.h"
#include "../../robot/match/endMatch.h"

#include "../../robot/config/robotConfig.h"

/**
 * This unit is done to isolate specific Functions to 2020 Editions & common
 * to PC and PIC Implementation
 */

// 2020
#define MAIN_BOARD_2020_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH    30

/**
 * Startup CheckList
 * @param startMatch
 * @return 
 */
bool startupCheckList2020(StartMatch* startMatch);

/**
* The action to do before the end of the match, for the 2020 eurobot edition (flag on).
*/
bool endMatchBeforeEnd2020(EndMatch* endMatch);

GameStrategyContext* initGameStrategyContext2020(RobotConfig* robotConfig,
        IOExpander* ioExpanderStrategy,
        EndMatch* endMatch,
        TofSensorList* tofSensorList,
        ServoList* servoList);

Navigation* initNavigation2020(void);

GameBoard* initGameBoard2020(GameStrategyContext* gameStrategyContext);

void mainBoardCommonStrategyMainEndInit2020(GameStrategyContext* gameStrategyContext);

#endif
