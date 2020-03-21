#include "gameBoardElement2020.h"
#include <stdlib.h>

#include "../../../common/math/cenMath.h"
#include "../../../common/color/color.h"

#include "../../../motion/extended/bspline.h"

#include "../../../navigation/navigation.h"

#include "../../../robot/gameboard/gameboard.h"
#include "../../../robot/gameboard/gameboardElement.h"
#include "../../../robot/gameboard/gameboardElementList.h"
#include "../../../robot/gameboard/gameboardBSplinePrint.h"

#include "../../../robot/strategy/gameStrategyHandler.h"

#include "../../../robot/fake/fakeRobot.h"
#include "../../../robot/2020/strategy/strategy2020.h"

// FAKE ROBOT : TODO : Move it outside 2020

void fakeRobotPrint2020(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_YELLOW);
    FakeRobot* fakeRobot = getFakeRobotInstance();
    drawCircle(gameBoard, fakeRobot->x, fakeRobot->y, fakeRobot->radius, '!');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

// 2020 ELEMENTS

// AREA

void windowExclusion2020Print(GameBoard* gameBoard, int* element) {
    // Do nothing
}

bool windowExclusionNotReachable2020(GameBoard* gameBoard, int* element, float x, float y, float z) {


    return true;
}

void addGameBoardElements2020(GameBoardElementList* gameBoardElementList) {
    // Excluding zone
    addGameBoardElement(gameBoardElementList, &windowExclusion2020Print, &windowExclusionNotReachable2020, GAME_BOARD_ELEMENT_REACHABLE_ONLY);

    // Fake Robot
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &fakeRobotPrint2020);
}
