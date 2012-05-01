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
