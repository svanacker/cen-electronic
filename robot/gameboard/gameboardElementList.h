#ifndef GAMEBOARD_ELEMENT_LIST_H
#define GAMEBOARD_ELEMENT_LIST_H

#include "gameboardElement.h"

/** The max limit of game board element. */
#define MAX_GAME_BOARD_ELEMENT 		20

/**
 * Tre struct defining a list of gameBoard Element.
 */
typedef struct {
    /** An array of pointer on gameBoard Element descriptor. */
    GameboardElement* elements[MAX_GAME_BOARD_ELEMENT];
    /** the size of the list. */
    unsigned char size;
} GameboardElementList;


/**
 * Add a a game board element list.
 * @param element the game board element to add
 */
void addGameboardElement(GameboardElement* element, gameboardElementPrintFunction* printFunction);

/**
 * Get the game board element at index
 */
GameboardElement* getGameboardElement(int index);

/**
 * Get the count of game board element list.
 */
int getGameboardElementCount();

#endif
