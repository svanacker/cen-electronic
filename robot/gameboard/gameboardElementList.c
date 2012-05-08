#include <stdlib.h>

#include "gameboardElementList.h"
#include "gameboardElement.h"

#include "../../common/error/error.h"

/**
 * Gameboard Element list.
 */
static GameboardElementList elements;

void clearGameboardElements() {
	elements.size = 0;
}

GameboardElement* addGameboardElement(gameboardElementPrintFunction* printFunction, int* object) {
    unsigned char size = elements.size;
	if (size < MAX_GAME_BOARD_ELEMENT) {
		GameboardElement* result = &(elements.elements[size]);
		result->object = object;
		result->print = printFunction;
	    elements.size++;
		return result;
	}
	else {
		writeError(TOO_MUCH_GAME_BOARD_ELEMENTS);
    }
	return NULL;
}

GameboardElement* getGameboardElement(int index) {
    return &(elements.elements[index]);
}

int getGameboardElementCount() {
    return elements.size;
}

// ROBOT

void addRobotPositionAsGameboardElement(Point* point) {
	addGameboardElement(&robotPositionPrint, (int*) point);
}

void addGameTargetListAsGameboardElements(GameTargetList* gameTargetList) {
	int i;
	unsigned char size = gameTargetList->size;
	for (i = 0; i < size; i++) {
		GameTarget* gameTarget = gameTargetList->targets[i];

		addGameTargetAsGameboardElement(gameTarget);
	}	
}
