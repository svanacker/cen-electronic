#include "gameboardElementList.h"
#include "gameboardElement.h"

#include "../../common/error/error.h"

/**
 * Gameboard Element list.
 */
static GameboardElementList elements;

void addGameboardElement(GameboardElement* element, gameboardElementPrintFunction* printFunction) {
    unsigned char size = elements.size;
	if (size < MAX_GAME_BOARD_ELEMENT) {
		element->print = printFunction;
	    elements.elements[size] = element;
	    elements.size++;
	}
	else {
		writeError(TOO_MUCH_GAME_BOARD_ELEMENTS);
    }
}

GameboardElement* getGameboardElement(int index) {
    return elements.elements[index];
}

int getGameboardElementCount() {
    return elements.size;
}
