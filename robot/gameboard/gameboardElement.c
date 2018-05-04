#include <math.h>
#include <stdlib.h>

#include "gameboardElement.h"
#include "gameboard.h"

int convertXToColumn(int x) {
    float scale = (float) (GAMEBOARD_COLUMN_COUNT / GAMEBOARD_WIDTH);
    return (int) (x * scale);
}

int convertYToLine(int y) {
    float scale = (float) (GAMEBOARD_LINE_COUNT / GAMEBOARD_HEIGHT);
    return (int) ((GAMEBOARD_HEIGHT - y) * scale);
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

char filledCirclePrint(int column, int line, int x, int y, int radius, char c) {
    int xColumn = convertXToColumn(x);
    int yLine = convertYToLine(y);
    if ((column - xColumn) * (column - xColumn) + (line - yLine) * (line - yLine) <= radius * radius) {
        return c;
    }
    return CHAR_NO_DRAW;
}

// RECTANGLE

char filledRectanglePrint(int column, int line, int x, int y, int width, int height, char c) {
    int xColumn = convertXToColumn(x);
    int yLine = convertYToLine(y);
    if (abs(column - xColumn) <= width && abs(line - yLine) <= height) {
        return c;
    }
    return CHAR_NO_DRAW;
}

char emptyRectanglePrint(int column, int line, int x, int y, int width, int height, char verticalChar, char horizontalChar) {
    int x1Column = convertXToColumn(x);
    int y1Line = convertYToLine(y);
    int x2Column = convertXToColumn(x + width);
    int y2Line = convertYToLine(y + height);

    // Verticall Left and Right line
    // Be careful, 1 & 2 must be inverted because char are written to the bottom (inverse as coordinates)
    if ((column == x1Column || column == x2Column) && y2Line <= line && line <= y1Line ) {
        return verticalChar;
    }
    // Horizontal Bottom & Top Line
    if ((line == y1Line || line == y2Line) && x1Column <= column && column <= x2Column) {
        return horizontalChar;
    }
    return CHAR_NO_DRAW;
}