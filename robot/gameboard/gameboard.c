#include <stdlib.h>

#include "gameboard.h"
#include "gameboardElement.h"
#include "../../robot/2012/gameboardElement2012.h"


#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyHandler.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

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

char drawOpponent(int column, int line) {
    GameStrategyContext* context = getStrategyContext();
    Point* opponent = &(context->opponentRobotPosition);
    return drawPoint(column, line, opponent, 'H');
}

char drawLastObstacle(int column, int line) {
    GameStrategyContext* context = getStrategyContext();
    Point* opponent = &(context->lastObstaclePosition);
    return drawPoint(column, line, opponent, 'L');
}

// ROBOT

char drawRobot(int column, int line) {
    GameStrategyContext* context = getStrategyContext();
    Point* opponent = &(context->robotPosition);
    return drawPoint(column, line, opponent, 'R');
}

// GAMEBOARD

char gameboardPrint(int* element, int column, int line) {
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
    return pointPrint(column, line, location->x, location->y, c);
}

char printAllElements(int* element, int column, int line) {
    // Robot
    char result = drawRobot(column, line);
    if (result != CHAR_NO_DRAW) {
        return result;
    }

    // Last Obstacle
    result = drawLastObstacle(column, line);
    if (result != CHAR_NO_DRAW) {
        return result;
    }

    // Opponent
    result = drawOpponent(column, line);
    if (result != CHAR_NO_DRAW) {
        return result;
    }

    // Gameboard
    result = gameboardPrint(element, column, line);
    if (result != CHAR_NO_DRAW) {
        return result;
    }

    // Targets
    int i;
    GameTargetList* gameTargetList = getGameTargetList();
    unsigned char size = gameTargetList->size;
    for (i = 0; i < size; i++) {
        GameTarget* gameTarget = gameTargetList->targets[i];

        result = gameTargetPrint((int*) gameTarget, column, line);
        if (result != CHAR_NO_DRAW) {
            return result;
        }    
    }

    return result; 
}

void printGameboard(OutputStream* outputStream) {
    println(outputStream);
    int line;
    int column;
	for (line = 0; line < GAMEBOARD_LINE_COUNT; line++) {
		for (column = 0; column < GAMEBOARD_COLUMN_COUNT; column++) {
			char c = printAllElements(NULL, column, line);
			append(outputStream, c);
		}
		if (GAMEBOARD_COLUMN_COUNT < 80) {
			append(outputStream, '\n');
		}
    }
}

// POINT

char robotPositionPrint(int* element, int column, int line) {
    Point* point = (Point*) element;
    return pointPrint(column, line, (int)point->x, (int) point->y, 'X');
}
