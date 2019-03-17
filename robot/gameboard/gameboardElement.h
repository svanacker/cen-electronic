#ifndef GAMEBOARD_ELEMENT_H
#define GAMEBOARD_ELEMENT_H

#include "../../common/2d/2d.h"

#include "gameboard.h"

// BASE FUNCTIONS

/**
 * Set a pixel on a gameboard at a coordinates.
 */
void setGameBoardPixel(GameBoard* gameBoard, float x, float y, char c);

// TEXT
void drawString(GameBoard* gameBoard, float x, float y, char* s);

// POINTS

/**
 * Print Function to draw a point with a c char. 
 */
void drawPointCoordinates(GameBoard* gameBoard, float x, float y, char c);

void drawPoint(GameBoard* gameBoard, Point* p, char value);

// LINE

void drawLine(GameBoard* gameBoard, float x1, float y1, float x2, float y2, char value);

// CIRCLE

/** 
 * Circle with radius draw function.
 */
void drawCircle(GameBoard* gameBoard, float x, float y, float radius, char c);

// RECTANGLE

/**
* Empty Rectangle draw function.
*/
void drawRectangle(GameBoard* gameBoard, float x, float y, float width, float height, char verticalChar, char horizontalChar);

#endif
