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

#include "../../../robot/2019/gameboard/gameBoardElement2019.h"
#include "../../../robot/2019/strategy/strategy2019.h"

// 2019 ELEMENTS

// AREA
void windowExclusion2019Print(GameBoard* gameBoard, int* element) {
    // Do nothing
}

bool windowExclusionNotReachable(GameBoard* gameBoard, int* element, float x, float y, float z) {
    // If it's outside of the rectangle of the gameboard with border, return false
    if (!isInRectangle(GAME_BOARD_TOF_WINDOW_WIDTH, GAME_BOARD_TOF_WINDOW_WIDTH,
        GAMEBOARD_WIDTH - 2 * GAME_BOARD_TOF_WINDOW_WIDTH, GAMEBOARD_HEIGHT - 2 * GAME_BOARD_TOF_WINDOW_WIDTH,
        x, y)) {
        return false;
    }

    // Exclude the slope area
    if (isInRectangle(GAME_BOARD_BIG_DISTRIBUTOR_X - GAME_BOARD_TOF_WINDOW_WIDTH, 
                      GAME_BOARD_BIG_DISTRIBUTOR_Y - GAME_BOARD_TOF_WINDOW_WIDTH,
                      GAME_BOARD_BIG_DISTRIBUTOR_WIDTH + GAME_BOARD_SLOPE_WIDTH + GAME_BOARD_TOF_WINDOW_WIDTH, 
                      GAMEBOARD_HEIGHT - 2 * (GAME_BOARD_BIG_DISTRIBUTOR_Y - GAME_BOARD_TOF_WINDOW_WIDTH),
        x, y)) {
        return false;
    }
    // Excluding the separation of the weighting Machine
    if (isInRectangle(GAME_BOARD_WEIGHING_MACHINE_SEPARATOR_X - GAME_BOARD_TOF_SMALL_WINDOW_WIDTH,
        GAME_BOARD_WEIGHING_MACHINE_SEPARATOR_Y - GAME_BOARD_TOF_SMALL_WINDOW_WIDTH,
        GAME_BOARD_WEIGHING_MACHINE_SEPARATOR_WIDTH + GAME_BOARD_TOF_SMALL_WINDOW_WIDTH,
        GAME_BOARD_WEIGHING_MACHINE_SEPARATOR_HEIGHT + 2 * GAME_BOARD_TOF_SMALL_WINDOW_WIDTH,
        x, y)) {
        return false;
    }


    return true;
}

