#ifndef GAMEBOARD_ELEMENT_H
#define GAMEBOARD_ELEMENT_H

#define CHAR_NO_DRAW				' '

// forward declaration
struct GameboardElement;
typedef struct GameboardElement GameboardElement;

/**
 * Define a char function which returns a char representing what we want to print
 * Ex : | if we want to paint a border, '\0' if we don't want to represent anything
 * @param element untyped pointer on element to be able to obtain information (Ex : location)
 */
typedef char gameboardElementPrintFunction(int* element, int column, int line);

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

/**
 * Encapsulates the GameBoard Element.
 */
struct GameboardElement {
	// Print function
	gameboardElementPrintFunction* print;
	// Reference to an object to be able to have dynamic information !	
	int* object;
};

#endif
