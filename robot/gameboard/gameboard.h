#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <stdlib.h>

// Forward declaration
struct GameBoard;
typedef struct GameBoard GameBoard;
struct GameBoardElementList;
struct GameBoardElement;
typedef struct GameBoardElementList GameBoardElementList;
typedef struct GameBoardElement GameBoardElement;

#define CHAR_NO_DRAW                ' '
#define CHAR_VERTICAL               '|'
#define CHAR_HORIZONTAL             '-'

#define GAMEBOARD_COLUMN_COUNT             80
#define GAMEBOARD_LINE_COUNT               60

#define GAMEBOARD_WIDTH               2000.0f
#define GAMEBOARD_HEIGHT              3000.0f

#define GAMEBOARD_WIDTH_INTEGER          2000
#define GAMEBOARD_HEIGHT_INTEGER         3000

#define GAMEBOARD_MIDDLE_WIDTH        (GAMEBOARD_WIDTH / 2.0f)    
#define GAMEBOARD_MIDDLE_HEIGHT       (GAMEBOARD_HEIGHT / 2.0f)

/**
* Type of function which must be called to draw an element of the gameboard.
*/
typedef void GameboardPrintFunction(GameBoard* gameBoard, int* element);

/**
* Structure to store the gameboard element;
*/
struct GameBoardElement {
    /** The function which will be used to be print. */
    GameboardPrintFunction* printFunction;
};

/**
* Structure to store the list of Game Board elements which are not "targets"
*/
struct GameBoardElementList {
    /* An array of pointer on element pointer. */
    GameBoardElement(*elements)[];
    /** the size of the list. */
    unsigned char size;
    /** the max size of the list. */
    unsigned char maxSize;
};

#include "../../motion/extended/bspline.h"
#include "../strategy/gameStrategyContext.h"

#include "../../common/io/outputStream.h"

/**
 * Gameboard.
 */
typedef struct GameBoard {
    // List of elements to draw
    GameBoardElementList* gameBoardElementList;
    // To be able to draw curve !
    BSplineCurve* gameBoardCurve;
    // pixels of the gameboard
    char pixels[GAMEBOARD_COLUMN_COUNT + 1][GAMEBOARD_LINE_COUNT + 1];
    // Show Location
    bool showLocation;
    // Show Path
    bool showPath;

// Color are only manage on Windows !
#ifdef _MSC_VER
    // colors (foreground and background) of the gameboard
    char colors[GAMEBOARD_COLUMN_COUNT + 1][GAMEBOARD_LINE_COUNT + 1];
    // Current color so that we could use the primitive easily
    char currentColorPaletIndex;
#endif

    // All informations about the strategy
    GameStrategyContext* gameStrategyContext;
} GameBoard;

/**
 * Init the gameboard with all informations
 */
void initGameBoard(GameBoard* gameBoard,
                   BSplineCurve* gameBoardCurve,
                   GameBoardElementList* gameBoardElementList, 
                   GameBoardElement(*gameBoardElementListArray)[],
                   unsigned char gameBoardElementListSize,
                   GameStrategyContext* gameStrategyContext);

/**
 * Define the color palet index to use, but it could have only effect on Windows, because RX/TX does not support Colors :)
 */
void setGameBoardCurrentColor(GameBoard* gameBoard, char currentColorPaletIndex);

/**
 * Print the gameboard in the serial console.
 */
void printGameboard(GameBoard* gameBoard, OutputStream* outputStream);

// COLLISION DETECTION

bool isPointInTheCollisionArea(GameBoard* gameBoard, Point* collisionPoint);

#endif
