#include <stdlib.h>
#include <math.h>
#include "gameboard.h"
#include "gameboardElement.h"
#include "gameboardElementList.h"
#include "gameboardBSplinePrint.h"
#include "../../robot/2012/gameBoardElement2012.h"

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyHandler.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"


// Initialization

void initGameBoard(GameBoard* gameBoard,
                   BSplineCurve* gameBoardSplineCurve,
                    GameBoardElementList* gameBoardElementList,
                    GameBoardElement(*gameBoardElementListArray)[],
                    unsigned char gameBoardElementListSize,
                    GameStrategyContext* gameStrategyContext) {
    gameBoard->gameBoardElementList = gameBoardElementList;
    gameBoard->gameBoardCurve = gameBoardSplineCurve;
    initGameBoardElementList(gameBoardElementList, gameBoardElementListArray, gameBoardElementListSize);
    gameBoard->gameStrategyContext = gameStrategyContext;
}

// OPPONENT

void drawOpponent(GameBoard* gameBoard, Point* opponent) {
    drawPoint(gameBoard, opponent, 'H');
}

void drawLastObstacle(GameBoard* gameBoard, Point* obstacle) {
    drawPoint(gameBoard, obstacle, 'L');
}

// ROBOT

void drawRobot(GameBoard* gameBoard, Point* robotPosition) {
    drawPoint(gameBoard, robotPosition, 'R');
}

// GAMEBOARD

void gameboardBorderPrint(GameBoard* gameBoard, int* element) {
    drawRectangle(gameBoard, 0.0f, 0.0f, GAMEBOARD_WIDTH, GAMEBOARD_HEIGHT, '|', '-');
}

// TARGET

void gameTargetPrint(GameBoard* gameBoard, int* element) {
    GameTarget* target = (GameTarget*) element;
    Location* location = target->location;
    char c;
    if (target->status == TARGET_AVAILABLE) {
        c = 'X';
    }
    else {
        c = 'O';
    }
    drawPointCoordinates(gameBoard, location->x, location->y, c);
}

void gamePathPrint(GameBoard* gameBoard, int* element) {
    PathData* pathData = (PathData*)element;
    Location* location1 = pathData->location1;
    Location* location2 = pathData->location2;
    parameterBSplineWithDistanceAndAngle(gameBoard->gameBoardCurve, location1->x, location1->y, pathData->angle1,
                                                          location2->x, location2->y, pathData->angle2,
                                                          pathData->controlPointDistance1, pathData->controlPointDistance2, 
                                                          MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL,
                                                          false);

    bSplinePrint(gameBoard, gameBoard->gameBoardCurve, '*');
}

void fillGameBoardCharElements(GameBoard* gameBoard, int* element) {
    GameStrategyContext* gameStrategyContext = gameBoard->gameStrategyContext;

    // Borders (At the beginning so it could be override by other chars)
    gameboardBorderPrint(gameBoard, element);

    // Paths
    Navigation* navigation = gameStrategyContext->navigation;
    PathList* pathList = getNavigationPathList(navigation);
    unsigned char size = pathList->size;
    unsigned int i;
    for (i = 0; i < size; i++) {
        PathData* pathData = getPath(pathList, i);
        gamePathPrint(gameBoard, (int*)pathData);
    }

    // Elements
    GameBoardElementList* gameBoardElementList = gameBoard->gameBoardElementList;
    size = gameBoardElementList->size;
    for (i = 0; i < size; i++) {
        GameBoardElement* gameBoardElement = getGameBoardElement(gameBoardElementList, i);

        GameboardPrintFunction* printFunction = gameBoardElement->printFunction;
        printFunction(gameBoard, (int*)gameBoardElement);
    }

    // Targets
    GameTargetList* gameTargetList = getGameTargetList();
    size = gameTargetList->size;
    for (i = 0; i < size; i++) {
        GameTarget* gameTarget = gameTargetList->targets[i];

        gameTargetPrint(gameBoard, (int*) gameTarget);
    }

    // Robot
    drawRobot(gameBoard, gameStrategyContext->robotPosition);

    // Last Obstacle
    drawLastObstacle(gameBoard, gameStrategyContext->lastObstaclePosition);

    // Opponent
    drawOpponent(gameBoard, gameStrategyContext->opponentRobotPosition);
}

void printGameboard(GameBoard* gameBoard,  OutputStream* outputStream) {
    println(outputStream);
    // Fill All Chars
    fillGameBoardCharElements(gameBoard, NULL);
    // Print Gameboard
    unsigned int line;
    unsigned int column;
    for (line = 0; line <= GAMEBOARD_LINE_COUNT; line++) {
        for (column = 0; column <= GAMEBOARD_COLUMN_COUNT; column++) {
            append(outputStream, gameBoard->pixels[column][line]);
        }
        append(outputStream, '\n');
    }
}

// POINT

void robotPositionPrint(GameBoard* gameBoard, int* element) {
    Point* point = (Point*) element;
    drawPoint(gameBoard, point, 'X');
}
