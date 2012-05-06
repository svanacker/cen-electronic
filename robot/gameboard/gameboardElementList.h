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

// TARGETS

/**
 * Add a target as a gameBoard Element.
 */
void addGameTargetAsGameboardElement(GameTarget* gameTarget);

/**
 * Add all Target as gameboard elements
 */
void addGameTargetListAsGameboardElements(GameTargetList* gameTargetList);

// POINTS

/**
 * Add the robot Position as a gameboard element
 */
void addRobotPositionAsGameboardElement(Point* point);

/**
 * Get the game board element at index
 */
GameboardElement* getGameboardElement(int index);

/**
 * Get the count of game board element list.
 */
int getGameboardElementCount();

#endif
