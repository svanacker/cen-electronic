#include <stdlib.h>

#include "gameboardElement2012.h"

#include "../../navigation/navigation.h"


#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"



// START AREA

char startAreaVioletPrint(int* element, int column, int line) {
	int xColumn = convertXToColumn(500);
	int yLine = convertYToLine(500);
	if (column == xColumn && yLine <= line) {
		return '|';
	}
	if (line == yLine && xColumn >= column) {
		return '-';
	}
	return CHAR_NO_DRAW;
}

char startAreaRedPrint(int* element, int column, int line) {
	int xColumn = convertXToColumn(500);
	int yLine = convertYToLine(2500);
	if (column == xColumn && yLine >= line) {
		return '|';
	}
	if (line == yLine && xColumn >= column) {
		return '-';
	}
	return CHAR_NO_DRAW;
}

// BOAT

char boatVioletPrint(int* element, int column, int line) {
	int xColumn = convertXToColumn(500);
	int yLine = convertYToLine(400);
	if (line == yLine && xColumn <= column) {
		return '-';
	}
	return CHAR_NO_DRAW;
}

char boatRedPrint(int* element, int column, int line) {
	int xColumn = convertXToColumn(500);
	int yLine = convertYToLine(2600);
	if (line == yLine && xColumn <= column) {
		return '-';
	}
	return CHAR_NO_DRAW;
}

// BOTTLES

char bottle1VioletPrint(int* element, int column, int line) {
	return pointPrint(column, line, 1950, 640, 'V');
}

char bottle2VioletPrint(int* element, int column, int line) {
	return pointPrint(column, line, 1950, 1883, 'V');
}

char bottle1RedPrint(int* element, int column, int line) {
	return pointPrint(column, line, 1950, 2360, 'R');
}

char bottle2RedPrint(int* element, int column, int line) {
	return pointPrint(column, line, 1950, 1117, 'R');
}

// PALM TREE

char palmTreePrint(int* element, int column, int line) {
	return pointPrint(column, line, GAMEBOARD_MIDDLE_WIDTH, GAMEBOARD_MIDDLE_HEIGHT, '*');
}

// TOTEMS

char totemRedPrint(int* element, int column, int line) {
	return rectanglePrint(column, line, GAMEBOARD_MIDDLE_WIDTH, GAMEBOARD_HEIGHT - 1100.0f, 2, 2, '*');
}

char totemVioletPrint(int* element, int column, int line) {
	return rectanglePrint(column, line, GAMEBOARD_MIDDLE_WIDTH, 1100.0f, 2, 2, '*');
}

// BULLION

char bullionViolet1Print(int* element, int column, int line) {
	return rectanglePrint(column, line, GAMEBOARD_MIDDLE_WIDTH, 1100.0f, 2, 1, '*');
}


void addElements2012() {
	addGameboardElement(&startAreaVioletPrint, NULL);
	addGameboardElement(&startAreaRedPrint, NULL);

	addGameboardElement(&boatVioletPrint, NULL);
	addGameboardElement(&boatRedPrint, NULL);

	addGameboardElement(&palmTreePrint, NULL);

	addGameboardElement(&totemVioletPrint, NULL);
	addGameboardElement(&totemRedPrint, NULL);

	addGameboardElement(&bottle1VioletPrint, NULL);
	addGameboardElement(&bottle2VioletPrint, NULL);
	addGameboardElement(&bottle1RedPrint, NULL);
	addGameboardElement(&bottle2RedPrint, NULL);

}
