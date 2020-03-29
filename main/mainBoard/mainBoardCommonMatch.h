#ifndef MAIN_BOARD_COMMON_MATCH_H
#define MAIN_BOARD_COMMON_MATCH_H

#include <stdbool.h>

#include "mainBoardCommon.h"

#include "../../robot/match/startMatch.h"

typedef bool mainBoardWaitForInstructionFunction(StartMatch* startMatchParam);

/**
 * Init the devices of the Main Board related to Match.
 */
void mainBoardCommonMatchAddDevices(void);

/**
 * Returns the startMatch object of the main Board.
 * @return 
 */
StartMatch* mainBoardCommonMatchGetStartMatch(void);

/**
 * Returns the endMatch object of the main Board.
 * @return 
 */
EndMatch* mainBoardCommonMatchGetEndMatch(void);

/**
 * Initializes StartMatch & EndMatch object.
 * @param robotConfig
 * @param isMatchStartedFunctionParam
 * @param loopUntilStartHandleFunction
 */
void mainBoardCommonMatchMainInitDrivers(RobotConfig* robotConfig,
        StartupCheckListFunction* startupCheckListFunction,
        IsMatchStartedFunction* isMatchStartedFunctionParam,
        LoopUntilStartHandleFunction* loopUntilStartHandleFunction,
        MatchHandleInstructionFunction* matchHandleInstructionFunction,
        EndMatchBeforeEndFunction* endMatchBeforeEndFunction
);

#endif
