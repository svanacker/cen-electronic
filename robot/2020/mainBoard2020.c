#include "mainBoard2020.h"

#include "../../common/i2c/i2cConstants.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"

#include "../../common/timer/timerConstants.h"
#include "../../common/timer/timerList.h"

#include "../../device/deviceList.h"

#include "../../main/meca1/mechanicalMainBoard1Common.h"

#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"

#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/tof/strategyTofSensorList.h"


#include "../../main/mainBoard/mainBoardCommon.h"

// 2019
#include "../../robot/2020/strategy/strategy2020.h"
#include "../../robot/2020/strategy/strategyConfig2020.h"
#include "../../robot/2020/gameboard/gameBoardElement2020.h"

// 2020 -> GameStrategyContext
static GameStrategyContext gameStrategyContext;
static Point robotPosition;
static Point opponentRobotPosition;
static Point lastObstaclePosition;

// 2020 -> Navigation
static Navigation navigation;
static LocationList locationList;
static Location locationListArray[STRATEGY_2020_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH];

static PathList pathList;
static PathData pathListArray[STRATEGY_2020_NAVIGATION_PATH_LIST_ARRAY_LENGTH];

// Temporary Objects
static OutgoingPathList tmpOutgoingPathList;
static unsigned int tmpOutgoingPathListtArray[STRATEGY_2020_NAVIGATION_PATH_LIST_ARRAY_LENGTH];

// 2020 -> Robot
static GameBoard gameBoard;
static BSplineCurve gameBoardCurve;
static GameBoardElementList gameBoardElementList;
static GameBoardElement gameBoardElementListArray[MAIN_BOARD_2020_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH];

bool startupCheckList2020(StartMatch* startMatch) {

    return true;
}


Navigation* initNavigation2020(void) {
    // Navigation
    initLocationList(&locationList, (Location(*)[]) &locationListArray, STRATEGY_2020_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH);
    initPathList(&pathList, (PathData(*)[]) &pathListArray, STRATEGY_2020_NAVIGATION_PATH_LIST_ARRAY_LENGTH);
    initOutgoingPathList(&tmpOutgoingPathList, (OutgoingPathData(*)[]) &tmpOutgoingPathListtArray, STRATEGY_2020_NAVIGATION_PATH_LIST_ARRAY_LENGTH);

    initNavigation(&navigation, &locationList, &pathList, &tmpOutgoingPathList);

    return &navigation;
}

GameStrategyContext* initGameStrategyContext2020(RobotConfig* robotConfig, EndMatch* endMatch, TofSensorList* tofSensorList, ServoList* servoList) {
    initGameStrategyContext(&gameStrategyContext, robotConfig, &navigation, endMatch, tofSensorList, &robotPosition, &opponentRobotPosition, &lastObstaclePosition, servoList);
    initStrategy2020(&gameStrategyContext);

    return &gameStrategyContext;
}

GameBoard* initGameBoard2020(GameStrategyContext* gameStrategyContextParam) {
    initFirstTimeBSplineCurve(&gameBoardCurve);
    initGameBoard(&gameBoard,
        &gameBoardCurve,
        &gameBoardElementList,
        (GameBoardElement(*)[]) &gameBoardElementListArray,
        MAIN_BOARD_2020_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH,
        gameStrategyContextParam);

    addGameBoardElements2020(&gameBoardElementList);

    return &gameBoard;
}

void mainBoardCommonStrategyMainEndInit2020(GameStrategyContext* gameStrategyContextParam) {
    //ServoList* servoList = gameStrategyContext->servoList;    
    //appendStringCRLF(getDebugOutputStreamLogger(), "updateServoProperties2020");
    //updateServoProperties2020(servoList);
}
