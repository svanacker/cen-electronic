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

// DISTRIBUTOR 1


// BUILDING_AREA

void addGameBoardElements2018(GameBoardElementList* gameBoardElementList) {
    // Start Area
    addGameBoardElement(gameBoardElementList, &startAreaGreenPrint);
    addGameBoardElement(gameBoardElementList, &startAreaOrangePrint);

    // Garbage
    addGameBoardElement(gameBoardElementList, &garbageGreenPrint);
    addGameBoardElement(gameBoardElementList, &garbageOrangePrint);
}
