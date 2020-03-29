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

void cupRedAndGreen(GameBoard* gameBoard, float x, float y) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawCircle(gameBoard, x, y, CUP_RADIUS, '*');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawCircle(gameBoard, x, GAMEBOARD_HEIGHT - y, CUP_RADIUS, '*');
}

void cupGreenAndRed(GameBoard* gameBoard, float x, float y) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawCircle(gameBoard, x, y, CUP_RADIUS, '*');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawCircle(gameBoard, x, GAMEBOARD_HEIGHT - y, CUP_RADIUS, '*');
}

void startAreaPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLUE);
    drawRectangle(gameBoard, START_AREA_RECTANGLE_GREEN_LEFT_X, START_AREA_RECTANGLE_GREEN_LEFT_Y, START_AREA_RECTANGLE_WITH, START_AREA_RECTANGLE_GREEN_HEIGHT, '|', '-');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_YELLOW);
    drawRectangle(gameBoard, START_AREA_RECTANGLE_GREEN_LEFT_X, START_AREA_RECTANGLE_GREEN_LEFT_Y + 2600, START_AREA_RECTANGLE_WITH, START_AREA_RECTANGLE_GREEN_HEIGHT, '|', '-');

    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawRectangle(gameBoard, START_AREA_RECTANGLE_GREEN_LEFT_X, START_AREA_RECTANGLE_GREEN_LEFT_Y, START_AREA_RECTANGLE_GREEN_WIDTH, START_AREA_RECTANGLE_GREEN_HEIGHT, '|', '-');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawRectangle(gameBoard, START_AREA_RECTANGLE_RED_LEFT_X, START_AREA_RECTANGLE_RED_LEFT_Y, START_AREA_RECTANGLE_RED_WIDTH, START_AREA_RECTANGLE_RED_HEIGHT, '|', '-');

    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawRectangle(gameBoard, START_AREA_RECTANGLE_GREEN_LEFT_X, START_AREA_RECTANGLE_GREEN_LEFT_Y + 2600, START_AREA_RECTANGLE_GREEN_WIDTH, START_AREA_RECTANGLE_GREEN_HEIGHT, '|', '-');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawRectangle(gameBoard, START_AREA_RECTANGLE_RED_LEFT_X, START_AREA_RECTANGLE_RED_LEFT_Y + 2600, START_AREA_RECTANGLE_RED_WIDTH, START_AREA_RECTANGLE_RED_HEIGHT, '|', '-');
}

void protectionDropAreasPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_WHITE);
    drawRectangle(gameBoard, DROP_AREA_RECTANGLE_PROTECTION_LEFT_X, DROP_AREA_RECTANGLE_PROTECTION_LEFT_Y, DROP_AREA_RECTANGLE_PROTECTION_LEFT_WIDTH, DROP_AREA_RECTANGLE_PROTECTION_LEFT_HEIGHT, '|', '-');
    drawRectangle(gameBoard, DROP_AREA_RECTANGLE_PROTECTION_LEFT_X, GAMEBOARD_HEIGHT - DROP_AREA_RECTANGLE_PROTECTION_LEFT_Y, DROP_AREA_RECTANGLE_PROTECTION_LEFT_WIDTH, DROP_AREA_RECTANGLE_PROTECTION_LEFT_HEIGHT, '|', '-');
}

void dropAreasPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawRectangle(gameBoard, DROP_AREA_RECTANGLE_GREEN_LEFT_X, DROP_AREA_RECTANGLE_GREEN_LEFT_Y, DROP_AREA_RECTANGLE_GREEN_WIDTH, DROP_AREA_RECTANGLE_GREEN_HEIGHT, '|', '-');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawRectangle(gameBoard, DROP_AREA_RECTANGLE_RED_LEFT_X, DROP_AREA_RECTANGLE_RED_LEFT_Y, DROP_AREA_RECTANGLE_RED_WIDTH, DROP_AREA_RECTANGLE_RED_HEIGHT, '|', '-');

    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawRectangle(gameBoard, DROP_AREA_RECTANGLE_GREEN_LEFT_X, DROP_AREA_RECTANGLE_GREEN_LEFT_Y - 600, DROP_AREA_RECTANGLE_GREEN_WIDTH, DROP_AREA_RECTANGLE_GREEN_HEIGHT, '|', '-');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawRectangle(gameBoard, DROP_AREA_RECTANGLE_RED_LEFT_X, DROP_AREA_RECTANGLE_RED_LEFT_Y - 600, DROP_AREA_RECTANGLE_RED_WIDTH, DROP_AREA_RECTANGLE_RED_HEIGHT, '|', '-');
}

void rightReefPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLUE);
    drawRectangle(gameBoard, RIGHT_REEF_RECTANGLE_LEFT_X, RIGHT_REEF_RECTANGLE_LEFT_Y, RIGHT_REEF_RECTANGLE_WIDTH, RIGHT_REEF_RECTANGLE_HEIGHT, '|', '-');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_YELLOW);
    drawRectangle(gameBoard, RIGHT_REEF_RECTANGLE_LEFT_X, RIGHT_REEF_RECTANGLE_LEFT_Y + 3000, RIGHT_REEF_RECTANGLE_WIDTH, RIGHT_REEF_RECTANGLE_HEIGHT, '|', '-');
}

void cupPrints(GameBoard* gameBoard, int* element) {
    // Start Area Cups
    cupRedAndGreen(gameBoard, START_AREA_CUP_RED_LEFT_X, START_AREA_CUP_RED_LEFT_Y);
    cupGreenAndRed(gameBoard, START_AREA_CUP_GREEN_LEFT_X, START_AREA_CUP_GREEN_LEFT_Y);
    cupRedAndGreen(gameBoard, START_AREA_CUP_RED_RIGHT_X, START_AREA_CUP_RED_RIGHT_Y);
    cupGreenAndRed(gameBoard, START_AREA_CUP_GREEN_RIGHT_X, START_AREA_CUP_GREEN_RIGHT_Y);

    // Reef Cups
    cupRedAndGreen(gameBoard, LEFT_REEF_CUP_RED_LEFT_X, LEFT_REEF_CUP_RED_LEFT_Y);
    cupGreenAndRed(gameBoard, LEFT_REEF_CUP_GREEN_RIGHT_X, LEFT_REEF_CUP_GREEN_RIGHT_Y);

    // Central Cups
    cupRedAndGreen(gameBoard, CENTRAL_CUP_RED_LEFT_X, CENTRAL_CUP_RED_LEFT_Y);
    cupGreenAndRed(gameBoard, CENTRAL_CUP_GREEN_RIGHT_X, CENTRAL_CUP_GREEN_RIGHT_Y);

    // Drop Area Cups
    cupGreenAndRed(gameBoard, DROP_AREA_CUP_GREEN_LEFT_X, DROP_AREA_CUP_GREEN_LEFT_Y);
    cupRedAndGreen(gameBoard, DROP_AREA_CUP_RED_RIGHT_X, DROP_AREA_CUP_RED_RIGHT_Y);
    cupRedAndGreen(gameBoard, DROP_AREA_CUP_RED_LEFT_X, DROP_AREA_CUP_RED_LEFT_Y);
    cupGreenAndRed(gameBoard, DROP_AREA_CUP_GREEN_RIGHT_X, DROP_AREA_CUP_GREEN_RIGHT_Y);

    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_WHITE);
}

void addGameBoardElements2020(GameBoardElementList* gameBoardElementList) {
    // Excluding zone
    addGameBoardElement(gameBoardElementList, &windowExclusion2020Print, &windowExclusionNotReachable2020, GAME_BOARD_ELEMENT_REACHABLE_ONLY);

    // Fake Robot
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &fakeRobotPrint2020);

    // Cups
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &cupPrints);

    // Start Areas : TODO : Change to unreachable
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &startAreaPrint);

    // Protection Areas : TODO : Change to unreachable
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &protectionDropAreasPrint);

    // Drop Areas
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &dropAreasPrint);

    // Right Reef
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &rightReefPrint);
}
