#include <stdlib.h>
#include <math.h>

#include "../../common/ascii/asciiUtils.h"

#include "../../common/math/cenMath.h"
#include "../../common/error/error.h"

#include "gameboard.h"
#include "gameboardElement.h"
#include "gameboardElementList.h"
#include "gameboardBSplinePrint.h"
#include "../../robot/2012/gameBoardElement2012.h"

#include "../../motion/extended/bspline.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../robot/config/robotConfig.h"
#include "../../robot/strategy/gameTarget.h"
#include "../../robot/strategy/gameTargetList.h"
#include "../../robot/strategy/gameStrategyContext.h"
#include "../../robot/strategy/gameStrategyHandler.h"

#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"

#ifdef _MSC_VER
#include <Windows.h>
#endif

// Initialization

void initGameBoard(GameBoard* gameBoard,
                   BSplineCurve* gameBoardSplineCurve,
                    GameBoardElementList* gameBoardElementList,
                    GameBoardElement(*gameBoardElementListArray)[],
                    unsigned char gameBoardElementListSize,
                    GameStrategyContext* gameStrategyContext) {
    gameBoard->showLocation = true;
    gameBoard->showPath = true;
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

// COLOR MANAGEMENT
void setGameBoardCurrentColor(GameBoard* gameBoard, char currentColorPaletIndex) {
    // ONLY ON WINDOW
#ifdef _MSC_VER
    gameBoard->currentColorPaletIndex = currentColorPaletIndex;
#endif
}

// ROBOT

void drawRobot(GameBoard* gameBoard, Point* robotPosition, float angle) {
    setGameBoardCurrentColor(gameBoard, 7);
    float x = robotPosition->x;
    float y = robotPosition->y;

    GameStrategyContext* strategyContext = gameBoard->gameStrategyContext;
    RobotConfig* robotConfig = strategyContext->robotConfig;
    enum RobotType robotType = robotConfig->robotType;
    // Draw the central point
    if (robotType == ROBOT_TYPE_BIG) {
        drawPoint(gameBoard, robotPosition, 'B');
    }
    else if (robotType == ROBOT_TYPE_SMALL) {
        drawPoint(gameBoard, robotPosition, 'S');
    }
    float radius = 150.0f;

    // Right Front Point
    float rightFrontX = x + radius * cosf(angle - (3.0f * PI / 8.0f));
    float rightFrontY = y + radius * sinf(angle - (3.0f * PI / 8.0f));

    // Right Middle Point
    float rightMiddleX = x + radius * cosf(angle - (5.0f * PI / 8.0f));
    float rightMiddleY = y + radius * sinf(angle - (5.0f * PI / 8.0f));

    // Right Bottom Point
    float rightBottomX = x + radius * cosf(angle - (7.0f * PI / 8.0f));
    float rightBottomY = y + radius * sinf(angle - (7.0f * PI / 8.0f));

    // Left Bottom Point
    float leftBottomX = x + radius * cosf(angle + (7.0f * PI / 8.0f));
    float leftBottomY = y + radius * sinf(angle + (7.0f * PI / 8.0f));

    // Left Middle Point
    float leftMiddleX = x + radius * cosf(angle + (5.0f * PI / 8.0f));
    float leftMiddleY = y + radius * sinf(angle + (5.0f * PI / 8.0f));

    // Left Front Point
    float leftFrontX = x + radius * cosf(angle + (3.0f * PI / 8.0f));
    float leftFrontY = y + radius * sinf(angle + (3.0f * PI / 8.0f));

    // set of chars if angle = PI / 2
    char verticalChar = transformVerticalChar(angle);
    char slashChar = transformSlashChar(angle);
    char horizontalChar = transformHorizontalChar(angle);
    char antiSlashChar = transformAntiSlashChar(angle);

    // Right horizontal Line
    drawLine(gameBoard, rightFrontX, rightFrontY, rightMiddleX, rightMiddleY, horizontalChar);
    // Right 45 deg line
    drawLine(gameBoard, rightMiddleX, rightMiddleY, rightBottomX, rightBottomY, antiSlashChar);
    // vertical Bottom Line
    drawLine(gameBoard, rightBottomX, rightBottomY, leftBottomX, leftBottomY, verticalChar);
    // Left 45 deg line
    drawLine(gameBoard, leftBottomX, leftBottomY, leftMiddleX, leftMiddleY, slashChar);
    // Left horizontal Line
    drawLine(gameBoard, leftMiddleX, leftMiddleY, leftFrontX, leftFrontY, horizontalChar);
    // Front vertical line
    drawLine(gameBoard, leftFrontX, leftFrontY, rightFrontX, rightFrontY, verticalChar);
    setGameBoardCurrentColor(gameBoard, 0);
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

void gamePathPrint(GameBoard* gameBoard, int* element, char c) {
    PathData* pathData = (PathData*)element;
    if (pathData == NULL) {
        writeError(PATH_NULL);
        return;
    }
    Location* location1 = pathData->location1;
    Location* location2 = pathData->location2;
    BSplineCurve* bSplineCurve = gameBoard->gameBoardCurve;

    parameterBSplineWithDistanceAndAngle(bSplineCurve, location1->x, location1->y, pathData->angleRadian1,
                                                          location2->x, location2->y, pathData->angleRadian2,
                                                          pathData->controlPointDistance1, pathData->controlPointDistance2, 
                                                          MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL,
                                                          false);

    bSplinePrint(gameBoard, bSplineCurve, c);
}

void clearGameBoardPixels(GameBoard* gameBoard) {
    unsigned int line;
    unsigned int column;
    for (line = 0; line <= GAMEBOARD_LINE_COUNT; line++) {
        for (column = 0; column <= GAMEBOARD_COLUMN_COUNT; column++) {
            gameBoard->pixels[column][line] = CHAR_NO_DRAW;
        }
    }
}

void fillGameBoardCharElements(GameBoard* gameBoard, int* element) {
    GameStrategyContext* gameStrategyContext = gameBoard->gameStrategyContext;

    // Borders (At the beginning so it could be override by other chars)
    gameboardBorderPrint(gameBoard, element);

    // Locations
    if (gameBoard->showLocation) {
        Navigation* navigation = gameStrategyContext->navigation;
        LocationList* locationList = getNavigationLocationList(navigation);
        unsigned int locationSize = locationList->size;
        unsigned int i;
        for (i = 0; i < locationSize; i++) {
            Location* location = getLocation(locationList, i);
            drawString(gameBoard, location->x, location->y, location->name);
        }
    }

    // Paths
    if (gameBoard->showPath) {
        Navigation* navigation = gameStrategyContext->navigation;
        PathList* pathList = getNavigationPathList(navigation);
        unsigned int pathSize = pathList->size;
        unsigned int i;
        for (i = 0; i < pathSize; i++) {
            PathData* pathData = getPath(pathList, i);
            // We try to use the alphabet to avoid that path could not be easily read
            char c = (char) ((i % 26) + 97);
            gamePathPrint(gameBoard, (int*)pathData, c);
        }
    }

    // Elements
    GameBoardElementList* gameBoardElementList = gameBoard->gameBoardElementList;
    unsigned int elementSize = gameBoardElementList->size;
    unsigned int i;
    for (i = 0; i < elementSize; i++) {
        GameBoardElement* gameBoardElement = getGameBoardElement(gameBoardElementList, i);

        GameboardPrintFunction* printFunction = gameBoardElement->printFunction;
        printFunction(gameBoard, (int*)gameBoardElement);
    }

    // Targets
    GameTargetList* gameTargetList = getGameTargetList();
    unsigned int targetSize = gameTargetList->size;
    for (i = 0; i < targetSize; i++) {
        GameTarget* gameTarget = gameTargetList->targets[i];

        gameTargetPrint(gameBoard, (int*) gameTarget);
    }

    // Robot
    drawRobot(gameBoard, gameStrategyContext->robotPosition, gameStrategyContext->robotAngleRadian);

    // Last Obstacle
    drawLastObstacle(gameBoard, gameStrategyContext->lastObstaclePosition);

    // Opponent
    drawOpponent(gameBoard, gameStrategyContext->opponentRobotPosition);
}

void printGameboard(GameBoard* gameBoard,  OutputStream* outputStream) {
    println(outputStream);
    clearGameBoardPixels(gameBoard);
    // Fill All Chars
    fillGameBoardCharElements(gameBoard, NULL);
    // Print Gameboard
    unsigned int line;
    unsigned int column;
    for (line = 0; line <= GAMEBOARD_LINE_COUNT; line++) {
        for (column = 0; column <= GAMEBOARD_COLUMN_COUNT; column++) {
            char pixelChar = gameBoard->pixels[column][line];
#ifdef _MSC_VER            
            char colorPalet = gameBoard->colors[column][line];
            if (colorPalet == 0) {
                colorPalet = 1;
            }
            HANDLE standardOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
            SetConsoleTextAttribute(standardOutputHandle, colorPalet);
#endif
            append(outputStream, pixelChar);
        }
        println(outputStream);
    }
}

// POINT

void robotPositionPrint(GameBoard* gameBoard, int* element) {
    Point* point = (Point*) element;
    drawPoint(gameBoard, point, 'X');
}

bool isPointInTheCollisionArea(GameBoard* gameBoard, Point* collisionPoint) {
    // The robot could not be more close to the border than 150.0f
    float windowLimit = 300.0f;
    if (collisionPoint->x <= windowLimit || collisionPoint->x >= GAMEBOARD_WIDTH - windowLimit) {
        return false;
    }
    if (collisionPoint->y <= windowLimit || collisionPoint->y >= GAMEBOARD_HEIGHT - windowLimit) {
        return false;
    }
    return true;
}
