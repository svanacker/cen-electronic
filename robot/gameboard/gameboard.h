#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <stdlib.h>
#include <stdbool.h>

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
* Type of function which must be called to know if the point is in the exclusion area.
* This is important to avoid to detect something wrong
* @param z is important because it could be possible that we detect something at the level of tof (between 35 / 39 cm), and not 
* at the floor
*/
typedef bool GameboardIsReachableByOpponentRobot(GameBoard* gameBoard, int* element, float x, float y, float z);

/**
 * Type of element to know if we must draw, or just manage it just for collision.
 */
enum GameBoardElementType {
    /** Type undefined. */
    GAME_BOARD_ELEMENT_UNKNOWN = 0,
    /** The element is just a print and not must manage the reacheability. */
    GAME_BOARD_ELEMENT_PRINT_ONLY = 1,
    /** The element is just something used to manage the collision. */
    GAME_BOARD_ELEMENT_REACHABLE_ONLY = 2,
    /** The element could be drawn and is used to manage the collision. */
    GAME_BOARD_ELEMENT_PRINT_AND_REACHABLE = 3
};


/**
* Structure to store the gameboard element;
*/
struct GameBoardElement {
    /** The function which will be used to be print. */
    GameboardPrintFunction* printFunction;
    /** If we consider that this area is not reachable by the robot (so we do not stop if the Time Of Flight show a specific presence). */
    GameboardIsReachableByOpponentRobot* reachableByOpponentRobotFunction;
};

/**
* Structure to store the list of Game Board elements which are not "targets"
*/
struct GameBoardElementList {
    /* An array of pointer on element pointer. */
    GameBoardElement(*elements)[];
    /** the size of the list. */
    unsigned int size;
    /** the max size of the list. */
    unsigned int maxSize;
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
    // Show Location Name
    bool showLocation;
    // Show Path Line
    bool showPath;
    // Show unavailable Path
    bool showUnavailablePath;
    // show Outgoing Path
    bool showOutgoingPath;
    // Show Unreachable Area
    bool showUnreachableArea;
    // Show Robot
    bool showRobot;
    // Show Robot Cone with Angle
    bool showRobotTofsCones;
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
void setGameBoardCurrentColor(GameBoard* gameBoard, unsigned char currentColorPaletIndex);

/**
 * Print the gameboard in the serial console.
 */
void printGameboard(GameBoard* gameBoard, OutputStream* outputStream);

// COLLISION DETECTION

bool isPointInTheCollisionArea(GameBoard* gameBoard, Point* collisionPoint);

#endif
