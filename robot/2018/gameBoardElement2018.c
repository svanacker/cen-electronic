#include <stdlib.h>

#include "gameboardElement2018.h"

#include "../../navigation/navigation.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"

// START AREA

char startAreaGreenPrint(int* element, int column, int line) {
    return emptyRectanglePrint(column, line, 0, 0, START_AREA_2018_WIDTH, START_AREA_2018_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

char startAreaOrangePrint(int* element, int column, int line) {
    return emptyRectanglePrint(column, line, 0, START_AREA_2018_ORANGE_Y, START_AREA_2018_WIDTH, START_AREA_2018_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

// GARBAGE
char garbageGreenPrint(int* element, int column, int line) {
    return emptyRectanglePrint(column, line, GARBAGE_2018_X, GARBAGE_2018_GREEN_Y, GARBAGE_2018_WIDTH, GARBAGE_2018_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

char garbageOrangePrint(int* element, int column, int line) {
    return emptyRectanglePrint(column, line, GARBAGE_2018_X, GARBAGE_2018_ORANGE_Y, GARBAGE_2018_WIDTH, GARBAGE_2018_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

// SWITCH
char switchGreenPrint(int* element, int column, int line) {
    return pointPrint(column, line, SWITCH_2018_X, SWITCH_GREEN_2018_Y, 'S');
}

char switchOrangePrint(int* element, int column, int line) {
    return pointPrint(column, line, SWITCH_2018_X, SWITCH_ORANGE_2018_Y, 'S');
}

// CUBES
char cubeSetPrintAtLocation(int* element, int column, int line, int x, int y) {
    unsigned result = CHAR_NO_DRAW;
    result = pointPrint(column, line, x, y, '@');
    if (result != CHAR_NO_DRAW) {
        return result;
    }
    result = pointPrint(column, line, x, y + CUBE_HEIGHT, '@');
    if (result != CHAR_NO_DRAW) {
        return result;
    }
    result = pointPrint(column, line, x + CUBE_WIDTH, y, '@');
    if (result != CHAR_NO_DRAW) {
        return result;
    }
    result = pointPrint(column, line, x, y - CUBE_HEIGHT, '@');
    if (result != CHAR_NO_DRAW) {
        return result;
    }
    result = pointPrint(column, line, x - CUBE_WIDTH, y, '@');
    return result;
}

char cubeSetLeft1(int* element, int column, int line) {
    return cubeSetPrintAtLocation(element, column, line, CUBE_LEFT_X, CUBE_LEFT_Y1);
}

char cubeSetLeft2(int* element, int column, int line) {
    return cubeSetPrintAtLocation(element, column, line, CUBE_LEFT_X, CUBE_LEFT_Y2);
}

char cubeSetMiddle1(int* element, int column, int line) {
    return cubeSetPrintAtLocation(element, column, line, CUBE_MIDDLE_X, CUBE_MIDDLE_Y1);
}

char cubeSetMiddle2(int* element, int column, int line) {
    return cubeSetPrintAtLocation(element, column, line, CUBE_MIDDLE_X, CUBE_MIDDLE_Y2);
}

char cubeSetRight1(int* element, int column, int line) {
    return cubeSetPrintAtLocation(element, column, line, CUBE_RIGHT_X, CUBE_RIGHT_Y1);
}

char cubeSetRight2(int* element, int column, int line) {
    return cubeSetPrintAtLocation(element, column, line, CUBE_RIGHT_X, CUBE_RIGHT_Y2);
}


// BUILDING_AREA
char buildingAreaGreenPrint(int* element, int column, int line) {
    return emptyRectanglePrint(column, line, 0, BUILDING_GREEN_AREA_Y, BUILDING_AREA_WIDTH, BUILDING_AREA_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

char buildingAreaOrangePrint(int* element, int column, int line) {
    return emptyRectanglePrint(column, line, 0, BUILDING_ORANGE_AREA_Y, BUILDING_AREA_WIDTH, BUILDING_AREA_HEIGHT, CHAR_VERTICAL, CHAR_HORIZONTAL);
}

// BEE
char beeLaunchingAreaGreenPrint(int* element, int column, int line) {
    return pointPrint(column, line, BEE_LAUNCHING_AREA_X, BEE_LAUNCHING_GREEN_AREA_Y, 'B');
}

char beeLaunchingAreaOrangePrint(int* element, int column, int line) {
    return pointPrint(column, line, BEE_LAUNCHING_AREA_X, BEE_LAUNCHING_ORANGE_AREA_Y, 'B');
}

// DISTRIBUTOR 1
char distributor1GreenPrint(int* element, int column, int line) {
    return pointPrint(column, line, GAME_BOARD_DISTRIBUTOR_1_X, GAME_BOARD_DISTRIBUTOR_1_GREEN_Y, 'D');
}

char distributor2GreenPrint(int* element, int column, int line) {
    return pointPrint(column, line, GAME_BOARD_DISTRIBUTOR_2_X, GAME_BOARD_DISTRIBUTOR_2_GREEN_Y, 'D');
}

char distributor1OrangePrint(int* element, int column, int line) {
    return pointPrint(column, line, GAME_BOARD_DISTRIBUTOR_1_X, GAME_BOARD_DISTRIBUTOR_1_ORANGE_Y, 'D');
}

char distributor2OrangePrint(int* element, int column, int line) {
    return pointPrint(column, line, GAME_BOARD_DISTRIBUTOR_2_X, GAME_BOARD_DISTRIBUTOR_2_ORANGE_Y, 'D');
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
