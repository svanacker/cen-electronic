#include "mainBoard2019.h"

#include "../../common/i2c/i2cConstants.h"

#include "../../common/timer/timerConstants.h"
#include "../../common/timer/timerList.h"

#include "../../device/deviceList.h"

#include "../../main/meca1/mechanicalMainBoard1Common.h"

#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"

#include "../../robot/strategy/gameStrategyContext.h"

// 2019
#include "../../robot/2019/distributor2019.h"
#include "../../robot/2019/strategy2019.h"
#include "../../robot/2019/gameBoardElement2019.h"

// 2019 -> GameStrategyContext
static GameStrategyContext gameStrategyContext;
static Point robotPosition;
static Point opponentRobotPosition;
static Point lastObstaclePosition;

// 2019 -> Navigation
static Navigation navigation;
static LocationList locationList;
static Location locationListArray[STRATEGY_2019_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH];

static PathList pathList;
static PathData pathListArray[STRATEGY_2019_NAVIGATION_PATH_LIST_ARRAY_LENGTH];

static BitList outgoingPathBitList;
static unsigned int outgoingPathBitArray[STRATEGY_2019_BIT_LIST_NAVIGATION_ARRAY_LENGTH];
static BitList availablePathBitList;
static unsigned int availablePathBitArray[STRATEGY_2019_BIT_LIST_NAVIGATION_ARRAY_LENGTH];

// 2019 -> Robot
static GameBoard gameBoard;
static BSplineCurve gameBoardCurve;
static GameBoardElementList gameBoardElementList;
static GameBoardElement gameBoardElementListArray[MAIN_BOARD_2019_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH];

Navigation* initNavigation2019(void) {
    // Navigation
    initLocationList(&locationList, (Location(*)[]) &locationListArray, STRATEGY_2019_BIT_LIST_NAVIGATION_ARRAY_LENGTH);
    initPathList(&pathList, (PathData(*)[]) &pathListArray, STRATEGY_2019_NAVIGATION_PATH_LIST_ARRAY_LENGTH);
    initBitList(&outgoingPathBitList, (unsigned int(*)[]) &outgoingPathBitArray, STRATEGY_2019_BIT_LIST_NAVIGATION_ARRAY_LENGTH);
    initBitList(&availablePathBitList, (unsigned int(*)[]) &availablePathBitArray, STRATEGY_2019_BIT_LIST_NAVIGATION_ARRAY_LENGTH);

    initNavigation(&navigation, &locationList, &pathList, &outgoingPathBitList, &availablePathBitList);

    return &navigation;
}

GameStrategyContext* initGameStrategyContext2019(RobotConfig* robotConfig, EndMatch* endMatch, TofSensorList* tofSensorList) {
    initGameStrategyContext(&gameStrategyContext, robotConfig, &navigation, endMatch, tofSensorList, &robotPosition, &opponentRobotPosition, &lastObstaclePosition);
    initStrategy2019(&gameStrategyContext);

    return &gameStrategyContext;
}

GameBoard* initGameBoard2019(GameStrategyContext* gameStrategyContext) {
    initFirstTimeBSplineCurve(&gameBoardCurve);
    initGameBoard(&gameBoard,
        &gameBoardCurve,
        &gameBoardElementList,
        (GameBoardElement(*)[]) &gameBoardElementListArray,
        MAIN_BOARD_2019_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH,
        gameStrategyContext);

    addGameBoardElements2019(&gameBoardElementList);

    return &gameBoard;
}

