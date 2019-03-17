#include <math.h>
#include <stdlib.h>

#include "../../common/math/cenMath.h"

#include "gameboardElement.h"
#include "gameboard.h"

// UTILS FUNCTIONS

float getXResolutionLength(void) {
    return GAMEBOARD_WIDTH / (float)GAMEBOARD_COLUMN_COUNT;
}

float getYResolutionLength(void) {
    return GAMEBOARD_HEIGHT / (float)GAMEBOARD_LINE_COUNT;
}

/**
* @private
* Convert X into print coordinates
* @param x (mm)
*/
int convertXToColumn(float x) {
    return (int) (x / getXResolutionLength());
}

/**
* @private
* Convert Y into print coordinates
*/
int convertYToLine(float y) {
    return (int) ((GAMEBOARD_HEIGHT - y) / getYResolutionLength());
}

// BASE FUNCTIONS

void setGameBoardPixel(GameBoard* gameBoard, float x, float y, char c) {
    unsigned char column = convertXToColumn(x);
    unsigned char line = convertYToLine(y);
    gameBoard->pixels[column][line] = c;
#ifdef _MSC_VER    
    gameBoard->colors[column][line] = gameBoard->currentColorPaletIndex;
#endif
}

void setGameBoardArray(GameBoard* gameBoard, int column, int line, char c) {
    if (column >= 0 && column < GAMEBOARD_COLUMN_COUNT && line >= 0 && line < GAMEBOARD_LINE_COUNT)
    gameBoard->pixels[column][line] = c;
}

// TEXT
void drawString(GameBoard* gameBoard, float x, float y, char* s) {
    unsigned int count = 2;
    unsigned char column = convertXToColumn(x);
    unsigned char line = convertYToLine(y);
    setGameBoardArray(gameBoard, column, line, 'x');
    while (*s != '\0') {
        setGameBoardArray(gameBoard, column + count, line, *s++);
        count++;
    }
}

// POINT

void drawPoint(GameBoard* gameBoard, Point* p, char value) {
    setGameBoardPixel(gameBoard, p->x, p->y, value);
}

void drawPointCoordinates(GameBoard* gameBoard, float x, float y, char c) {
    setGameBoardPixel(gameBoard, x, y, c);
}

// LINE

void drawLine(GameBoard* gameBoard, float x1, float y1, float x2, float y2, char value) {
    float length = sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    float iteration = length / getXResolutionLength();
    if (getYResolutionLength() < getXResolutionLength()) {
        iteration = getYResolutionLength();
    }
    float stepX = (x2 - x1) / iteration;
    float stepY = (y2 - y1) / iteration;

    unsigned i;
    float x = x1;
    float y = y1;
    for (i = 0; i < iteration; i++) {
        drawPointCoordinates(gameBoard, x, y, value);
        x += stepX;
        y += stepY;
    }
}

// CIRCLE

void drawCircle(GameBoard* gameBoard, float x, float y, float radius, char c) {
    float angle;
    for (angle = 0.0f; angle < PI * 2; angle += PI / 16) {
        float circleX = x + cosf(angle) * radius;
        float circleY = y + sinf(angle) * radius;
        setGameBoardPixel(gameBoard, circleX, circleY, c);
    }
}

// RECTANGLE

void drawRectangle(GameBoard* gameBoard, float x, float y, float width, float height, char verticalChar, char horizontalChar) {
    // Horizontal Lines
    drawLine(gameBoard, x, y, x + width, y, horizontalChar);
    drawLine(gameBoard, x, y + height, x + width, y + height, horizontalChar);

    // Vertical Lines
    drawLine(gameBoard, x, y, x, y + height, verticalChar);
    drawLine(gameBoard, x + width, y, x + width, y + height, verticalChar);
}