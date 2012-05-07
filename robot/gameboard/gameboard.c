#include <stdlib.h>

#include "gameboard.h"

#include "gameboardElement.h"
#include "gameboardElementList.h"

#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyHandler.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

static gameboardElementsSpecificYearFunction* initElementsFunction;

void setGameboardElementsSpecificYearFunction(gameboardElementsSpecificYearFunction* function) {
	initElementsFunction = function;
}

void gameboardInit() {
	// reinitialize the game board
	clearGameboardElements();

	// Static Elements
	addGameboardElement(&gameboardPrint, NULL);

	if (initElementsFunction != NULL) {
		initElementsFunction();
	}
	GameTargetList* targetList = getGameTargetList();
	addGameTargetListAsGameboardElements(targetList);
	addRobotPositionAsGameboardElement(&(getStrategyContext()->robotPosition));
}

char gameboardPrint(int* element, int column, int line) {
	if (column == 0 || column == GAMEBOARD_COLUMN_COUNT - 1) {
		return '|';
	}
	else if (line == 0 || line == GAMEBOARD_LINE_COUNT - 1) {
		return '-';
	}
	return CHAR_NO_DRAW;
}

void printGameboard(OutputStream* outputStream) {
	println(outputStream);
	int line;
	int column;
	int element;
	int elementCount = getGameboardElementCount();
	for (line = 0; line < GAMEBOARD_LINE_COUNT; line++) {
		for (column = 0; column < GAMEBOARD_COLUMN_COUNT; column++) {
			char c = CHAR_NO_DRAW;
			for (element = 0; element < elementCount; element++) {
				GameboardElement* gameboardElement = getGameboardElement(element);
				gameboardElementPrintFunction* function = gameboardElement->print;
				if (function != NULL) {
					char elementPrintChar = function(gameboardElement->object, column, line);
					if (elementPrintChar != CHAR_NO_DRAW) {
						c = elementPrintChar;
					}
				}
			}
			append(outputStream, c);
		}
		append(outputStream, '\n');
	}
}
