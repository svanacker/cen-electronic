#ifndef GAMEBOARD_ELEMENT_LIST_H
#define GAMEBOARD_ELEMENT_LIST_H

#include "gameboardElement.h"

#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetList.h"

/** The max limit of game board element. */
#define MAX_GAME_BOARD_ELEMENT 		30

/**
 * Tre struct defining a list of gameBoard Element.
 */
typedef struct {
    /** An array of pointer on gameBoard Element. */
    GameboardElement elements[MAX_GAME_BOARD_ELEMENT];
    /** the size of the list. */
    unsigned char size;
} GameboardElementList;


/**
 * Add a game board element to the list.
 * @param element the game board element to add
 */
GameboardElement* addGameboardElement(gameboardElementPrintFunction* printFunction, int* object);

/**
 * Add a location as a gameBoard Element.
 */
void addGameTargetAsGameboardElement(GameTarget* gameTarget);

void addGameTargetListAsGameboardElements(GameTargetList* gameTargetList);

/**
 * Get the game board element at index
 */
GameboardElement* getGameboardElement(int index);

/**
 * Get the count of game board element list.
 */
int getGameboardElementCount();

#endif
