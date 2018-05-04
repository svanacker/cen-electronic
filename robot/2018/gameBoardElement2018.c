#include <stdlib.h>

#include "gameboardElement2018.h"
#include "strategy2018.h"

#include "../../common/math/cenMath.h"

#include "../../motion/extended/bspline.h"

#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"
#include "../../robot/gameboard/gameboardBSplinePrint.h"

#include "../../robot/strategy/gameStrategyHandler.h"

// START AREA
void startAreaGreenPrint(GameBoard* gameBoard, int* element) {
    drawRectangle(gameBoard, 0.0f, 0.0f, GAME_BOARD_START_AREA_2018_WIDTH, GAME_BOARD_START_AREA_2018_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

void startAreaOrangePrint(GameBoard* gameBoard, int* element) {
    drawRectangle(gameBoard, 0.0f, GAME_BOARD_START_AREA_2018_ORANGE_Y, GAME_BOARD_START_AREA_2018_WIDTH, GAME_BOARD_START_AREA_2018_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

// GARBAGE
void garbageGreenPrint(GameBoard* gameBoard, int* element) {
    drawRectangle(gameBoard, GAME_BOARD_GARBAGE_2018_X, GAME_BOARD_GARBAGE_2018_GREEN_Y, GAME_BOARD_GARBAGE_2018_WIDTH, GAME_BOARD_GARBAGE_2018_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

void garbageOrangePrint(GameBoard* gameBoard, int* element) {
    drawRectangle(gameBoard, GAME_BOARD_GARBAGE_2018_X, GAME_BOARD_GARBAGE_2018_ORANGE_Y, GAME_BOARD_GARBAGE_2018_WIDTH, GAME_BOARD_GARBAGE_2018_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

// SWITCH
void switchGreenPrint(GameBoard* gameBoard, int* element) {
    drawPointCoordinates(gameBoard, GAME_BOARD_SWITCH_2018_X, GAME_BOARD_SWITCH_GREEN_2018_Y, 'S');
}

void switchOrangePrint(GameBoard* gameBoard, int* element) {
    drawPointCoordinates(gameBoard, GAME_BOARD_SWITCH_2018_X, GAME_BOARD_SWITCH_ORANGE_2018_Y, 'S');
}

// CUBES
void cubeSetPrintAtLocation(GameBoard* gameBoard, int* element, float x, float y) {
    drawPointCoordinates(gameBoard, x, y, '@');
    drawPointCoordinates(gameBoard, x, y + GAME_BOARD_CUBE_HEIGHT, '@');
    drawPointCoordinates(gameBoard, x + GAME_BOARD_CUBE_WIDTH, y, '@');
    drawPointCoordinates(gameBoard, x, y - GAME_BOARD_CUBE_HEIGHT, '@');
    drawPointCoordinates(gameBoard, x - GAME_BOARD_CUBE_WIDTH, y, '@');
}

void cubeSetLeft1(GameBoard* gameBoard, int* element) {
    cubeSetPrintAtLocation(gameBoard, element, GAME_BOARD_CUBE_LEFT_X, GAME_BOARD_CUBE_LEFT_Y1);
}

void cubeSetLeft2(GameBoard* gameBoard, int* element) {
    cubeSetPrintAtLocation(gameBoard, element, GAME_BOARD_CUBE_LEFT_X, GAME_BOARD_CUBE_LEFT_Y2);
}

void cubeSetMiddle1(GameBoard* gameBoard, int* element) {
    cubeSetPrintAtLocation(gameBoard, element, GAME_BOARD_CUBE_MIDDLE_X, GAME_BOARD_CUBE_MIDDLE_Y1);
}

void cubeSetMiddle2(GameBoard* gameBoard, int* element) {
    cubeSetPrintAtLocation(gameBoard, element, GAME_BOARD_CUBE_MIDDLE_X, GAME_BOARD_CUBE_MIDDLE_Y2);
}

void cubeSetRight1(GameBoard* gameBoard, int* element) {
    cubeSetPrintAtLocation(gameBoard, element, GAME_BOARD_CUBE_RIGHT_X, GAME_BOARD_CUBE_RIGHT_Y1);
}

void cubeSetRight2(GameBoard* gameBoard, int* element) {
    cubeSetPrintAtLocation(gameBoard, element, GAME_BOARD_CUBE_RIGHT_X, GAME_BOARD_CUBE_RIGHT_Y2);
}


// BUILDING_AREA
void buildingAreaGreenPrint(GameBoard* gameBoard, int* element) {
    drawRectangle(gameBoard, 0, GAME_BOARD_BUILDING_GREEN_AREA_Y, GAME_BOARD_BUILDING_AREA_WIDTH, GAME_BOARD_BUILDING_AREA_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

void buildingAreaOrangePrint(GameBoard* gameBoard, int* element) {
    drawRectangle(gameBoard, 0, GAME_BOARD_BUILDING_ORANGE_AREA_Y, GAME_BOARD_BUILDING_AREA_WIDTH, GAME_BOARD_BUILDING_AREA_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

// BEE
void beeLaunchingAreaGreenPrint(GameBoard* gameBoard, int* element) {
    drawPointCoordinates(gameBoard, GAME_BOARD_BEE_LAUNCHING_AREA_X, GAME_BOARD_BEE_LAUNCHING_GREEN_AREA_Y, 'B');
}

void beeLaunchingAreaOrangePrint(GameBoard* gameBoard, int* element) {
    drawPointCoordinates(gameBoard, GAME_BOARD_BEE_LAUNCHING_AREA_X, GAME_BOARD_BEE_LAUNCHING_ORANGE_AREA_Y, 'B');
}

// DISTRIBUTOR 1
void distributor1GreenPrint(GameBoard* gameBoard, int* element) {
    drawPointCoordinates(gameBoard, GAME_BOARD_DISTRIBUTOR_1_X, GAME_BOARD_DISTRIBUTOR_1_GREEN_Y, 'D');
}

void distributor2GreenPrint(GameBoard* gameBoard, int* element) {
    drawPointCoordinates(gameBoard, GAME_BOARD_DISTRIBUTOR_2_X, GAME_BOARD_DISTRIBUTOR_2_GREEN_Y, 'D');
}

void distributor1OrangePrint(GameBoard* gameBoard, int* element) {
    drawPointCoordinates(gameBoard, GAME_BOARD_DISTRIBUTOR_1_X, GAME_BOARD_DISTRIBUTOR_1_ORANGE_Y, 'D');
}

void distributor2OrangePrint(GameBoard* gameBoard, int* element) {
    drawPointCoordinates(gameBoard, GAME_BOARD_DISTRIBUTOR_2_X, GAME_BOARD_DISTRIBUTOR_2_ORANGE_Y, 'D');
}

// 2018 ELEMENTS

void addGameBoardElements2018(GameBoardElementList* gameBoardElementList) {

    // Start Area
    addGameBoardElement(gameBoardElementList, &startAreaGreenPrint);
    addGameBoardElement(gameBoardElementList, &startAreaOrangePrint);

    // Garbage
    addGameBoardElement(gameBoardElementList, &garbageGreenPrint);
    addGameBoardElement(gameBoardElementList, &garbageOrangePrint);

    // Switch
    addGameBoardElement(gameBoardElementList, &switchGreenPrint);
    addGameBoardElement(gameBoardElementList, &switchOrangePrint);

    // Cubes
    addGameBoardElement(gameBoardElementList, &cubeSetLeft1);
    addGameBoardElement(gameBoardElementList, &cubeSetLeft2);
    addGameBoardElement(gameBoardElementList, &cubeSetMiddle1);
    addGameBoardElement(gameBoardElementList, &cubeSetMiddle2);
    addGameBoardElement(gameBoardElementList, &cubeSetRight1);
    addGameBoardElement(gameBoardElementList, &cubeSetRight2);

    // Building Area
    addGameBoardElement(gameBoardElementList, &buildingAreaGreenPrint);
    addGameBoardElement(gameBoardElementList, &buildingAreaOrangePrint);

    // Bee
    addGameBoardElement(gameBoardElementList, &beeLaunchingAreaGreenPrint);
    addGameBoardElement(gameBoardElementList, &beeLaunchingAreaOrangePrint);

    // Distributors
    addGameBoardElement(gameBoardElementList, &distributor1GreenPrint);
    addGameBoardElement(gameBoardElementList, &distributor2GreenPrint);
    addGameBoardElement(gameBoardElementList, &distributor1OrangePrint);
    addGameBoardElement(gameBoardElementList, &distributor2OrangePrint);
}
