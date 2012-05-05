#include <math.h>
#include <stdlib.h>

#include "gameboardElement.h"
#include "gameboard.h"

int convertXToColumn(int x) {
	float scale = (float) GAMEBOARD_COLUMN_COUNT / GAMEBOARD_WIDTH;
	return (int)( (float) x * scale);
}

int convertYToLine(int y) {
	float scale = (float) GAMEBOARD_LINE_COUNT / GAMEBOARD_HEIGHT;
	return (int)( (float) (3000.0f - y) * scale);
}


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
