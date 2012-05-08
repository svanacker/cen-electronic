#ifndef GAMEBOARD_ELEMENT_H
#define GAMEBOARD_ELEMENT_H

/**
 * Convert X into print coordinates
 * @param x (mm)
 */
int convertXToColumn(int x);

/**
 * Convert Y into print coordinates
 */
int convertYToLine(int y);

/**
 * Print Function to draw a point with a c char. 
 */
char pointPrint(int column, int line, int x, int y, char c);

/** 
 * Circle with radius draw function.
 */
char circlePrint(int column, int line, int x, int y, int radius, char c);

/**
 * Rectangle draw function
 */
char rectanglePrint(int column, int line, int x, int y, int width, int height, char c);

#endif
