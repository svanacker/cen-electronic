#include "mainBoard2019.h"

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
#include "../../robot/2019/fork/fork2019.h"
#include "../../robot/2019/fork/forkScan2019.h"
#include "../../robot/2019/distributor/distributor2019.h"
#include "../../robot/2019/strategy/strategy2019.h"
#include "../../robot/2019/strategy/strategyConfig2019.h"
#include "../../robot/2019/gameboard/gameBoardElement2019.h"

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

// Temporary Objects
static OutgoingPathList tmpOutgoingPathList;
static unsigned int tmpOutgoingPathListtArray[STRATEGY_2019_NAVIGATION_PATH_LIST_ARRAY_LENGTH];

// 2019 -> Robot
static GameBoard gameBoard;
static BSplineCurve gameBoardCurve;
static GameBoardElementList gameBoardElementList;
static GameBoardElement gameBoardElementListArray[MAIN_BOARD_2019_GAME_BOARD_PRINT_ELEMENT_ARRAY_LENGTH];

Navigation* initNavigation2019(void) {
    // Navigation
    initLocationList(&locationList, (Location(*)[]) &locationListArray, STRATEGY_2019_NAVIGATION_LOCATION_LIST_ARRAY_LENGTH);
    initPathList(&pathList, (PathData(*)[]) &pathListArray, STRATEGY_2019_NAVIGATION_PATH_LIST_ARRAY_LENGTH);
    initOutgoingPathList(&tmpOutgoingPathList, (OutgoingPathData(*)[]) &tmpOutgoingPathListtArray, STRATEGY_2019_NAVIGATION_PATH_LIST_ARRAY_LENGTH);

    initNavigation(&navigation, &locationList, &pathList, &tmpOutgoingPathList);

    return &navigation;
}

GameStrategyContext* initGameStrategyContext2019(RobotConfig* robotConfig, EndMatch* endMatch, TofSensorList* tofSensorList, ServoList* servoList) {
    initGameStrategyContext(&gameStrategyContext, robotConfig, &navigation, endMatch, tofSensorList, &robotPosition, &opponentRobotPosition, &lastObstaclePosition, servoList);
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

void mainBoardCommonStrategyMainEndInit2019(GameStrategyContext* gameStrategyContext) {
    ServoList* servoList = gameStrategyContext->servoList;    
    appendStringCRLF(getDebugOutputStreamLogger(), "updateServoProperties2019");
    updateServoProperties2019(servoList);
    
    OutputStream* debugOutputStream = getDebugOutputStreamLogger();
    appendStringCRLF(debugOutputStream, "fork2019Init");
    fork2019Init(servoList);
}
