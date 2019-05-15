#include "gameboardElementList.h"

#include <stdlib.h>

#include "../../common/error/error.h"

void initGameBoardElementList(GameBoardElementList* gameBoardElementList,
                              GameBoardElement(*gameBoardElementListArray)[],
                              unsigned char gameBoardElementListSize) {
    // TODO : Check Illegal Arguments
    gameBoardElementList->elements = gameBoardElementListArray;
    gameBoardElementList->size = 0;
    gameBoardElementList->maxSize = gameBoardElementListSize;
}

GameBoardElement* getGameBoardElement(GameBoardElementList* gameBoardElementList, unsigned int index) {
    if (gameBoardElementList == NULL || gameBoardElementList->maxSize == 0) {
        writeError(ROBOT_GAMEBOARD_ELEMENT_LIST_NOT_INITIALIZED);
        return NULL;
    }
    if (index < 0 || index >= gameBoardElementList->maxSize) {
        writeError(ROBOT_GAMEBOARD_ELEMENT_LIST_OUT_OF_BOUNDS);
        return NULL;
    }
    GameBoardElement* result = (GameBoardElement*)gameBoardElementList->elements;
    // we don't need use sizeof because our pointer is a GameBoardElement pointer, so the shift
    // is already of the structure, we just have to shift of index.
    result += index;

    return result;
}

bool reachableByOpponentAlways(GameBoard* gameBoard, int* element, float x, float y, float z) {
    return true;
}

bool rectangleUnReachableByOpponentAlways(GameBoard* gameBoard, int* element, float x, float y, float width, float height) {
    return false;
}

GameBoardElement* addReachableByOpponentRobotGameBoardElement(GameBoardElementList* gameBoardElementList, 
                                                              GameboardPrintFunction* gameBoardPrintFunction) {
    return addGameBoardElement(gameBoardElementList, gameBoardPrintFunction, reachableByOpponentAlways, GAME_BOARD_ELEMENT_PRINT_ONLY);
}

GameBoardElement* addGameBoardElement(GameBoardElementList* gameBoardElementList,
                                      GameboardPrintFunction* gameBoardPrintFunction,
                                      GameboardIsReachableByOpponentRobot* reachableByOpponentRobotFunction,
                                      enum GameBoardElementType gameBoardElementType) {
    if (gameBoardElementList == NULL || gameBoardElementList->maxSize == 0) {
        writeError(ROBOT_GAMEBOARD_ELEMENT_LIST_NULL);
        return NULL;
    }

    unsigned int size = gameBoardElementList->size;
    if (size < gameBoardElementList->maxSize) {
        GameBoardElement* gameBoardElement = getGameBoardElement(gameBoardElementList, size);
        gameBoardElement->printFunction = gameBoardPrintFunction;
        gameBoardElement->reachableByOpponentRobotFunction = reachableByOpponentRobotFunction;
        gameBoardElement->type = gameBoardElementType;
        gameBoardElementList->size++;
        return gameBoardElement;
    }
    else {
        writeError(ROBOT_GAMEBOARD_TOO_MUCH_ELEMENTS);
        return NULL;
    }

}