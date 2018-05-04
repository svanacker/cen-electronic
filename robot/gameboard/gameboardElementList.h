#ifndef GAMEBOARD_ELEMENT_LIST_H
#define GAMEBOARD_ELEMENT_LIST_H


#include "gameboard.h"

/**
* Initializes the GameboardElement List with an array and the size of the array to avoid big and uniform
* array length.
* @param gameBoardElementListArray the array of element pointer to add.
* @param gameBoardElementListSize the size of the array of pointer to add.
*/
void initGameBoardElementList(GameBoardElementList* gameBoardElementList,
                              GameBoardElement(*gameBoardElementListArray)[],
                              unsigned char gameBoardElementListSize);

GameBoardElement* getGameBoardElement(GameBoardElementList* gameBoardElementList, unsigned int index);

/**
* Add a game board element to draw.
*/
GameBoardElement* addGameBoardElement(GameBoardElementList* gameBoardElementList, GameboardPrintFunction* gameBoardPrintFunction);

#endif
