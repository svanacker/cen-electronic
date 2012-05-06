#include <stdlib.h>

#include "gameboardElementList.h"
#include "gameboardElement.h"

#include "../../common/error/error.h"

/*
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
*/

/**
 * Gameboard Element list.
 */
static GameboardElementList elements;

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

// TARGET

char gameTargetPrint(int* element, int column, int line) {
	GameTarget* target = (GameTarget*) element;
	Location* location = target->location;
	char c;
	if (target->available) {
		c = 'X';
	}
	else {
		c = 'O';
	}
	return pointPrint(column, line, location->x, location->y, c);
}

void addGameTargetAsGameboardElement(GameTarget* target) {
	addGameboardElement(&gameTargetPrint, (int*) target);
}

// POINT

char robotPositionPrint(int* element, int column, int line) {
	Point* point = (Point*) element;
	return pointPrint(column, line, point->x, point->y, 'X');
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
