#ifndef GAMEBOARD_ELEMENT_H
#define GAMEBOARD_ELEMENT_H

#define CHAR_NO_DRAW				' '

// forward declaration
struct GameboardElement;
typedef struct GameboardElement GameboardElement;

/**
 * Define a char function which returns a char representing what we want to print
 * Ex : | if we want to paint a border, '\0' if we don't want to represent anything
 */
typedef char gameboardElementPrintFunction(GameboardElement* element, int column, int line);

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
 * Encapsulates the GameBoard Element.
 */
struct GameboardElement {
	// Print function
	gameboardElementPrintFunction* print;
};

#endif
