#include <stdlib.h>

#include "gameBoardElement2019.h"
#include "strategy2019.h"

#include "../../common/math/cenMath.h"
#include "../../common/color/color.h"

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
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_REDIUM_X, GAME_BOARD_PERIODIC_TABLE_REDIUM_Y, GAME_BOARD_PERIODIC_TABLE_REDIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_REDIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT - GAME_BOARD_PERIODIC_TABLE_REDIUM_Y, GAME_BOARD_PERIODIC_TABLE_REDIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

void periodicTableGreeniumPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_GREENIUM_X, GAME_BOARD_PERIODIC_TABLE_GREENIUM_Y, GAME_BOARD_PERIODIC_TABLE_GREENIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_GREENIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_GREENIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_PERIODIC_TABLE_GREENIUM_HEIGHT - GAME_BOARD_PERIODIC_TABLE_GREENIUM_Y, GAME_BOARD_PERIODIC_TABLE_GREENIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_GREENIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

void periodicTableBlueiumPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLUE);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_X, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_Y, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_PERIODIC_TABLE_GREENIUM_HEIGHT - GAME_BOARD_PERIODIC_TABLE_BLUEIUM_Y, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

// CHAOS AREAS
void chaosAreaPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GRAY);
    // Big Circles : Yellow / Purple
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X, GAME_BOARD_CHAOS_AREA_Y, GAME_BOARD_CHAOS_AREA_RADIUS, '*');
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X, GAMEBOARD_HEIGHT - GAME_BOARD_CHAOS_AREA_Y, GAME_BOARD_CHAOS_AREA_RADIUS, '*');

    // Pucks Yellow
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLUE);
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X - 100.0f, GAME_BOARD_CHAOS_AREA_Y, GAME_BOARD_PUCK_RADIUS, '*');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X, GAME_BOARD_CHAOS_AREA_Y + 100.0f, GAME_BOARD_PUCK_RADIUS, '*');
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X + 100.0f, GAME_BOARD_CHAOS_AREA_Y, GAME_BOARD_PUCK_RADIUS, '*');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X, GAME_BOARD_CHAOS_AREA_Y - 100.0f, GAME_BOARD_PUCK_RADIUS, '*');

    // Pucks Magenta
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLUE);
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X - 100.0f, GAMEBOARD_HEIGHT - GAME_BOARD_CHAOS_AREA_Y, GAME_BOARD_PUCK_RADIUS, '*');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X, GAMEBOARD_HEIGHT - GAME_BOARD_CHAOS_AREA_Y + 100.0f, GAME_BOARD_PUCK_RADIUS, '*');
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X + 100.0f, GAMEBOARD_HEIGHT - GAME_BOARD_CHAOS_AREA_Y, GAME_BOARD_PUCK_RADIUS, '*');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawCircle(gameBoard, GAME_BOARD_CHAOS_AREA_X, GAMEBOARD_HEIGHT - GAME_BOARD_CHAOS_AREA_Y - 100.0f, GAME_BOARD_PUCK_RADIUS, '*');

    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

// WeighingMachine

void weighingMachinePrint(GameBoard* gameBoard, int* element) {
    // Separation
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GRAY);
    drawRectangle(gameBoard, GAME_BOARD_WEIGHING_MACHINE_SEPARATOR_X, GAME_BOARD_WEIGHING_MACHINE_SEPARATOR_Y, GAME_BOARD_WEIGHING_MACHINE_SEPARATOR_WIDTH, GAME_BOARD_WEIGHING_MACHINE_SEPARATOR_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);

    // Rectangle Yellow
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_YELLOW);
    drawRectangle(gameBoard, GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_X, GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_Y, GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_WIDTH, GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);

    // Rectangle Magenta
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_MAGENTA);
    drawRectangle(gameBoard, GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_X, GAMEBOARD_HEIGHT - GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_HEIGHT - GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_Y, GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_WIDTH, GAME_BOARD_WEIGHING_MACHINE_RECTANGLE_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

// Distributor
void bigDistributorPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GRAY);
    drawRectangle(gameBoard, GAME_BOARD_BIG_DISTRIBUTOR_X, GAME_BOARD_BIG_DISTRIBUTOR_Y, GAME_BOARD_BIG_DISTRIBUTOR_WIDTH, GAME_BOARD_BIG_DISTRIBUTOR_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    drawRectangle(gameBoard, GAME_BOARD_BIG_DISTRIBUTOR_X, GAMEBOARD_HEIGHT - GAME_BOARD_BIG_DISTRIBUTOR_HEIGHT - GAME_BOARD_BIG_DISTRIBUTOR_Y, GAME_BOARD_BIG_DISTRIBUTOR_WIDTH, GAME_BOARD_BIG_DISTRIBUTOR_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);

    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

void smallDistributorPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_YELLOW);
    drawRectangle(gameBoard, GAME_BOARD_SMALL_DISTRIBUTOR_X, GAME_BOARD_SMALL_DISTRIBUTOR_Y, GAME_BOARD_SMALL_DISTRIBUTOR_WIDTH, GAME_BOARD_SMALL_DISTRIBUTOR_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_MAGENTA);
    drawRectangle(gameBoard, GAME_BOARD_SMALL_DISTRIBUTOR_X, GAMEBOARD_HEIGHT - GAME_BOARD_SMALL_DISTRIBUTOR_HEIGHT - GAME_BOARD_SMALL_DISTRIBUTOR_Y, GAME_BOARD_SMALL_DISTRIBUTOR_WIDTH, GAME_BOARD_SMALL_DISTRIBUTOR_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);

    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}


