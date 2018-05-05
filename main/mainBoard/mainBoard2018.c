#include "mainBoard2018.h"

#include "../../common/i2c/i2cConstants.h"

#include "../../device/deviceList.h"

#include "../../main/meca1/mechanicalMainBoard1Common.h"

#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"

#include "../../robot/strategy/gameStrategyContext.h"

// 2018
#include "../../robot/2018/launcherDevice2018.h"
#include "../../robot/2018/launcherDeviceInterface2018.h"

#include "../../robot/2018/distributor2018.h"
#include "../../robot/2018/strategy2018.h"
#include "../../robot/2018/strategyDevice2018.h"
#include "../../robot/2018/strategyDeviceInterface2018.h"
#include "../../robot/2018/gameBoardElement2018.h"

// 2018 -> Distributor
static Distributor distributor;

// 2018 -> GameStrategyContext
static GameStrategyContext gameStrategyContext;
static Timer strategyTimer;
static Point robotPosition;
static Point opponentRobotPosition;
static Point lastObstaclePosition;

// 2018 -> Navigation
static Navigation navigation;
static LocationList locationList;
static Location locationListArray[STRATEGY_2018_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH];

static PathList pathList;
static PathData pathListArray[STRATEGY_2018_NAVIGATION_PATH_LIST_ARRAY_LENGTH];

static BitList outgoingPathBitList;
static unsigned int outgoingPathBitArray[STRATEGY_2018_BIT_LIST_NAVIGATION_ARRAY_LENGTH];
static BitList availablePathBitList;
static unsigned int availablePathBitArray[STRATEGY_2018_BIT_LIST_NAVIGATION_ARRAY_LENGTH];

// 2018 -> Robot
static GameBoard gameBoard;
static BSplineCurve gameBoardCurve;
static GameBoardElementList gameBoardElementList;
static GameBoardElement gameBoardElementListArray[MAIN_BOARD_2018_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH];

Navigation* initNavigation2018(void) {
    // Navigation
    initLocationList(&locationList, (Location(*)[]) &locationListArray, STRATEGY_2018_BIT_LIST_NAVIGATION_ARRAY_LENGTH);
    initPathList(&pathList, (PathData(*)[]) &pathListArray, STRATEGY_2018_NAVIGATION_PATH_LIST_ARRAY_LENGTH);
    initBitList(&outgoingPathBitList, (unsigned int(*)[]) &outgoingPathBitArray, STRATEGY_2018_BIT_LIST_NAVIGATION_ARRAY_LENGTH);
    initBitList(&availablePathBitList, (unsigned int(*)[]) &availablePathBitArray, STRATEGY_2018_BIT_LIST_NAVIGATION_ARRAY_LENGTH);

    initNavigation(&navigation, &locationList, &pathList, &outgoingPathBitList, &availablePathBitList);

    return &navigation;
}

GameStrategyContext* initGameStrategyContext2018(RobotConfig* robotConfig) {
    initGameStrategyContext(&gameStrategyContext, robotConfig, &navigation, &strategyTimer, &robotPosition, &opponentRobotPosition, &lastObstaclePosition);
    // TODO : Fill GameStrategy Context

    return &gameStrategyContext;
}

GameBoard* initGameBoard2018(GameStrategyContext* gameStrategyContext) {
    initGameBoard(&gameBoard,
        &gameBoardCurve,
        &gameBoardElementList,
        (GameBoardElement(*)[]) &gameBoardElementListArray,
        MAIN_BOARD_2018_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH,
        gameStrategyContext);

    addGameBoardElements2018(&gameBoardElementList);

    return &gameBoard;
}

void initDistributor2018(ColorSensor* colorSensor, enum TeamColor teamColor) {
    initDistributor(&distributor, teamColor, colorSensor);
}

