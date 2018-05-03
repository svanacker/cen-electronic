#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gameboardElement.h"
#include "gameboardElementList.h"

#include "../strategy/gameStrategyContext.h"

#include "../../common/io/outputStream.h"

#define CHAR_NO_DRAW                ' '

#define GAMEBOARD_COLUMN_COUNT             80
#define GAMEBOARD_LINE_COUNT               60

#define GAMEBOARD_WIDTH               2000.0f
#define GAMEBOARD_HEIGHT              3000.0f

#define GAMEBOARD_MIDDLE_WIDTH        (GAMEBOARD_WIDTH / 2.0f)    
#define GAMEBOARD_MIDDLE_HEIGHT       (GAMEBOARD_HEIGHT / 2.0f)

struct GameBoard;
typedef struct GameBoard GameBoard;

/**
 * Gameboard.
 */
typedef struct GameBoard {
    // List of elements to draw
    GameBoardElementList* gameBoardElementList;
    // All informations about the strategy
    GameStrategyContext* gameStrategyContext;
} GameBoard;

/**
 * Init the gameboard with all informations
 */
void initGameBoard(GameBoard* gameBoard,
                   GameBoardElementList* gameBoardElementList, 
                   GameBoardElement(*gameBoardElementListArray)[],
                   unsigned char gameBoardElementListSize,
                   GameStrategyContext* gameStrategyContext);

/**
 * Print the gameboard in the serial console.
 */
void printGameboard(GameBoard* gameBoard, OutputStream* outputStream);

#endif
