#include <stdlib.h>

#include "gameBoardElement2019.h"
// #include "strategy2019.h"

#include "../../common/math/cenMath.h"

#include "../../motion/extended/bspline.h"

#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"
#include "../../robot/gameboard/gameboardBSplinePrint.h"

#include "../../robot/strategy/gameStrategyHandler.h"


// 2019 ELEMENTS

// PERIODIC TABLE 
void periodicTableRediumPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, 2);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_REDIUM_X, GAME_BOARD_PERIODIC_TABLE_REDIUM_Y, GAME_BOARD_PERIODIC_TABLE_REDIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, 0);
}

void periodicTableGreeniumPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, 3);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_GREENIUM_X, GAME_BOARD_PERIODIC_TABLE_GREENIUM_Y, GAME_BOARD_PERIODIC_TABLE_GREENIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_GREENIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, 0);
}

void periodicTableBlueiumPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, 4);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_X, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_Y, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, 0);
}


void addGameBoardElements2019(GameBoardElementList* gameBoardElementList) {
    // Periodic Table
    addGameBoardElement(gameBoardElementList, &periodicTableRediumPrint);
    addGameBoardElement(gameBoardElementList, &periodicTableGreeniumPrint);
    addGameBoardElement(gameBoardElementList, &periodicTableBlueiumPrint);

}
