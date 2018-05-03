#include <stdlib.h>

#include "gameboard.h"
#include "gameboardElement.h"
#include "gameboardElementList.h"
#include "../../robot/2012/gameboardElement2012.h"


#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyHandler.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

// Initialization

void initGameBoard(GameBoard* gameBoard,
                    GameBoardElementList* gameBoardElementList,
                    GameBoardElement(*gameBoardElementListArray)[],
                    unsigned char gameBoardElementListSize,
                    GameStrategyContext* gameStrategyContext) {
    gameBoard->gameBoardElementList = gameBoardElementList;
    initGameBoardElementList(gameBoardElementList, gameBoardElementListArray, gameBoardElementListSize);
    gameBoard->gameStrategyContext = gameStrategyContext;
}

char drawPoint(int column, int line, Point* p, char value) {
    if (p->x == 0 && p->y == 0) {
        return CHAR_NO_DRAW;
    }
    
    int xColumn = convertXToColumn((int) p->x);
    int yLine = convertYToLine((int) p->y);

    if (line == yLine && column == xColumn) {
        return value;
    }

    return CHAR_NO_DRAW;
}

// OPPONENT

char drawOpponent(Point* opponent, int column, int line) {
    return drawPoint(column, line, opponent, 'H');
}

char drawLastObstacle(Point* obstacle, int column, int line) {
    return drawPoint(column, line, obstacle, 'L');
}

// ROBOT

char drawRobot(Point* robotPosition, int column, int line) {
    return drawPoint(column, line, robotPosition, 'R');
}

// GAMEBOARD

char gameboardBorderPrint(int* element, int column, int line) {
    if (column == 0 || column == GAMEBOARD_COLUMN_COUNT - 1) {
        return '|';
    }
    else if (line == 0 || line == GAMEBOARD_LINE_COUNT - 1) {
        return '-';
    }
    return CHAR_NO_DRAW;
}

// TARGET

char gameTargetPrint(int* element, int column, int line) {
    GameTarget* target = (GameTarget*) element;
    Location* location = target->location;
    char c;
    if (target->status == TARGET_AVAILABLE) {
        c = 'X';
    }
    else {
        c = 'O';
    }
    return pointPrint(column, line, (int) location->x, (int)location->y, c);
}

char printAllElements(GameBoard* gameBoard, int* element, int column, int line) {
    GameStrategyContext* gameStrategyContext = gameBoard->gameStrategyContext;
    // Robot
    char result = drawRobot(gameStrategyContext->robotPosition, column, line);
    if (result != CHAR_NO_DRAW) {
        return result;
    }

    // Last Obstacle
    result = drawLastObstacle(gameStrategyContext->lastObstaclePosition, column, line);
    if (result != CHAR_NO_DRAW) {
        return result;
    }

    // Opponent
    result = drawOpponent(gameStrategyContext->opponentRobotPosition, column, line);
    if (result != CHAR_NO_DRAW) {
        return result;
    }

    // Borders
    result = gameboardBorderPrint(element, column, line);
    if (result != CHAR_NO_DRAW) {
        return result;
    }

    // Elements
    GameBoardElementList* gameBoardElementList = gameBoard->gameBoardElementList;
    int i;
    unsigned char size = gameBoardElementList->size;
    for (i = 0; i < size; i++) {
        GameBoardElement* gameBoardElement = getGameBoardElement(gameBoardElementList, i);

        GameboardPrintFunction* printFunction = gameBoardElement->printFunction;
        result = printFunction((int*)gameBoardElement, column, line);
        if (result != CHAR_NO_DRAW) {
            return result;
        }
    }

    // Targets
    GameTargetList* gameTargetList = getGameTargetList();
    size = gameTargetList->size;
    for (i = 0; i < size; i++) {
        GameTarget* gameTarget = gameTargetList->targets[i];

        result = gameTargetPrint((int*) gameTarget, column, line);
        if (result != CHAR_NO_DRAW) {
            return result;
        }    
    }

    return result; 
}

void printGameboard(GameBoard* gameBoard,  OutputStream* outputStream) {
    println(outputStream);
    int line;
    int column;
	for (line = 0; line < GAMEBOARD_LINE_COUNT; line++) {
		for (column = 0; column < GAMEBOARD_COLUMN_COUNT; column++) {
			char c = printAllElements(gameBoard, NULL, column, line);
			append(outputStream, c);
		}
        append(outputStream, '\n');
    }
}

// POINT

char robotPositionPrint(int* element, int column, int line) {
    Point* point = (Point*) element;
    return pointPrint(column, line, (int)point->x, (int) point->y, 'X');
}
