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

// POINTS

/**
 * Print Function to draw a point with a c char. 
 */
char pointPrint(int column, int line, int x, int y, char c);

// CIRCLE

/** 
 * Circle with radius draw function.
 */
char filledCirclePrint(int column, int line, int x, int y, int radius, char c);

// RECTANGLE

/**
 * Filled Rectangle draw function.
 */
char filledRectanglePrint(int column, int line, int x, int y, int width, int height, char c);

/**
* Empty Rectangle draw function.
*/
char emptyRectanglePrint(int column, int line, int x, int y, int width, int height, char verticalChar, char horizontalChar);

#endif