// Pucks
void puckPeriodicTablePrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawCircle(gameBoard, GAME_BOARD_PUCK_RED_PERIODIC_TABLE_X, GAME_BOARD_PUCK_RED_PERIODIC_TABLE_Y, GAME_BOARD_PUCK_RADIUS, '.');
    drawCircle(gameBoard, GAME_BOARD_PUCK_GREEN_PERIODIC_TABLE_X, GAME_BOARD_PUCK_GREEN_PERIODIC_TABLE_Y, GAME_BOARD_PUCK_RADIUS, '.');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_GREEN);
    drawCircle(gameBoard, GAME_BOARD_PUCK_BLUE_PERIODIC_TABLE_X, GAME_BOARD_PUCK_BLUE_PERIODIC_TABLE_Y, GAME_BOARD_PUCK_RADIUS, '.');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

void acceleratorPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_MAGENTA);
    drawRectangle(gameBoard, GAME_BOARD_ACCELERATOR_X, GAME_BOARD_ACCELERATOR_Y, GAME_BOARD_ACCELERATOR_WIDTH, GAME_BOARD_ACCELERATOR_HEIGHT, 'A', 'A');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_YELLOW);
    drawRectangle(gameBoard, GAME_BOARD_ACCELERATOR_X, GAMEBOARD_HEIGHT - -GAME_BOARD_ACCELERATOR_HEIGHT - GAME_BOARD_ACCELERATOR_Y, GAME_BOARD_ACCELERATOR_WIDTH, GAME_BOARD_ACCELERATOR_HEIGHT, 'A', 'A');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

void goldeniumPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_MAGENTA);
    drawRectangle(gameBoard, GAME_BOARD_GOLDENIUM_X, GAME_BOARD_GOLDENIUM_Y, GAME_BOARD_GOLDENIUM_WIDTH, GAME_BOARD_GOLDENIUM_HEIGHT, 'X', 'X');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_YELLOW);
    drawRectangle(gameBoard, GAME_BOARD_GOLDENIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_GOLDENIUM_HEIGHT - GAME_BOARD_GOLDENIUM_Y, GAME_BOARD_GOLDENIUM_WIDTH, GAME_BOARD_GOLDENIUM_HEIGHT, 'X', 'X');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

void addGameBoardElements2019(GameBoardElementList* gameBoardElementList) {
    // Periodic Table
    addGameBoardElement(gameBoardElementList, &periodicTableRediumPrint);
    addGameBoardElement(gameBoardElementList, &periodicTableGreeniumPrint);
    addGameBoardElement(gameBoardElementList, &periodicTableBlueiumPrint);

    // Chaos Area
    addGameBoardElement(gameBoardElementList, &chaosAreaPrint);

    // WeighingMachine
    addGameBoardElement(gameBoardElementList, &weighingMachinePrint);

    // Distributors
    addGameBoardElement(gameBoardElementList, &bigDistributorPrint);
    addGameBoardElement(gameBoardElementList, &smallDistributorPrint);

    // Accelerators
    addGameBoardElement(gameBoardElementList, &acceleratorPrint);

    // puckPeriodicTablePrint
    addGameBoardElement(gameBoardElementList, &puckPeriodicTablePrint);
    addGameBoardElement(gameBoardElementList, &goldeniumPrint);

}
