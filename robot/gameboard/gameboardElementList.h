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
* Add a game board element to draw and which is reachable by the opponent Robot (mostly case).
*/
GameBoardElement* addReachableByOpponentRobotGameBoardElement(GameBoardElementList* gameBoardElementList,
                                                              GameboardPrintFunction* gameBoardPrintFunction);

/**
* Simplest implementation of GameboardIsreachableByOpponentRobotFunction which returns always true.
*/
bool reachableByOpponentAlways(GameBoard* gameBoard, int* element, float x, float y, float z);

/**
* Add a game board element to draw and which is not reachable by the opponent Robot. In that case, the function will be called to know
* if the opponent could be there by passing x, y, z coordinates.
*/
GameBoardElement* addGameBoardElement(
                                      GameBoardElementList* gameBoardElementList, 
                                      GameboardPrintFunction* gameBoardPrintFunction,
                                      GameboardIsReachableByOpponentRobot* reachableByOpponentRobotFunction);

#endif