// PERIODIC TABLE 
void periodicTableRediumPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_RED);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_REDIUM_X, GAME_BOARD_PERIODIC_TABLE_REDIUM_Y, GAME_BOARD_PERIODIC_TABLE_REDIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    drawRectangle(gameBoard, GAME_BOARD_PERIODIC_TABLE_REDIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT - GAME_BOARD_PERIODIC_TABLE_REDIUM_Y, GAME_BOARD_PERIODIC_TABLE_REDIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

bool periodicTableRediumNotReachable(GameBoard* gameBoard, int* element, float x, float y, float z) {
    if (isInRectangle(GAME_BOARD_PERIODIC_TABLE_REDIUM_X, GAME_BOARD_PERIODIC_TABLE_REDIUM_Y,
        GAME_BOARD_PERIODIC_TABLE_REDIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT,
        x, y)) {
        return false;
    }
    if (isInRectangle(GAME_BOARD_PERIODIC_TABLE_REDIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT - GAME_BOARD_PERIODIC_TABLE_REDIUM_Y,
        GAME_BOARD_PERIODIC_TABLE_REDIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_REDIUM_HEIGHT,
        x, y)) {
        return false;
    }
    return true;
}

bool periodicTableBlueiumNotReachable(GameBoard* gameBoard, int* element, float x, float y, float z) {
    if (isInRectangle(GAME_BOARD_PERIODIC_TABLE_BLUEIUM_X, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_Y,
        GAME_BOARD_PERIODIC_TABLE_BLUEIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_HEIGHT,
        x, y)) {
        return false;
    }
    if (isInRectangle(GAME_BOARD_PERIODIC_TABLE_BLUEIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_PERIODIC_TABLE_BLUEIUM_HEIGHT - GAME_BOARD_PERIODIC_TABLE_BLUEIUM_Y,
        GAME_BOARD_PERIODIC_TABLE_BLUEIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_BLUEIUM_HEIGHT,
        x, y)) {
        return false;
    }
    return true;
}

bool periodicTableGreeniumNotReachable(GameBoard* gameBoard, int* element, float x, float y, float z) {
    if (isInRectangle(GAME_BOARD_PERIODIC_TABLE_GREENIUM_X, GAME_BOARD_PERIODIC_TABLE_GREENIUM_Y,
        GAME_BOARD_PERIODIC_TABLE_GREENIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_GREENIUM_HEIGHT,
        x, y)) {
        return false;
    }
    if (isInRectangle(GAME_BOARD_PERIODIC_TABLE_GREENIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_PERIODIC_TABLE_GREENIUM_HEIGHT - GAME_BOARD_PERIODIC_TABLE_GREENIUM_Y,
        GAME_BOARD_PERIODIC_TABLE_GREENIUM_WIDTH, GAME_BOARD_PERIODIC_TABLE_GREENIUM_HEIGHT,
        x, y)) {
        return false;
    }
    return true;
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
    drawRectangle(gameBoard, GAME_BOARD_ACCELERATOR_X, GAMEBOARD_HEIGHT - GAME_BOARD_ACCELERATOR_HEIGHT - GAME_BOARD_ACCELERATOR_Y, GAME_BOARD_ACCELERATOR_WIDTH, GAME_BOARD_ACCELERATOR_HEIGHT, 'A', 'A');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

void goldeniumPrint(GameBoard* gameBoard, int* element) {
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_MAGENTA);
    drawRectangle(gameBoard, GAME_BOARD_GOLDENIUM_X, GAME_BOARD_GOLDENIUM_Y, GAME_BOARD_GOLDENIUM_WIDTH, GAME_BOARD_GOLDENIUM_HEIGHT, 'G', 'G');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_YELLOW);
    drawRectangle(gameBoard, GAME_BOARD_GOLDENIUM_X, GAMEBOARD_HEIGHT - GAME_BOARD_GOLDENIUM_HEIGHT - GAME_BOARD_GOLDENIUM_Y, GAME_BOARD_GOLDENIUM_WIDTH, GAME_BOARD_GOLDENIUM_HEIGHT, 'G', 'G');
    setGameBoardCurrentColor(gameBoard, CONSOLE_COLOR_BLACK);
}

void addGameBoardElements2019(GameBoardElementList* gameBoardElementList) {
    // Excluding zone
    addGameBoardElement(gameBoardElementList, &windowExclusion2019Print, &windowExclusionNotReachable, GAME_BOARD_ELEMENT_REACHABLE_ONLY);

    // Periodic Table
    addGameBoardElement(gameBoardElementList, &periodicTableRediumPrint, &periodicTableRediumNotReachable, GAME_BOARD_ELEMENT_PRINT_AND_REACHABLE);
    addGameBoardElement(gameBoardElementList, &periodicTableGreeniumPrint, &periodicTableGreeniumNotReachable, GAME_BOARD_ELEMENT_PRINT_AND_REACHABLE);
    addGameBoardElement(gameBoardElementList, &periodicTableBlueiumPrint, &periodicTableBlueiumNotReachable, GAME_BOARD_ELEMENT_PRINT_AND_REACHABLE);

    // Chaos Area
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &chaosAreaPrint);

    // WeighingMachine
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &weighingMachinePrint);

    // Distributors
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &bigDistributorPrint);
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &smallDistributorPrint);

    // Accelerators
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &acceleratorPrint);

    // puckPeriodicTablePrint
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &puckPeriodicTablePrint);
    addReachableByOpponentRobotGameBoardElement(gameBoardElementList, &goldeniumPrint);
}
