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


// LOCATION

char locationPrint(int* element, int column, int line) {
	Location* location = (Location*) element;
	return pointPrint(column, line, location->x, location->y, 'L');
}

void addLocationAsGameboardElement(Location* location) {
	addGameboardElement(&locationPrint, (int*) location);
}

void addLocationListAsGameboardElements(LocationList* locationList) {
	int i;
	unsigned char size = locationList->size;
	for (i = 0; i < size; i++) {
		Location* location = locationList->locations[i];

		addLocationAsGameboardElement(location);
	}	
}
