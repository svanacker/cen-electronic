#include "stdlib.h"

#include "gameboardElement2012.h"

#include "../../robot/gameboard/gameboard.h"
#include "../../robot/gameboard/gameboardElement.h"
#include "../../robot/gameboard/gameboardElementList.h"

static GameboardElement gameboard;

// startArea
static GameboardElement startAreaViolet;
static GameboardElement startAreaRed;

// boat
static GameboardElement boatViolet;
static GameboardElement boatRed;

// bottles
static GameboardElement bottle1Violet;
static GameboardElement bottle2Violet;
static GameboardElement bottle1Red;
static GameboardElement bottle2Red;

// totems
static GameboardElement totemViolet;
static GameboardElement totemRed;

// palmTree
static GameboardElement palmTree;

// 

// UTILS FUNCTIONS

char pointPrint(int column, int line, int x, int y, char c) {
	int xColumn = convertXToColumn(x);
	int yLine = convertYToLine(y);
	if (column == xColumn && line == yLine) {
		return c;
	}
	return CHAR_NO_DRAW;
}

char circlePrint(int column, int line, int x, int y, int radius, char c) {
	int xColumn = convertXToColumn(x);
	int yLine = convertYToLine(y);
	if ((column - xColumn) * (column - xColumn) + (line - yLine) * (line - yLine) <= radius * radius) {
		return c;
	}
	return CHAR_NO_DRAW;
}

char rectanglePrint(int column, int line, int x, int y, int width, int height, char c) {
	int xColumn = convertXToColumn(x);
	int yLine = convertYToLine(y);
	if (abs(column - xColumn) <= width && abs(line - yLine) <= height) {
		return c;
	}
	return CHAR_NO_DRAW;
}


// START AREA

char startAreaVioletPrint(GameboardElement* element, int column, int line) {
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

char startAreaRedPrint(GameboardElement* element, int column, int line) {
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

char boatVioletPrint(GameboardElement* element, int column, int line) {
	int xColumn = convertXToColumn(500);
	int yLine = convertYToLine(400);
	if (line == yLine && xColumn <= column) {
		return '-';
	}
	return CHAR_NO_DRAW;
}

char boatRedPrint(GameboardElement* element, int column, int line) {
	int xColumn = convertXToColumn(500);
	int yLine = convertYToLine(2600);
	if (line == yLine && xColumn <= column) {
		return '-';
	}
	return CHAR_NO_DRAW;
}

// BOTTLES

char bottle1VioletPrint(GameboardElement* element, int column, int line) {
	return pointPrint(column, line, 1950, 640, 'V');
}

char bottle2VioletPrint(GameboardElement* element, int column, int line) {
	return pointPrint(column, line, 1950, 1883, 'V');
}

char bottle1RedPrint(GameboardElement* element, int column, int line) {
	return pointPrint(column, line, 1950, 2360, 'R');
}

char bottle2RedPrint(GameboardElement* element, int column, int line) {
	return pointPrint(column, line, 1950, 1117, 'R');
}

// PALM TREE

char palmTreePrint(GameboardElement* element, int column, int line) {
	return pointPrint(column, line, GAMEBOARD_MIDDLE_WIDTH, GAMEBOARD_MIDDLE_HEIGHT, '*');
}

// TOTEMS

char totemRedPrint(GameboardElement* element, int column, int line) {
	return rectanglePrint(column, line, GAMEBOARD_MIDDLE_WIDTH, GAMEBOARD_HEIGHT - 1100.0f, 2, 2, '*');
}

char totemVioletPrint(GameboardElement* element, int column, int line) {
	return rectanglePrint(column, line, GAMEBOARD_MIDDLE_WIDTH, 1100.0f, 2, 2, '*');
}

// BULLION

char bullionViolet1(GameboardElement* element, int column, int line) {
	return rectanglePrint(column, line, GAMEBOARD_MIDDLE_WIDTH, 1100.0f, 2, 1, '*');
}

void addElements2012() {
	// Static Elements
	addGameboardElement(&gameboard, &gameboardPrint);
	addGameboardElement(&startAreaViolet, &startAreaVioletPrint);
	addGameboardElement(&startAreaRed, &startAreaRedPrint);

	addGameboardElement(&boatViolet, &boatVioletPrint);
	addGameboardElement(&boatRed, 	&boatRedPrint);

	addGameboardElement(&palmTree, &palmTreePrint);

	addGameboardElement(&totemViolet, &totemVioletPrint);
	addGameboardElement(&totemRed, &totemRedPrint);

	addGameboardElement(&bottle1Violet, &bottle1VioletPrint);
	addGameboardElement(&bottle2Violet, &bottle2VioletPrint);
	addGameboardElement(&bottle1Red, &bottle1RedPrint);
	addGameboardElement(&bottle2Red, &bottle2RedPrint);

}
